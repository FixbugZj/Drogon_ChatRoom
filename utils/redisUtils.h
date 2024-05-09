#pragma once

#include <optional>
#include <string>
#include <drogon/drogon.h>

class redisUtils
{
public:
    static std::optional<std::string> getRedisValue(const std::string& command);

    static drogon::Task<std::string> getCoroRedisValue(const std::string& command);
};