#pragma once

#include <mutex>
#include <unordered_map>

#include <drogon/WebSocketConnection.h>


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

    void addUserToMap(int userId, const drogon::WebSocketConnectionPtr& conn) {
        //std::lock_guard<std::mutex> lock(mutex_);
       //groupMembers_[groupId].insert(conn);
        userMembers_[userId].insert(conn);
    }

    void removeUserFromMap(int userId, const drogon::WebSocketConnectionPtr& conn) {
        //std::lock_guard<std::mutex> lock(mutex_);
        auto it = userMembers_.find(userId);
        if (it != userMembers_.end()) {
            it->second.erase(conn);
            if (it->second.empty()) {
                userMembers_.erase(it);
            }
        }
    }

    void broadcastMessageToUser(int userId, const std::string& message) {
        //std::lock_guard<std::mutex> lock(mutex_);
        auto it = userMembers_.find(userId);
        if (it != userMembers_.end()) {
            for (const auto& member : it->second) {
                member->send(message);
            }
        }
    }
                
    std::unordered_map<int, std::unordered_set<drogon::WebSocketConnectionPtr>> getUserMembers() const {
        //std::unique_lock<std::mutex> lock(mutex_);
        return userMembers_;
    }


private:
    std::unordered_map<int,std::unordered_set<drogon::WebSocketConnectionPtr>> userMembers_;
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
