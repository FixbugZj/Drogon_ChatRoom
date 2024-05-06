#include "userfunc.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>



using namespace orm;
using namespace drogon_model::db;

// Add definition of your processing function here
void userfunc::loginPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    
    // data.insert("nickname",std::string("于森"));
    //auto session = req->session();
    //auto userinfo = session->get<drogon_model::db::Users>("userinfo");
    
    
    //HttpViewData data;
    //data.insert("nickname",userinfo.getValueOfNickname());
    //LOG_INFO<<userinfo.getValueOfNickname();

    auto resp = HttpResponse::newHttpViewResponse("login");
    callback(resp);
}


void userfunc::doLogin(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback,
//drogon_model::db::Users &user
User users) const   //
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
            int id = row["id"].as<int>();
            LOG_ERROR<<id;
        }
    
        //WebSocketConnectionPtr conn;
        
        //_userConnMap.insert(std::make_pair(userid, conn));


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
    
    std::string username = (*JsonBody)["username"].asString();
    std::string password = (*JsonBody)["password"].asString();
    std::string nickname = (*JsonBody)["nickname"].asString();
    service::UserModel().registdo(username,password,nickname);
    
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);   
    // auto resp = HttpResponse::newHttpJsonResponse(json);
    // callback(resp);

}


//-------------------------







