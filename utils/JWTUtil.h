#pragma once
#include <jwt-cpp/jwt.h>
#include <string>




namespace utils_m
{

class JWTUtil
{
public:
    std::string createToken(std::string userId);
    std::string verifyToken(std::string token);



private:
    long EXPIRE_TIME = 15*60*1000; //15MIN
    std::string TOKEN_SECRET = "privateKey";

};

}

