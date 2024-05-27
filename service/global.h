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

    void addUserToMap(int id,int toid, const drogon::WebSocketConnectionPtr& conn) {
        std::lock_guard<std::mutex> lock(mutex_);
       //groupMembers_[groupId].insert(conn);
        userMembers_[id][toid] = conn;
    }

    void removeUserFromMap(int userId,int toid, const drogon::WebSocketConnectionPtr& conn) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = userMembers_.find(userId);
        if (it != userMembers_.end()) {
            auto& userConnections = it->second;
            auto connIt = userConnections.find(toid);
            if (connIt != userConnections.end()) {
                userConnections.erase(connIt);
                if (userConnections.empty()) {
                    userMembers_.erase(it);
                }
            }
        }
    }

    void broadcastMessageToUser(int id,int toid, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it_to = userMembers_.find(toid);

        if (it_to != userMembers_.end() ) {
            for(auto &conn : it_to->second){
                if(conn.first == id)
                {
                    conn.second->send(message);
                }
                else
                {
                    LOG_INFO<<"用户不存在";
                }
            }  
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

                
    std::unordered_map<int, std::unordered_map<int,drogon::WebSocketConnectionPtr>> getUserMembers() const {
        //std::unique_lock<std::mutex> lock(mutex_);
        return userMembers_;
    }


private:
    std::unordered_map<int,std::unordered_map<int,drogon::WebSocketConnectionPtr>> userMembers_;
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
