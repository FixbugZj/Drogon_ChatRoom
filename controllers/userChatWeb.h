#pragma once

#include <drogon/WebSocketController.h>

#include <unordered_map>


#include "chatpage.h"


using namespace drogon;



struct JsonMessage
{
  int id;
  int toid;
  std::string message;
};



namespace controllers
{
  class userChatWeb : public drogon::WebSocketController<userChatWeb>
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
    WS_PATH_ADD("/user/chat",Get,Post,Options);
    
    WS_PATH_LIST_END

  private:

};
}




