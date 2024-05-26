#ifndef CHECKLOGINUTILS_H
#define CHECKLOGINUTILS_H

#include <jwt-cpp/jwt.h>
#include <drogon/HttpAppFramework.h>
#include <optional>


namespace utils_m
{
    class CheckLogin
{
public:
    [[gnu::always_inline]] inline static std::optional<std::string> checklogin(const drogon::HttpRequestPtr& req);

};

std::optional<std::string> utils::CheckLogin::checklogin(const drogon::HttpRequestPtr& req)
{
    try
    {
        const auto req_token = req->getHeader("Authorization");
        const auto decoded = jwt::decode(req_token);
        const auto verifier = jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256{drogon::app().getCustomConfig()["jwt-secret"].asString()})
                            .with_issuer("auth0");

        verifier.verify(decoded);
        return decoded.get_payload_claim("user_id").as_string();
    }
    catch(const std::exception& e)
    {
        return std::nullopt;
    }

}
}


#endif