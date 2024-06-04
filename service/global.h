#pragma once

#include <mutex>
#include <unordered_map>

#include <drogon/WebSocketConnection.h>
#include <drogon/drogon.h>
#include "../service/global.h"
#include "../service/UserModel.h"
#include "../models/Users.h"
#include "../models/Friends.h"
#include "../models/Groupuser.h"
#include "../models/Allgroup.h"
#include "../models/Offlinemessages.h"

//    std::unordered_map<int,std::shared_ptr<drogon::WebSocketConnection>> userConnMap_;

namespace global{

//std::unordered_map<int,std::shared_ptr<drogon::WebSocketConnection>> userConnMap_;



class UserChatManager
{
public:
    static UserChatManager& getInstance() {
        static UserChatManager instance;
        return instance;
    }

    void addUserToMap(int id, const drogon::WebSocketConnectionPtr& conn) {
        std::lock_guard<std::mutex> lock(mutex_);
       //groupMembers_[groupId].insert(conn);
       if(userMembers_.find(id) != userMembers_.end()) 
       {
            userMembers_[id]=conn;
       }
      else
      {
        userMembers_.insert(std::make_pair(id,conn));
      }
    }

    void removeUserFromMap(int userId, const drogon::WebSocketConnectionPtr& conn) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = userMembers_.find(userId);
        if (it != userMembers_.end()) {
            userMembers_.erase(it);
        }
        else
        {
            LOG_INFO<<"该用户已断开连接";
        }
        
    }

    drogon::WebSocketConnectionPtr getUserConnection(int userId) {
        std::lock_guard<std::mutex> lock(mutex_);
        if(userMembers_.find(userId) != userMembers_.end()) {
            return userMembers_[userId];
        }
        return nullptr;
    }
    
    int getUserIdFromWebSocket(const drogon::WebSocketConnectionPtr& conn)
    {
        auto userMembers = global::UserChatManager::getInstance().getUserMembers();
        for (const auto& pair : userMembers) {
        if (pair.second == conn) {
            return pair.first;
        }
        }
        return -1; // 或者其他表示未找到的值
    }

    void broadcastMessageToUser(int id,int toid, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto userConn = userMembers_.find(toid);

        if (userConn != userMembers_.end() ) {
            userConn->second->send(message);
            LOG_INFO<<"send message success";
        }
        else
        {
            saveOfflineMessage(id, toid, message);
        }
    }


    void saveOfflineMessage(int id,int toid, const std::string& message)
    {
        try
        {
            /* code */
            auto clientDb=drogon::app().getDbClient();
            auto res = clientDb->execSqlSync("insert into offlinemessages(id,from_id,message) values(?,?,?)",toid,id,message);
        }
        catch(const std::exception& e)
        {
            LOG_ERROR<<"数据库连接失败";
            return ;
        }
    }

                
    std::unordered_map<int,drogon::WebSocketConnectionPtr> getUserMembers() const {
        //std::unique_lock<std::mutex> lock(mutex_);
        return userMembers_;
    }


private:
    std::unordered_map<int,drogon::WebSocketConnectionPtr> userMembers_;
    std::mutex mutex_;

    UserChatManager() = default;
    ~UserChatManager() = default;
    UserChatManager(const UserChatManager&) = delete;
    UserChatManager& operator=(const UserChatManager&) = delete;
};




class GroupChatManager {
public:
    static GroupChatManager& getInstance() {
        static GroupChatManager instance;
        return instance;
    }

    void addUserToGroup(int groupId, const drogon::WebSocketConnectionPtr& conn) {
        //std::lock_guard<std::mutex> lock(mutex_);
        groupMembers_[groupId].insert(conn);
    }

    void removeUserFromGroup(int groupId, const drogon::WebSocketConnectionPtr& conn) {
        //std::lock_guard<std::mutex> lock(mutex_);
        auto it = groupMembers_.find(groupId);
        if (it != groupMembers_.end()) {
            it->second.erase(conn);
            if (it->second.empty()) {
                groupMembers_.erase(it);
            }
        }
    }

    void broadcastMessageToGroup(int groupId, const std::string& message) {
        //std::lock_guard<std::mutex> lock(mutex_);
        auto it = groupMembers_.find(groupId);
        if (it != groupMembers_.end()) {
            for (const auto& member : it->second) {
                member->send(message);
            }
        }
    }


    std::unordered_map<int, std::unordered_set<drogon::WebSocketConnectionPtr>> getGroupMembers() const {
        //std::unique_lock<std::mutex> lock(mutex_);
        return groupMembers_;
    }

private:
    std::unordered_map<int, std::unordered_set<drogon::WebSocketConnectionPtr>> groupMembers_;
    std::mutex mutex_;

    GroupChatManager() = default;
    ~GroupChatManager() = default;
    GroupChatManager(const GroupChatManager&) = delete;
    GroupChatManager& operator=(const GroupChatManager&) = delete;
};


}
