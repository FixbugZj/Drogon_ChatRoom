#include "chatpage.h"
#include <drogon/drogon.h>
#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>
#include <vector>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace orm;
using namespace drogon_model::koi;




// Add definition of your processing function here
void controllers::chatpage::getchatPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
)  const
{
    Json::Value data;

    auto session = req->getSession();

    auto userinfo = session->get<drogon_model::koi::Users>("userinfo");

    // HttpViewData data;
    // data.insert("nickname",userinfo.getValueOfNickname());
    LOG_INFO<<userinfo.getValueOfNickname();


    LOG_INFO<<userinfo.getValueOfAccount();
    LOG_INFO<<userinfo.getValueOfPassword();
    int id = userinfo.getValueOfId();
    
    std::vector<service::User> vec;

    vec = service::FriendModel().query(id);

    for(auto row :vec)
    {
        int id = row.getId();
        std::string name = row.getName();

        LOG_INFO<<id;
        LOG_INFO<<name;

    }
    data["message"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(data);
    resp->setStatusCode(k500InternalServerError);
    callback(resp);
}



void controllers::chatpage::addfriend(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
) const 
{

    Json::Value data;
    try{
        auto jsonBody = req->getJsonObject();
        if(!jsonBody){

            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        int id = (*jsonBody)["Id"].asInt();
        int friendid = (*jsonBody)["friendId"].asInt();
        auto clientDb = app().getDbClient();

        auto res1 = clientDb->execSqlSync("select id from users where id = ?",friendid);
        
        if(res1.empty())
        {
            data["message"] = "该用户不存在";
            auto resp = HttpResponse::newHttpJsonResponse(data);
            resp->setStatusCode(k400BadRequest);
            callback(resp); 
        }else
        {
            auto res = clientDb->execSqlSync("select friendid from friends where id = ?",id);
            for(auto row : res)
            {   
                int fid = row["friendid"].as<int>();
                if(fid == friendid)
                {
                    data["message"] = "该用户已经是好友";
                    auto resp = HttpResponse::newHttpJsonResponse(data);
                    resp->setStatusCode(k400BadRequest);
                    callback(resp); 
                }
            }     
            service::FriendModel().insert(id,friendid);
            data["message"] = "添加成功";
            auto resp = HttpResponse::newHttpJsonResponse(data);
            resp->setStatusCode(k200OK);
            callback(resp); 
        }

     }catch(const std::exception& e)
     {
        data["message"] = "error";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp); 
     }

}

/*

void controllers::chatpage::addfriend(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const 
{
    Json::Value data;
    try {
        auto jsonBody = req->getJsonObject();
        if (!jsonBody) {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        int userId = (*jsonBody)["Id"].asInt();
        int friendId = (*jsonBody)["friendId"].asInt();
        auto clientDb = app().getDbClient();

        // Insert a record into friend_requests table
        clientDb->execSqlAsync("insert into friend_requests (from_user, to_user) values (?, ?)", userId, friendId, [userId, friendId, clientDb, callback, &data](const Result& res) {
            if (res.affectedRows() > 0) {
                // Friend request successfully inserted
                data["message"] = "好友请求已发送";
                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                return callback(resp);
            } else {
                // Failed to insert friend request
                data["message"] = "好友请求发送失败";
                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k500InternalServerError);
                return callback(resp);
            }
        });
    } catch(const std::exception& e) {
        data["message"] = "操作失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        return callback(resp); 
    }
}

*/


void controllers::chatpage::respondToFriendRequest(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const 
{
    Json::Value data;

    try {
        auto jsonBody = req->getJsonObject();
        if (!jsonBody) {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }


        int requestId = (*jsonBody)["requestId"].asInt();
        bool acceptRequest = (*jsonBody)["acceptRequest"].asBool();
        auto clientDb = app().getDbClient();

        if (acceptRequest) {
            // If the user accepts the request, add the requester as a friend

            auto res = clientDb->execSqlSync("select from_user, to_user from friendRequests where id=?", requestId);            
            if (!res.empty()){
                int fromUser;
                int toUser;
                for(auto row:res)
                {
                    fromUser = row["from_user"].as<int>();
                    toUser = row["to_user"].as<int>();;
                }

                // Insert the requester as a friend
                clientDb->execSqlSync("insert into friends (id, friendid) values (?, ?), (?, ?)", fromUser, toUser, toUser, fromUser);
                if (res.affectedRows() > 0) 
                {
                // Friend successfully added
                // Delete the friend request
                    clientDb->execSqlSync("delete from friendRequests where id = ?", requestId);
                    data["message"] = "好友请求已同意";
                    auto resp = HttpResponse::newHttpJsonResponse(data);
                    resp->setStatusCode(k200OK);
                    callback(resp);
                }else{
                // Failed to add friend
                    data["message"] = "好友请求处理失败";
                    auto resp = HttpResponse::newHttpJsonResponse(data);
                    resp->setStatusCode(k500InternalServerError);
                    callback(resp);
                }
            } else{
                    // Friend request not found
                    data["message"] = "好友请求不存在";
                    auto resp = HttpResponse::newHttpJsonResponse(data);
                    resp->setStatusCode(k404NotFound);
                    callback(resp);
                }      
        } else {
            // If the user rejects the request, delete the request
                clientDb->execSqlSync("delete from friendRequests where id = ?", requestId);
                data["message"] = "好友请求已拒绝";
                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
        }
    } catch(const std::exception& e) {
        data["message"] = "操作失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp); 
    }
}




void controllers::chatpage::addgroup(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
) const
{
    
    Json::Value data;
    try{
        auto jsonBody = req->getJsonObject();

        if(!jsonBody){
        data["msg"] = "json is empty";
        return callback(HttpResponse::newHttpJsonResponse(data));
        }

        int id = (*jsonBody)["id"].asInt();
        int groupid = (*jsonBody)["groupid"].asInt();
        std::string role = "normal";

        auto clientDb = app().getDbClient();
        auto res1 = clientDb->execSqlSync("select groupid from allgroup where groupid = ?",groupid);
        if(res1.empty())
        {
            data["message"] = "该群组不存在";
            auto resp = HttpResponse::newHttpJsonResponse(data);
            resp->setStatusCode(k400BadRequest);
            callback(resp);   
        }else
        {
            auto res = clientDb->execSqlSync("select id from groupuser where groupid=? and id = ?",groupid,id);
            if(res.empty())
            {
                service::GroupModel().addGroup(id,groupid,role);
                data["message"] = "加入成功";
                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
            }else
            {
                data["message"] = "已加入该群组";
                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k400BadRequest);
                callback(resp);
            }
        }
        
    }
    catch(const std::exception& e){
        data["message"] = "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }

}




void controllers::chatpage::createGroups(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback
)const
{
    Json::Value data;

    auto jsonBody = req->getJsonObject();

    try{
        if(!jsonBody)
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }
        
        std::string groupname = (*jsonBody)["groupname"].asString();
        std::string groupdesc = (*jsonBody)["groupdesc"].asString();
        service::GroupModel().createGroup(groupname,groupdesc);

        data["msg"] = "create success";

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }catch(const std::exception& e)
    {
        data["msg"] = "create error";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }

}



void controllers::chatpage::getUserInfo(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;

    try
    {
        auto jsonBody = req->getJsonObject();
        auto session  = req->getSession();

        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        auto userInfo = session->get<drogon_model::koi::Users>("userinfo");

        int id = userInfo.getValueOfId();
        std::string nickname = userInfo.getValueOfNickname();
        std::string account = userInfo.getValueOfAccount();
        
        std::string phone = userInfo.getValueOfPhone();
        data["id"] = id;
        data["nickname"] = nickname;
        data["account"] = account;
        data["phone"] = phone;

        /*
        生日 :
        手机 :
        */

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        throw std::runtime_error("查询失败");
        data["message"]= "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }
    
}


void controllers::chatpage::changeUserNickname(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;
    try
    {
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        //id , nickname
        int id = (*jsonBody)["id"].asInt();
        std::string nickname = (*jsonBody)["nickname"].asString();

        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("update koi.users set nickname = ? where id = ?",nickname,id);
        
        data["message"] = "修改成功";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "修改失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }
    
}





void controllers::chatpage::changeUserPassWord(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;
    try
    {
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        //id , nickname
        int id = (*jsonBody)["id"].asInt();
        std::string oldPassword = (*jsonBody)["oldPassword"].asString();
        std::string newPassword = (*jsonBody)["newPassword"].asString();

        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("select password from users where id = ?",id);
        for(auto row : res)
        {
            std::string passwrod = row["password"].as<std::string>();
            if(oldPassword == passwrod)
            {
                auto res = clientDb->execSqlSync("update koi.users set password = ? where id = ?",newPassword,id);
        
                data["message"] = "修改成功";

                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
            }
            else
            {
                data["message"] = "修改失败旧密码错误";

                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
            }
        }

    }
    catch(const std::exception& e)
    {
        data["message"] = "修改失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }
}


void controllers::chatpage::getFriendList(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;
    try
    {
        // auto jsonBody = req->getJsonObject();
        // if(jsonBody==nullptr || jsonBody->empty())
        // {
        //     data["msg"] = "json is empty";
        //     return callback(HttpResponse::newHttpJsonResponse(data));
        // }

        
        auto id = req->getParameter("id");

        auto clientPtr = app().getDbClient();
        
        //-----------------------
        Json::Value friendList(Json::arrayValue);

        std::vector<int> vec;

        {
            auto res = clientPtr->execSqlSync("select friendid from friends where id = ? and friendid != ? ",id,id);
            for(auto row : res)
            {
            int friendid = row["friendid"].as<int>();
            
            vec.push_back(friendid);
            }
        }
        

        for(auto it :vec)
        {
            auto res = clientPtr->execSqlSync("select users.id,users.nickname,users.phone from users  where id=? ",it);
            for(auto row :res)
            {   
                Json::Value user;
                user["id"] = row["id"].as<std::string>();
                user["nickname"] = row["nickname"].as<std::string>();  
                user["phone"] = row["phone"].as<std::string>();

                friendList.append(user);
            }

        }

        data["message"] = "ok";
        data["friends"] = friendList;
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }
}





//根据群组ID查询用户ID列表 除了user自己
void controllers::chatpage::getGroupUserList(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{

    Json::Value data;
    try
    {
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        //id , nickname
        //int id = (*jsonBody)["Id"].asInt();
        int groupId = (*jsonBody)["groupId"].asInt();

        auto clientPtr = app().getDbClient();

        //-----------------------
        Json::Value userList(Json::arrayValue);


        std::vector<int> vec = service::GroupModel().queryGroupUsers(groupId);
        for(auto it :vec)
        {
            auto res = clientPtr->execSqlSync("select users.id,users.nickname,users.phone,users.account from users where id = ?",it);
            for(auto row :res)
            {   
                Json::Value user;
                user["id"] = row["id"].as<std::string>();
                user["account"] = row["account"].as<std::string>();
                user["nickname"] = row["nickname"].as<std::string>();  
                user["phone"] = row["phone"].as<std::string>();

                userList.append(user);
            }

        }

        data["message"] = "ok";
        data["users"] = userList;

        //data["message"] = "修改成功";

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }

}


void controllers::chatpage::changeGroupName(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;
    try
    {
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        //id , nickname
        int groupId = (*jsonBody)["groupId"].asInt();
        std::string newName = (*jsonBody)["newName"].asString();

        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("update koi.allgroup set groupname = ? where id = ?",newName,groupId);
        
        data["message"] = "修改成功";

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "修改失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }
    
}


//根据用户ID搜索群聊列表 
void controllers::chatpage::getGroupList(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;

    try
    {
        // auto jsonBody = req->getJsonObject();
        // if(jsonBody==nullptr || jsonBody->empty())
        // {
        //     data["msg"] = "json is empty";
        //     return callback(HttpResponse::newHttpJsonResponse(data));
        // }
   

        auto id = req->getParameter("id");

        auto clientDb=drogon::app().getDbClient();

        Json::Value groupList(Json::arrayValue);

        std::vector<int> vec;

        {
            auto res = clientDb->execSqlSync("select groupid from groupuser where id = ? ",id);
            for(auto row : res)
            {   
            int groupid = row["groupid"].as<int>();

            vec.push_back(groupid);
            }
        }

        for(auto it :vec)
        {
            auto res = clientDb->execSqlSync("select * from allgroup  where groupid=?",it);
            for(auto row :res)
            {   
                Json::Value group;
                group["id"] = row["groupid"].as<std::string>();
                group["nickname"] = row["groupname"].as<std::string>();  
                //group["groupdesc"] = row["groupdesc"].as<std::string>();

                groupList.append(group);
            }

        }

        data["message"] = "查询成功";
        data["groups"] = groupList;
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch(const std::exception& e)
    {
        data["message"] = "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }

}


//删除好友
void controllers::chatpage::deleteFriend(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;

    try
    {
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        //id , nickname
        int id = (*jsonBody)["Id"].asInt();
        int friendId = (*jsonBody)["friendId"].asInt();

        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("DELETE FROM friends WHERE (id = ? AND friendid = ?) OR (id = ? AND friendid = ?)",id,friendId,friendId,id);
        
        data["message"] = "删除成功";

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "删除失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }


}

//解散群聊
void controllers::chatpage::deleteGroup(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;

    try
    {
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        //id , nickname
        int id = (*jsonBody)["Id"].asInt();
        int groupId = (*jsonBody)["groupId"].asInt();


        
        auto clientDb=drogon::app().getDbClient();
        //Mapper(clientDb)
        //auto res = clientDb->execSqlSync();
        
        data["message"] = "解散成功";

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "删除失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);

    }

}


void controllers::chatpage::uploadAvatar(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{

    Json::Value data;
    FileUpload fileUpload;
    
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Must only be one file");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }

    auto &file = fileUpload.getFiles()[0];
    auto md5 = file.getMd5();
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(
        "The server has calculated the file's MD5 hash to be " + md5);
    file.save();
    LOG_INFO << "The uploaded file has been saved to the ./uploads "
                "directory";
    callback(resp);
    

}





//-------通过------
void controllers::chatpage::getHistoryMessage(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;
    try
    {
        // auto jsonBody = req->getJsonObject();

        // if(jsonBody==nullptr || jsonBody->empty())
        // {
        //     data["msg"] = "json is empty";
        //     return callback(HttpResponse::newHttpJsonResponse(data));
        // }

        //id , nickname
      
        auto userId = req->getParameter("Id");
        auto toId = req->getParameter("toId");
        auto clientDb=drogon::app().getDbClient();

        Json::Value messageList(Json::arrayValue);
        auto res = clientDb->execSqlSync("select * from historymessages where (from_id = ? and id = ?) or (from_id = ? and id = ?) ORDER BY time ASC",std::stoi(toId),std::stoi(userId),std::stoi(userId),std::stoi(toId));
        for(auto row : res)
        {
            Json::Value message;
            message["id"] = row["id"].as<std::string>();
            message["from_id"] = row["from_id"].as<std::string>();
            message["message"] = row["message"].as<std::string>();
            message["time"] = row["time"].as<std::string>();

            messageList.append(message);
        }
             
        data["message"] = "ok";
        data["messageList"] = messageList;
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch(const std::exception& e)
    {
        data["message"] = "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}


