#include "groupChatWeb.h"
#include "../service/global.h"
#include "../service/global.h"
#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"
#include <jsoncpp/json/json.h>

using namespace drogon;
using namespace drogon_model::koi;
using namespace global;

void controllers::groupChatWeb::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
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

    if (!json.isMember("groupid") ) {
        LOG_ERROR << "Invalid 'toid' field in JSON: " << message;
        return ;
    }

    

}

void controllers::groupChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& conn)
{
    // // write your application logic here
    // LOG_DEBUG << "new websocket connection!";
    // auto userid = req->getParameter("id");
    // auto groupid = req->getParameter("groupid");
    // useridVec = service::GroupModel().queryGroupUsers(std::stoi(userid),std::stoi(groupid));
    

}


void controllers::groupChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& conn)
{

    

}
