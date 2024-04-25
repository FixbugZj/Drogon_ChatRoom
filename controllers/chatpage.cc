#include "chatpage.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>

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

    auto clientPtr = app().getDbClient();

    
    




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



void chatpage::getchat(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto resp = HttpResponse::newHttpViewResponse("test");
    resp->setStatusCode(k200OK);
    callback(resp);
}