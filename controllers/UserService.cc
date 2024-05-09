#include "UserService.h"

#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>
#include <jwt-cpp/jwt.h>



using namespace orm;
using namespace drogon_model::db;
// Add definition of your processing function here


void UserService::loginPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{

    auto resp = HttpResponse::newHttpViewResponse("login");
    callback(resp);
}


void UserService::doLogin(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
//const WebSocketConnectionPtr& wsConnPtr
) const    //
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
        

        std::string username = (*jsonBody)["username"].asString();
        std::string password = (*jsonBody)["password"].asString(); 

        LOG_INFO<<username;
        LOG_INFO<<password;

        Mapper<Users> mapper(app().getDbClient());
        auto userIndb = mapper.findOne({Users::Cols::_username,username});


        int userid;
        
        service::UserModel().login(username,password);

        auto clientDb=drogon::app().getDbClient();
        
        auto res = clientDb->execSqlSync("select id from users where username = ?",username);
        for(auto row:res)
        {
            userid = row["id"].as<int>();
            LOG_INFO<<userid;
        }


        //-------------------------------
        auto token = jwt::create()
                        .set_issuer("auth0")
                        .set_type("JWS")
                        .set_payload_claim("user_id", jwt::claim(std::string("123456")))
                        .set_payload_claim("name", jwt::claim(std::string("xxxxx")))
                        .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{drogon::app().getCustomConfig()["jwt-sessionTime"].asInt()})
                        .sign(jwt::algorithm::hs256{drogon::app().getCustomConfig()["jwt-secret"].asString()});


        std::cout << "secret = " << drogon::app().getCustomConfig()["jwt-secret"].asString() << std::endl;
        std::cout << "sessionTime = " << drogon::app().getCustomConfig()["jwt-sessionTime"].asInt() << std::endl;

        data["message"] = "ok";
        data["username"] = username;
        data["token"] = token;
        data["id"] = userid;
        //-------------------------------


        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);

        auto session=req->session();
        session->insert("userinfo",userIndb);
        
        
    }catch(const std::exception& e)
    {

        data["message"] = "loginError";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);
    }

    
}



void UserService::doregister(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
)  const
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