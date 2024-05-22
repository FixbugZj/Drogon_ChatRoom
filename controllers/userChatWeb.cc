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
    // write your application logic here
    LOG_INFO<<wsConnPtr.get()->connected()<< "  "<<message;
    
    Json::Value json;
    Json::Reader reader;
    
    if (!reader.parse(message, json)) {
        LOG_INFO<<message;
        std::cout << "解析 JSON 失败" << std::endl;
        return ;
    }// 从 JSON 对象中读取特定键的值


    Json::Value msg;    
    bool fuck = reader.parse(json["content"].asString(), msg);
    if (!fuck) {
        LOG_INFO<<message;
        std::cout << "解析 JSON 失败" << std::endl;
        return ;
    }// 从 JSON 对象中读取特定键的值

    int id = msg["id"].asInt();
    int toid = msg["toid"].asInt();
    std::string mes = msg["message"].asString();

    LOG_INFO<<id<<" "<<toid<<"  "<<mes;


    global::UserChatManager::getInstance().broadcastMessageToUser(toid,message);
    



}

void controllers::userChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{


    auto id = req->getParameter("id");
    
    {
        auto clientDb=drogon::app().getDbClient();
        auto res = clientDb->execSqlSync("select id,message,time from offlinemessage where id=? order by time",std::stoi(id));
        for(auto row : res)
        {   
            std::string id = row["id"].as<std::string>();
            std::string message= row["message"].as<std::string>();
            std::string time = row["time"].as<std::string>();
            wsConnPtr->send(message);
            clientDb->execSqlSync("delete id,message,time from offlinemessage where id=?,message =?,time=?",std::stoi(id),message,time);
        }

    }
        
    if(!id.empty())
    {
        global::UserChatManager::getInstance().addUserToMap(std::stoi(id),wsConnPtr);
        service::UserModel().updateState("online",std::stoi(id));
    }
    else
    {
        LOG_ERROR << "Missing Id parameter in URL";
    }

}


void controllers::userChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    auto userMembers = global::UserChatManager::getInstance().getUserMembers();
    for(auto &user : userMembers)
    {
        auto& members = user.second;
        auto it = members.find(wsConnPtr);
        if(it!=members.end())
        {
            members.erase(it);
            if(members.empty())
            {
                global::UserChatManager::getInstance().removeUserFromMap(user.first,wsConnPtr);
                service::UserModel().updateState("offline",user.first);
            }
        }
    }

}
