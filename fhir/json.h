//
// Created by sigsegv on 2/22/25.
//

#ifndef LIBSFMBASISAPI_JSON_H
#define LIBSFMBASISAPI_JSON_H

#include <nlohmann/json.hpp>

struct json;

class json_strindex {
private:
    nlohmann::json &js;
    std::string idx;
public:
    json_strindex(nlohmann::json &js, const std::string &idx) : js(js), idx(idx) {}
    template <class T> json_strindex &operator = (const T &cp) {
        js[idx] = cp;
        return *this;
    }
    template <class T> json_strindex &operator = (T &&mv) {
        js[idx] = std::move(mv);
        return *this;
    }
    json_strindex &operator =(const json &cp);
    json_strindex &operator =(json &&mv);
    operator nlohmann::json &() {
        return js[idx];
    }
};

struct json : public nlohmann::json {
    json() = default;
    json(const nlohmann::json &cp) : nlohmann::json(cp) {}
    json(nlohmann::json &&mv) : nlohmann::json(std::move(mv)) {}
    json &operator = (const nlohmann::json &js) {
        nlohmann::json::operator =(js);
        return *this;
    }
    json &operator = (nlohmann::json &&js) {
        nlohmann::json::operator =(std::move(js));
        return *this;
    }
    json_strindex operator [] (const std::string &str) {
        return {*this, str};
    }
    auto operator [] (const std::string &str) const {
        return nlohmann::json::operator [] (str);
    }
    json_strindex operator [] (const char *str) {
        return {*this, std::string(str)};
    }
    auto operator [] (const char *str) const {
        return nlohmann::json::operator [] (str);
    }
};

#endif //LIBSFMBASISAPI_JSON_H
