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

    auto value1 = req->getParameter("username");
    auto Result = clientPtr->execSqlSync("select username from users where username = ? ",value1);
    if(Result.empty())
    {
        throw std::runtime_error("该用户不存在,请从新输入");
        
    }
    else
    {
        //clientPtr->execSqlSync("")
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



