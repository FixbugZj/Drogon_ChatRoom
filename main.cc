#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
using namespace drogon;

int main() {
    //Set HTTP listener address and port
    //drogon::app().addListener("192.168.205.134", 8000);
    //Load config file
    app().setExceptionHandler(
        [](const std::exception &e,
        const HttpRequestPtr&req,
        std::function<void(const HttpResponsePtr &)>&&callback)
        {   
            Json::Value json;
            
            if(typeid(e)==typeid(std::invalid_argument)|| 
            typeid(e)==typeid(std::runtime_error))
            {
                json["error"] = e.what();
            }

            if(typeid(e)==typeid(orm::UnexpectedRows))
            {
                
                json["error"] = "用户名错误。main";
                
            }

            auto resp = HttpResponse::newHttpJsonResponse(json);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
        }
    );

    drogon::app().loadConfigFile("./config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();

    return 0;
}
