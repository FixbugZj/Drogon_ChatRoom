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




void chatpage::loginPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback)
{

    auto resp = HttpResponse::newHttpViewResponse("login");
    callback(resp);
}


void chatpage::doLogin(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
//const WebSocketConnectionPtr& wsConnPtr
)    //
{
    auto jsonBody = req->getJsonObject();

    if(!jsonBody){
        LOG_INFO<<"接收失败";
    }
    

    std::string username = (*jsonBody)["username"].asString();
    std::string password = (*jsonBody)["password"].asString(); 

    LOG_INFO<<username;
    LOG_INFO<<password;

    Mapper<Users> mapper(app().getDbClient());
    auto userIndb = mapper.findOne({Users::Cols::_username,username});

    try
    {   
        int userid;
        
        service::UserModel().login(username,password);
        auto clientDb=drogon::app().getDbClient();
        
        auto res = clientDb->execSqlSync("select id from users where username = ?",username);
        for(auto row:res)
        {
            userid = row["id"].as<int>();
            LOG_ERROR<<userid;
        }

        //-------------------------------

        //userConnMap_.insert({userid,wsConnPtr});

        //-------------------------------



        
    }catch(const std::exception& e)
    {
        throw std::runtime_error("登陆失败");
    }

    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);

    auto session=req->session();
    session->insert("userinfo",userIndb);


}



void chatpage::doregister(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
) 
{   

    auto JsonBody = req->getJsonObject();
    if(!JsonBody)
    {
        LOG_INFO<<"接收失败";
    }
    
    std::string username = (*JsonBody)["username"].asString();
    std::string password = (*JsonBody)["password"].asString();
    std::string nickname = (*JsonBody)["nickname"].asString();
    service::UserModel().registdo(username,password,nickname);
    
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);   

}

// Add definition of your processing function here
void chatpage::getchatPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) 
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
std::function<void (const HttpResponsePtr &)> &&callback) 
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
std::function<void (const HttpResponsePtr &)> &&callback)
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
) 
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
) 
{




}


