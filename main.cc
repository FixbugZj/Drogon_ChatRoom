#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <signal.h>
#include <./service/UserModel.h>
using namespace drogon;



void resetHandler(int)
{
  service::UserModel().resetState();
  exit(0);
}


int main() {
  // Set HTTP listener address and port
  
  // Load config file
  

  drogon::app().loadConfigFile("./config.json");
  // Cors
  // 设置 CORS 头
    drogon::app().registerHandler("/", [](const drogon::HttpRequestPtr& req, 
                                             std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->addHeader("Access-Control-Allow-Origin", "*"); // 允许所有来源的请求
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS"); // 允许的 HTTP 方法
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, Content-Length, Host, Connection"); // 允许的请求头
        callback(resp);
    });


    



    drogon::app().registerPostHandlingAdvice([](const HttpRequestPtr &,
      const drogon::HttpResponsePtr &resp)
      {
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS"); // 允许的 HTTP 方法
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, Content-Length, Host, Connection"); // 允许的请求头
        
      });

  // Run HTTP framework,the method will block in the internal event loop
  signal(SIGINT,resetHandler);
  drogon::app().run();

  return 0;
}



