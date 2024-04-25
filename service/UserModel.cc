#include "User.h"
#include <common/Response.h>
#include <models/Users.h>
#include <drogon/drogon.h>

using namespace drogon::orm;
using model_User = drogon_model::db::Users;

common::Response 
    service::User::login(std::string &account,
                        std::string &password) 
{
    auto clientDb=app().getDbClient();
    Mapper<Users> mapper(clientDb);

    auto userInDb = 
            mapper.findOne({Users::Cols::_username,user.getValueOfUsername()});
    
    
    if(userInDb.getValueOfPassword() != user.getValueOfPassword())
    {
        throw std::runtime_error("密码错误");
    }
    Criteria criteria("account",CompareOperator::EQ,account);
    std::vector<model_User> userList =mp.findAll();
    std::cout << userList.size() << "rows!" << std::endl;


    if (!cliPtr){
    return common::Response(300,"ok");
    }

    return common::Response(200,"ok");
}


common::Response 
    register(std::string &account,
            std::string &password,
            std::string nickname)
{


}

/*


    auto userInDb = 
            mapper.findOne({Users::Cols::_username,user.getValueOfUsername()});

    
   
    

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);

*/