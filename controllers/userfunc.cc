#include "userfunc.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"

using namespace orm;
//using namespace drogon_model::db;

// Add definition of your processing function here
void userfunc::loginPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    
   // data.insert("nickname",std::string("于森"));
    auto session = req->session();
    auto userinfo = session->get<drogon_model::db::Users>("userinfo");
    
    auto sessionID = req->session().get()->sessionId();
    HttpViewData data;
    data.insert("nickname",userinfo.getValueOfNickname());

    auto resp = HttpResponse::newHttpViewResponse("login",data);
    callback(resp);
}


void userfunc::dologin(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback,
//drogon_model::db::Users &user,
User user) const
{
    auto jsonBody = req->getJsonObject();

    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }
    //LOG_ERROR<<*jsonBody;
    

    std::string username = (*jsonBody)["username"].asString();//"yusen";//req->getParameter("username");
    std::string password = (*jsonBody)["password"].asString(); //"123456";//req->getParameter("password");

    LOG_INFO<<username;
    LOG_INFO<<password;

    
    service::UserModel().login(username,password);


    auto session=req->session();
    //session.insert();

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);

}



void userfunc::doregister(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
//drogon_model::db::Users user
) const
{   

    auto JsonBody = req->getJsonObject();
    if(!JsonBody)
    {
        LOG_INFO<<"接收失败";
    }
    
    std::string username = req->getParameter("username");
    std::string password = req->getParameter("password");
    std::string nickname = req->getParameter("nickename");
    service::UserModel().registdo(username,password,nickname);
    
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);   
    // auto resp = HttpResponse::newHttpJsonResponse(json);
    // callback(resp);

}


//-------------------------



