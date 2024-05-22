#include "personalCenter.h"
#include <drogon/drogon.h>
#include "../service/UserModel.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Exception.h>
#include <stdexcept>
#include "../service/UserModel.h"
#include <drogon/orm/Result.h>
#include <vector>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <sstream>
#include <iostream>

// Add definition of your processing function here




void controllers::personalCenter::getUserInfo(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    //获取用户信息


}


void controllers::personalCenter::changeUserInfo(const HttpRequestPtr& req,  
std::function<void (const HttpResponsePtr &)> &&callback) const
{
    //修改用户信息


}


//------业务待添加

