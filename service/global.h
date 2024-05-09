#pragma once


#include <unordered_map>
#include <drogon/WebSocketConnection.h>

namespace global{

    std::unordered_map<int,std::shared_ptr<WebSocketConnection>> userConnMap_;



}
