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
    // write your application logic here
    LOG_INFO<<wsConnPtr.get()->connected()<< "  "<<message;

    Json::Value json;
    Json::Reader reader;

    if (!reader.parse(message, json)) {
        LOG_INFO<<message;
        std::cout << "解析 JSON 失败" << std::endl;
        return ;
    }

    Json::Value msg;
    bool fuck = reader.parse(json["content"].asString(), msg);
    if (!fuck) {
        LOG_INFO<<message;
        std::cout << "解析 JSON 失败" << std::endl;
        return ;
    }// 从 JSON 对象中读取特定键的值


    int groupId = msg["groupId"].asInt();
    std::string mes = msg["message"].asString();
    
    global::GroupChatManager::getInstance().broadcastMessageToGroup(groupId, message);



}

void controllers::groupChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    auto groupId = req->getParameter("groupId");

    if (!groupId.empty()) {
        global::GroupChatManager::getInstance().addUserToGroup(std::stoi(groupId), wsConnPtr);
    } else {
        LOG_ERROR << "Missing groupId parameter in URL";
    }

}


void controllers::groupChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    auto groupMembers = GroupChatManager::getInstance().getGroupMembers();
    for (auto& group : groupMembers) {
        auto& members = group.second;
        auto it = members.find(wsConnPtr);
        if (it != members.end()) {
            members.erase(it);
            if (members.empty()) {
                GroupChatManager::getInstance().removeUserFromGroup(group.first, wsConnPtr);
            }
        }
    }

}
