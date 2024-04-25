#include "User.h"
#include <vector>


namespace service
{
class FriendModel
{
public:
    // 添加好友关系
    void insert(int userid, int friendid);

    // 返回用户好友列表
    vector<User> query(int userid);


}
}