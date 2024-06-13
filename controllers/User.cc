#include "User.h"

#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>
#include <../utils/cryptopp.h>
#include <jwt-cpp/jwt.h>
#include <chrono>
#include "../utils/JWTUtil.h"


using namespace orm;
using namespace drogon_model::koi;
// Add definition of your processing function here



void controllers::User::loginPage(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback) const
{

    Json::Value json;
    json["message"] = "ok";

    auto resp = HttpResponse::newHttpJsonResponse(json);
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

        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("select id,nickname from users where account=? and password = ?",account,password);
        if(res.empty())
        {
            auto resp = HttpResponse::newHttpJsonResponse(data);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
        }
        else
        {
            int id;
            std::string nickname;
            for(auto row:res)
            {
                id = row["id"].as<int>();
                nickname = row["nickname"].as<std::string>();
                LOG_INFO<<id;
            }
                data["message"] = "ok";
                data["nickname"] = nickname;
                //data["token"] = token;
                data["id"] = id;

                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
        }
        //-------------------------------
        //auto user_id = de.get_payload_claim("user_id").as_string();
        //auto account_token = de.get_payload_claim("account").as_string();
        //--------------------------------

    }catch(const std::exception& e)
    {

        data["message"] = "loginError";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }

    

}



void controllers::User::doregister(const HttpRequestPtr& req, 
std::function<void (const HttpResponsePtr &)> &&callback
)  const
{   
    Json::Value data;

    try
    {
        auto jsonBody = req->getJsonObject();
        if(!jsonBody){

            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        
        }
        
        std::string account = (*jsonBody)["account"].asString();
        std::string password = (*jsonBody)["password"].asString();
        //std::string nickname = (*jsonBody)["nickname"].asString();

        // std::string salt = utils::Cryptopp::generateSalt();
        // std::string hashedPassword = utils::Cryptopp::hashPassword(password + salt);


        service::UserModel().registdo(account,password);
        
        data["message"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k200OK);
        callback(resp);   
    }
    catch(const std::exception& e)
    {   
        data["message"] = "error";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp); 

    }
}
