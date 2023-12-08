//
// Created by sigsegv on 09.01.2021.
//

#ifndef ELECTRIC_CORSFILTER_H
#define ELECTRIC_CORSFILTER_H

#include "WebServer.h"

template <typename T> pplx::task<T> completed_task(T t) {
    return pplx::create_task<>([t] () -> T {
        return t;
    });
}

template <typename... Args> class CorsFilter : public WebFilter<web::http::http_request &, Args...> {
private:
    std::vector<std::string> originHosts;
public:
    CorsFilter(std::vector<std::string> originHosts) : originHosts(originHosts) {}

    std::optional<pplx::task<web::http::http_response>> filter(std::function<std::optional<pplx::task<web::http::http_response>> (web::http::http_request &, Args...)> next, const std::vector<std::string> &path, const std::map<std::string,std::string> &query, web::http::http_request &request, Args... args) override {
        auto &headers = request.headers();
        auto originHeader = headers.find("origin");
        if (originHeader != headers.end()) {
            std::string origin{originHeader->second};
            std::string originHost{origin};
            if (originHost.starts_with("https://")) {
                originHost = originHost.substr(8);
            } else if (originHost.starts_with("http://")) {
                originHost = originHost.substr(7);
            }
            if (std::find(originHosts.begin(), originHosts.end(), originHost) != originHosts.end()) {
                if (request.method() == web::http::methods::GET) {
                    std::optional<pplx::task<web::http::http_response>> opt_response = next(request, args...);
                    if (opt_response) {
                        pplx::task<web::http::http_response> response_task{
                            opt_response.value().then([origin] (web::http::http_response response) {
                                response.headers()["Access-Control-Allow-Origin"] = origin;
                                return response;
                            })
                        };
                        return { response_task };
                    } else {
                        return { };
                    }
                } else {
                    web::json::value json = web::json::value::object();
                    json["error"] = web::json::value("CORS rejected");
                    web::http::http_response response{web::http::status_codes::Forbidden};
                    response.set_body(json);
                    return { completed_task(response) };
                }
            } else {
                web::json::value json = web::json::value::object();
                json["error"] = web::json::value("CORS rejected");
                web::http::http_response response{web::http::status_codes::Forbidden};
                response.set_body(json);
                return { completed_task(response) };
            }
        } else {
            return next(request, args...);
        }
    }
};

#endif //ELECTRIC_CORSFILTER_H
