#pragma once

#include <drogon/HttpController.h>

#include <drogon/WebSocketController.h>
#include <drogon/WebSocketConnection.h>
#include <trantor/net/TcpConnection.h>


#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"
#include "../service/UserModel.h"
#include "../models/Friendrequests.h"
#include "../models/Historymessages.h"


using namespace drogon;


namespace controllers
{

  class chatpage : public drogon::HttpController<chatpage>
{
public:
  METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(chatpage::get, "/{2}/{1}", Get); // path is /chatpage/{arg2}/{arg1}
    // METHOD_ADD(chatpage::your_method_name, "/{1}/{2}/list", Get); // path is /chatpage/{arg1}/{arg2}/list
    // ADD_METHOD_TO(chatpage::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    
    
    ADD_METHOD_TO(chatpage::getchatPage,"/user/chat",Get,Options);

    ADD_METHOD_TO(chatpage::addfriend,"/user/chat/addfriend",Post,Options);

    ADD_METHOD_TO(chatpage::addgroup,"/user/chat/addgroup",Post,Options);

    ADD_METHOD_TO(chatpage::respondToFriendRequest,"/user/chat/respondFriendRequest",Post,Options);

    ADD_METHOD_TO(chatpage::createGroups,"/user/chat/createGroup",Post,Options);

    ADD_METHOD_TO(chatpage::getUserInfo,"/user/chat/getUserInfo",Post,Options);

    ADD_METHOD_TO(chatpage::changeUserNickname,"/user/chat/changeUserNickname",Post,Options);

    ADD_METHOD_TO(chatpage::changeUserPassWord,"/user/chat/changeUserPassWord",Post,Options);

    ADD_METHOD_TO(chatpage::getFriendList,"/user/chat/getFriendList",Get,Post,Options);

    ADD_METHOD_TO(chatpage::getGroupUserList,"/user/chat/getGroupUserList",Get,Post,Options);

    ADD_METHOD_TO(chatpage::changeGroupName,"/user/chat/changeGroupName",Post,Options);

    ADD_METHOD_TO(chatpage::getGroupList,"/user/chat/getGroupList",Get,Post,Options);
    
    ADD_METHOD_TO(chatpage::deleteFriend,"/user/chat/deleteFriend",Post,Options);

    ADD_METHOD_TO(chatpage::deleteGroup,"/user/chat/deleteGroup",Post,Options);

    ADD_METHOD_TO(chatpage::uploadAvatar,"/user/chat/uploadAvatar",Post,Options);

    ADD_METHOD_TO(chatpage::getHistoryMessage,"/user/chat/getHistoryMessage",Get,Post,Options);


  METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

    void getchatPage(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void addfriend(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;
    
    void addgroup(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void respondToFriendRequest(const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback) const; 

    void createGroups(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void getUserInfo(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void changeUserNickname(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void changeUserPassWord(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void getFriendList(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void getGroupUserList(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void changeGroupName(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;


    //根据用户名搜索群聊列表 
    void getGroupList(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void deleteFriend(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void deleteGroup(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;

    void uploadAvatar(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;    

    void getHistoryMessage(const HttpRequestPtr& req,  
    std::function<void (const HttpResponsePtr &)> &&callback) const;  
private:
  service::UserModel _userModel;
  service::FriendModel _friendModel;
  service::GroupModel _groupModel;


};
}




