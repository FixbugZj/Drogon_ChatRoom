#include "userChatWeb.h"
#include <string>

#include "../service/global.h"
#include "../service/UserModel.h"
#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"

#include <jsoncpp/json/json.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Result.h>
#include <drogon/orm/Exception.h>
#include <drogon/orm/Mapper.h>


using namespace drogon;
using namespace drogon_model::koi;
using namespace global;
using namespace orm;

void controllers::userChatWeb::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    //write your application logic here
    LOG_INFO<<wsConnPtr.get()->connected()<< "  "<<message;
    
    Json::Value json;
    Json::Reader reader;
    
    if (!reader.parse(message, json)) {
        LOG_ERROR << "Failed to parse JSON: " << message;
        return;
    }

    if (!json.isMember("id") || !json["id"].isInt()) {
        LOG_ERROR << "Invalid 'id' field in JSON: " << message;
        return;
    }

    if (!json.isMember("toid") || !json["toid"].isInt()) {
        LOG_ERROR << "Invalid 'toid' field in JSON: " << message;
        return;
    }



    int id = json["id"].asInt();
    int toid = json["toid"].asInt();
    std::string mes = json["message"].asString();

    LOG_INFO<<id<<" "<<toid<<"  "<<mes;
    global::UserChatManager::getInstance().broadcastMessageToUser(id,toid,mes);
    
    try
    {
        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("insert into historymessages(id,from_id,message) values(?,?,?)",toid,id,mes);
    }
    catch(const std::exception& e)
    {
        LOG_ERROR<<"数据库连接失败";
        return ;
    }



}

void controllers::userChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{


    auto id = req->getParameter("id");
    auto toid = req->getParameter("toid");
    global::UserChatManager::getInstance().addUserToMap(std::stoi(id),std::stoi(toid),wsConnPtr);
    service::UserModel().updateState("online",std::stoi(id));
    //std::unordered_map<int, std::unordered_set<drogon::WebSocketConnectionPtr>> map =  global::UserChatManager::getInstance().getUserMembers();



    auto clientDb=drogon::app().getDbClient();
    auto res = clientDb->execSqlSync("select id,message,from_id,time from offlinemessages where id=? order by time",std::stoi(id));
    if(!res.empty())
    {
        for(auto row : res)
        {   
            std::string id = row["id"].as<std::string>();
            std::string from_id = row["from_id"].as<std::string>();
            std::string message= row["message"].as<std::string>();
            std::string time = row["time"].as<std::string>();
            //wsConnPtr->send(message);
            //clientDb->execSqlSync("delete from offlinemessages where id=? and from_id=? and message =? and time=?",std::stoi(id),std::stoi(from_id),message,time);
        }
    }

        

}

void controllers::userChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here

    // auto userMembers = global::UserChatManager::getInstance().getUserMembers();

    // for(auto &user : userMembers)
    // {
    //     auto& members = user.second;
    //     auto it = members.find(wsConnPtr);
    //     if(it!=members.end())
    //     {
    //         members.erase(it);
    //         if(members.empty())
    //         {
    //             global::UserChatManager::getInstance().removeUserFromMap(user.first,wsConnPtr);
    //             service::UserModel().updateState("offline",user.first);
    //         }
    //     }
    // }
}



