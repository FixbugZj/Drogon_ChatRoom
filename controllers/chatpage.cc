#include "chatpage.h"

#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>
#include <vector>
#include <jsoncpp/json/value.h>



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
    resp->setStatusCode(k200OK);
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

        auto res = clientDb->execSqlSync("select friendid from friends where id = ?",id);
        for(auto row : res)
        {   
            int fid = row["friendid"].as<int>();
            if(fid == friendid)
            {
                data["message"] = "用户已经存在";
                return callback(HttpResponse::newHttpJsonResponse(data));
            }
        }

        service::FriendModel().insert(id,friendid);
        data["message"] = "ok";
            
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp); 

     }catch(const std::exception& e)
     {
         data["message"] = "error";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
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
        service::GroupModel().addGroup(id,groupid,role);


        data["message"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch(const std::exception& e){
        data["message"] = "查询失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
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
        resp->setStatusCode(k200OK);
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
        resp->setStatusCode(k200OK);
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
        resp->setStatusCode(k200OK);
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
        std::string password = (*jsonBody)["password"].asString();

        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("update koi.users set password = ? where id = ?",password,id);
        
        data["message"] = "修改成功";

        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
    catch(const std::exception& e)
    {
        data["message"] = "修改失败";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

    }
}


void controllers::chatpage::getFriendList(const HttpRequestPtr& req,  
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

        int id = (*jsonBody)["Id"].asInt();

        auto clientPtr = app().getDbClient();
        
        //-----------------------
        Json::Value friendList(Json::arrayValue);

        std::vector<int> vec;

        {
            auto res = clientPtr->execSqlSync("select friendid from friends where id = ?",id);
            for(auto row : res)
            {
            int id = row["friendid"].as<int>();

            vec.push_back(id);
            }
        }
        

        for(auto it :vec)
        {
            auto res = clientPtr->execSqlSync("select users.id,users.nickname,users.phone from users  where id=?",it);
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
        resp->setStatusCode(k200OK);
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
        resp->setStatusCode(k200OK);
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
        resp->setStatusCode(k200OK);
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
        auto jsonBody = req->getJsonObject();
        if(jsonBody==nullptr || jsonBody->empty())
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }
   

        int id = (*jsonBody)["Id"].asInt();

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
                group["groupid"] = row["groupid"].as<std::string>();
                group["groupname"] = row["groupname"].as<std::string>();  
                group["groupdesc"] = row["groupdesc"].as<std::string>();

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
        resp->setStatusCode(k200OK);
        callback(resp);

    }



}


//删除好友
void controllers::chatpage::deleteFriend(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;



}

//解散群聊
void controllers::chatpage::deleteGroup(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{



}
