#pragma once

#include <drogon/WebSocketController.h>
#include <string>

#include "../service/global.h"
#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"
#include <jsoncpp/json/json.h>

using namespace drogon;




namespace controllers
{
  class groupChatWeb : public drogon::WebSocketController<groupChatWeb>
{
  public:
     void handleNewMessage(const WebSocketConnectionPtr&,
                                  std::string &&,
                                  const WebSocketMessageType &) override;
    void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr&) override;
    void handleConnectionClosed(const WebSocketConnectionPtr&) override;
    WS_PATH_LIST_BEGIN
    // list path definitions here;
    // WS_PATH_ADD("/path", "filter1", "filter2", ...);
    WS_PATH_ADD("/group/chat",Get,Post,Options);

    WS_PATH_LIST_END
};

}
