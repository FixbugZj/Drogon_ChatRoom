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
#include <algorithm>



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
    }

    if (!json.isMember("id") ) {
    LOG_ERROR << "Invalid 'id' field in JSON: " << message;
    return ;
    }

    if (!json.isMember("toid") ) {
        LOG_ERROR << "Invalid 'toid' field in JSON: " << message;
        return ;
    }

    try
    {
        int  id = json["id"].asInt();
        int  toid  = json["toid"].asInt();
        std::string  mes = json["message"].asString();
        
        try{
            global::UserChatManager::getInstance().broadcastMessageToUser(id,toid,mes);
            auto clientDb=drogon::app().getDbClient();
            auto res = clientDb->execSqlSync("insert into historymessages(id,from_id,message) values(?,?,?)",toid,id,mes);
  
        }catch(const std::exception& e)
        {
            LOG_INFO<<"error";
        }
        
       
        
    }
    catch(const std::exception& e)
    {
        LOG_INFO<<e.what();
    }
    

}

void controllers::userChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{

        LOG_INFO<<"-------------CONNECTION-------------";
        auto id = req->getParameter("id");
 
        global::UserChatManager::getInstance().addUserToMap(std::stoi(id),wsConnPtr);


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
                wsConnPtr->send(message);
                clientDb->execSqlSync("delete from offlinemessages where id=? and from_id=? and message =? and time=?",std::stoi(id),std::stoi(from_id),message,time);
            }
        }
       
        
    service::UserModel().updateState("online",std::stoi(id));

}


void controllers::userChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    auto userMembers = global::UserChatManager::getInstance().getUserMembers();
    for(auto it = userMembers.begin();it!=userMembers.end();)
        {
            LOG_INFO<<"----------  close--------";
            LOG_INFO<<it->first<<" --- "<<it->second->connected();
            LOG_INFO<<"-------------------------";
            if(it->second->connected()==false)
            {
                it=userMembers.erase(it);
                
            }
            else
            {
                ++it;
            }
        }    
}



