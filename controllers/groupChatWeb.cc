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
    std::string chatRoomName = json["chatRoomName"].asString();
    std::string  mes  = json["message"].asString();

    auto &s = wsConnPtr->getContextRef<chatRoom>();
    chatRooms_.publish(chatRoomName, mes);



}

void controllers::groupChatWeb::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& conn)
{
    // write your application logic here
    LOG_DEBUG << "new websocket connection!";

    chatRoom chatroom;
    chatroom.chatRoomName = req->getParameter("room_name");
    chatroom.id = chatRooms_.subscribe(chatroom.chatRoomName,
                                 [conn](const std::string &topic,
                                        const std::string &message) {
                                     // Suppress unused variable warning
                                     (void)topic;
                                     conn->send(message);
                                 });
    conn->setContext(std::make_shared<chatRoom>(std::move(chatroom)));

}


void controllers::groupChatWeb::handleConnectionClosed(const WebSocketConnectionPtr& conn)
{
    // write your application logic here
    // auto groupMembers = GroupChatManager::getInstance().getGroupMembers();
    // for (auto& group : groupMembers) {
    //     auto& members = group.second;
    //     auto it = members.find(wsConnPtr);
    //     if (it != members.end()) {
    //         members.erase(it);
    //         if (members.empty()) {
    //             GroupChatManager::getInstance().removeUserFromGroup(group.first, wsConnPtr);
    //         }
    //     }
    // }
    
    LOG_DEBUG << "websocket closed!";
    auto &s = conn->getContextRef<chatRoom>();
    chatRooms_.unsubscribe(s.chatRoomName, s.id);

}
