#include "chatpage.h"

#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>



using namespace orm;
using namespace drogon_model::db;




// Add definition of your processing function here
void chatpage::getchatPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
)  const
{
    
    auto session = req->getSession();

    auto userinfo = session->get<drogon_model::db::Users>("userinfo");

    HttpViewData data;
    data.insert("nickname",userinfo.getValueOfNickname());
    LOG_INFO<<userinfo.getValueOfNickname();


    LOG_INFO<<userinfo.getValueOfUsername();
    LOG_INFO<<userinfo.getValueOfPassword();
    int id = userinfo.getValueOfId();
    
    std::vector<service::User> vec;

    vec = service::FriendModel().query(id);
    for(auto row :vec)
    {
        int id = row.getId();
        std::string name = row.getName();
        std::string state = row.getState();

        LOG_INFO<<id;
        LOG_INFO<<name;
        LOG_INFO<<state;
    }





    auto resp = HttpResponse::newHttpViewResponse("chat",data);

    resp->setStatusCode(k200OK);
    callback(resp);
}



void chatpage::addfriend(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
) const 
{
    auto jsonBody = req->getJsonObject();

    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }

    int userid = (*jsonBody)["userid"].asInt();
    int friendid = (*jsonBody)["friendid"].asInt();
    LOG_INFO<<userid;
    LOG_INFO<<friendid;
    try{
        service::FriendModel().insert(userid,friendid);
        throw std::runtime_error("添加成功");

    }catch(const std::exception& e)
    {
        throw std::runtime_error("添加失败");
    }
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);  
}



void chatpage::addgroup(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
) const
{
    auto jsonBody = req->getJsonObject();
    

    //-----------------
    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }

    int userid = (*jsonBody)["userid"].asInt();
    int groupid = (*jsonBody)["groupid"].asInt();
    std::string role = (*jsonBody)["role"].asString();
    LOG_INFO<<userid;
    LOG_INFO<<groupid;
    LOG_INFO<<role;

    try{
        service::GroupModel().addGroup(userid,groupid,role);
        throw std::runtime_error("加入成功");

    }catch(const std::exception& e)
    {
        throw std::runtime_error("加入失败");
    }
    //-----------------
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);  
}


void chatpage::oneChat(const HttpRequestPtr& req,
std::function<void (const HttpResponsePtr &)> &&callback
//const WebSocketConnectionPtr& conn
) const
{

    auto jsonBody = req->getJsonObject();

    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }

    int id = (*jsonBody)["id"].asInt();
    int toid = (*jsonBody)["toid"].asInt();
    std::string message = (*jsonBody)["message"].asString();


        LOG_INFO<<id;
        LOG_INFO<<toid;
        LOG_INFO<<message;


    Json::Value json;
    json["message"] = message;
    //------------------
    
        
    //-------------------
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);


}


void chatpage::groupChat(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback
//const WebSocketConnectionPtr& conn
) const
{




}



void chatpage::createGroups(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback
)const
{
    Json::Value data;

    auto jsonBody = req->getJsonObject();

    try{
        if(!jsonBody)
        {
            LOG_INFO<<"接收失败";
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



void chatpage::getUserInfo(const HttpRequestPtr& req,  
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

        auto userInfo = session->get<drogon_model::db::Users>("userinfo");

        auto id = userInfo.getValueOfId();
        auto nickname = userInfo.getValueOfNickname();
        auto username = userInfo.getValueOfUsername();
        
        data["id"] = id;
        data["nickname"] = nickname;
        data["username"] = username;

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