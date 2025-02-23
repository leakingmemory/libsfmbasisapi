//
// Created by sigsegv on 2/22/25.
//

#include "json.h"

json_strindex &json_strindex::operator =(const json &cp)  {
    js[idx] = static_cast<const nlohmann::json &>(cp);
    return *this;
}
json_strindex &json_strindex::operator =(json &&mv) {
    js[idx] = static_cast<nlohmann::json &&>(mv);
    return *this;
}
