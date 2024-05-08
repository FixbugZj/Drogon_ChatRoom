#include "userChatWeb.h"

#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"

using namespace drogon;
using namespace drogon_model::db;

void userChatWeb::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    LOG_INFO<<wsConnPtr.get()->connected()<< "  "<<message;
    

    Json::Value json;
    
    json["message"] = message;

    wsConnPtr->send(message);






}

void userChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    auto session = req->getSession();
    auto userinfo = session->get<Users>("userinfo");

    auto jsonBody = req->getJsonObject();
    int id = (*jsonBody)["id"].asInt();
    int toid = (*jsonBody)["id"].asInt();
    std::string message = (*jsonBody)["id"].asString();

    Json::Value json;
    json["message"] = message;

    
    


}


void userChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    


}
