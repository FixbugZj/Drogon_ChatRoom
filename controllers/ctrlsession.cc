#include "ctrlsession.h"

// Add definition of your processing function here
void ctrlsession::setSession(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto username = req->getParameter("username");
    auto password = req->getParameter("password");

    auto session = req->getSession();
    // if(username =="admin123" && password =="123456")
    // {
    //     session->insert("role",std::string("admin"));

    // }
    // else if()
    // {

    // }
    // else
    // {
    //     session->insert("role",std::string("visitor"));
    // }

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);
}


void ctrlsession::getSession(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    auto session = req->getSession();
    auto role = session->get<std::string>("role");

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);
}


void ctrlsession::removeSession(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)const
{
    auto session = req->getSession();
    session->erase("role");

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);

    
}
