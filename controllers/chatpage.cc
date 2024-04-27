#include "chatpage.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>

// Add definition of your processing function here

void chatpage::getchatPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    
    auto session = req->session();
    //session->get<User>("userinfo");
    
    
    auto userinfo = session->get<drogon_model::db::Users>("userinfo");

    HttpViewData data;
    data.insert("nickname",userinfo.getValueOfNickname());


    auto resp = HttpResponse::newHttpViewResponse("chat",data);

    resp->setStatusCode(k200OK);
    callback(resp);
}



void chatpage::addfriend(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto jsonBody = req->getJsonObject();

    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }

    int userid = (*jsonBody)["id"].asInt();
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
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto clientPtr = app().getDbClient();
    Json::Value json;




    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);  
}


void chatpage::oneChat(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{

    auto jsonBody = req->getJsonObject();

    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }
    //LOG_ERROR<<*jsonBody;
    std::string id = (*jsonBody)["id"].asString();
    std::string toid = (*jsonBody)["toid"].asString();
    std::string message = (*jsonBody)["message"].asString();
        LOG_INFO<<id;
        LOG_INFO<<toid;
        LOG_INFO<<message;

    Json::Value value;
    value["message"] = message;

    

    


    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);


}


