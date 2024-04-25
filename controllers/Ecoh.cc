#include "Ecoh.h"

void Ecoh::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    if(wsConnPtr->connected()){
        wsConnPtr->send("123");
    }
    

}

void Ecoh::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    auto resp = HttpResponse::newHttpViewResponse("websocket");
    resp->setStatusCode(k200OK);
    
}

void Ecoh::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here

}
