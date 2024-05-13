#include "User.h"

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



void controllers::User::loginPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{

    auto resp = HttpResponse::newHttpViewResponse("login");
    callback(resp);

}




void controllers::User::doLogin(const HttpRequestPtr& req, 
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
        

        std::string account = (*jsonBody)["account"].asString();
        std::string password = (*jsonBody)["password"].asString(); 

        LOG_INFO<<account;
        LOG_INFO<<password;

        Mapper<Users> mapper(app().getDbClient());
        auto userIndb = mapper.findOne({Users::Cols::_account,account});



        service::UserModel().login(account,password);

        // auto clientDb=drogon::app().getDbClient();
        

        // int userid;
        // std::string nickname;
        // auto res = clientDb->execSqlSync("select id,nickname from users where username = ?",username);
        // for(auto row:res)
        // {
        //     userid = row["id"].as<int>();
        //     nickname = row["nickname"].as<std::string>();
        //     LOG_INFO<<userid;
        // }


        //-------------------------------
        // auto token = jwt::create()
        //                 .set_issuer("auth0")
        //                 .set_type("JWS")
        //                 .set_payload_claim("user_id", jwt::claim(std::string("123456")))
        //                 .set_payload_claim("name", jwt::claim(std::string("xxxxx")))
        //                 .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{drogon::app().getCustomConfig()["jwt-sessionTime"].asInt()})
        //                 .sign(jwt::algorithm::hs256{drogon::app().getCustomConfig()["jwt-secret"].asString()});


        // std::cout << "secret = " << drogon::app().getCustomConfig()["jwt-secret"].asString() << std::endl;
        // std::cout << "sessionTime = " << drogon::app().getCustomConfig()["jwt-sessionTime"].asInt() << std::endl;

        data["message"] = "ok";
        // data["nickename"] = nickname;
        // data["token"] = token;
        // data["id"] = userid;
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



void controllers::User::doregister(const HttpRequestPtr& req, 
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
    //service::UserModel().registdo(username,password,nickname);
    
    
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);   

}
