#include "personalCenter.h"
#include <drogon/drogon.h>
#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>
#include <vector>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <sstream>
#include <iostream>

// Add definition of your processing function here
using namespace orm;
using namespace drogon_model::koi;



void controllers::personalCenter::getUserInfo(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Json::Value data;
    try
    {
        
        auto jsonBody = req->getJsonObject();
        if(!jsonBody)
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        std::string id = (*jsonBody)["id"].asString();
        auto clientDb = app().getDbClient();
        auto res = clientDb->execSqlSync("select * from users where id = ?",std::stoi(id));
        if(!res.empty())
        {
            for(auto row:res)
            {
                std::string id = row["id"].as<std::string>();
                std::string nickname =  row["nickname"].as<std::string>();
                std::string account = row["account"].as<std::string>();
                std::string sex = row["sex"].as<std::string>();
                std::string phone = row["phone"].as<std::string>();
                std::string createtime = row["createTime"].as<std::string>();

                data["id"] = id;
                data["nickname"] = nickname;
                data["account"] = account;
                data["sex"] = sex;
                data["phone"] = phone;
                data["createtime"] = createtime;


                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
            }
        }else{
                    data["message"] = "未查询到信息";
                    auto resp = HttpResponse::newHttpJsonResponse(data);
                    resp->setStatusCode(k200OK);
                    callback(resp);
        }
    }
    catch(const std::exception& e)
    {
        data["message"] = "无数据";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp); 
    }
    
}

 

void controllers::personalCenter::changeUserInfo(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    //修改用户信息
    Json::Value data;
    try
    {
        auto jsonBody = req->getJsonObject();
        if(!jsonBody)
        {
            data["msg"] = "json is empty";
            return callback(HttpResponse::newHttpJsonResponse(data));
        }

        std::string id = (*jsonBody)["Id"].asString();
        std::string nickname =(*jsonBody)["nickname"].asString();
        std::string phone = (*jsonBody)["phone"].asString();
        std::string sex = (*jsonBody)["sex"].asString();


        auto clientDb = app().getDbClient();
        auto res = clientDb->execSqlSync("update users set nickname = ?,phone = ?,sex=? where id = ?",nickname,phone,sex,std::stoi(id));
        if(!res.empty())
        {
            for(auto row:res)
            {
                std::string id = row["id"].as<std::string>();
                std::string nickname =  row["nickname"].as<std::string>();
                std::string account = row["account"].as<std::string>();
                std::string sex = row["sex"].as<std::string>();
                std::string phone = row["phone"].as<std::string>();
                std::string createtime = row["createTime"].as<std::string>();

                data["id"] = id;
                data["nickname"] = nickname;
                data["account"] = account;
                data["sex"] = sex;
                data["phone"] = phone;
                data["createtime"] = createtime;


                auto resp = HttpResponse::newHttpJsonResponse(data);
                resp->setStatusCode(k200OK);
                callback(resp);
            }
        }else{
                    data["message"] = "修改失败";
                    auto resp = HttpResponse::newHttpJsonResponse(data);
                    resp->setStatusCode(k200OK);
                    callback(resp);
        }

    }
    catch(const std::exception& e)
    {
        data["message"] = "error";
        auto resp = HttpResponse::newHttpJsonResponse(data);
        resp->setStatusCode(k500InternalServerError);
        callback(resp); 
    }

}


//------业务待添加

