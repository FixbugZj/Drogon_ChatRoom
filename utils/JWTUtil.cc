#include "JWTUtil.h"
#include <jwt-cpp/jwt.h>
#include <drogon/drogon.h>
#include <chrono>
#include <algorithm>

std::string utils_m::JWTUtil::createToken(std::string Id)
{
    try
    {
        auto currentTime = std::chrono::system_clock::now();
        auto expireTime = currentTime + std::chrono::seconds(EXPIRE_TIME);
        auto algorithm = jwt::algorithm::hs256(TOKEN_SECRET);

        auto token = jwt::create()
                        .set_issuer("auth0")
                        .set_type("JWS")
                        .set_payload_claim("user_id", jwt::claim(Id))
                        .set_expires_at(currentTime + std::chrono::seconds(EXPIRE_TIME))
                        .sign(jwt::algorithm::hs256(TOKEN_SECRET));
        
        return token;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "";
    }
    

}

std::string utils_m::JWTUtil::verifyToken(std::string token)
{
    try
    {
        auto de = jwt::decode(token);
        auto user_id = de.get_payload_claim("user_id").as_string();
        return user_id;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "";
    }
    
}