//
// Created by sigsegv on 12/7/23.
//

#include <fhir/extension.h>
#include <fhir/fhir.h>

#include "../win32/w32strings.h"

void FhirExtension::ToJsonInline(web::json::value &json) const {
    FhirExtendable::ToJsonInline(json);
    if (!url.empty()) {
        json[as_wstring_on_win32("url")] = web::json::value::string(as_wstring_on_win32(url));
    }
}

web::json::value FhirExtension::ToJson() const {
    return FhirExtendable::ToJson();
}

std::shared_ptr<FhirExtension> FhirExtension::Parse(const web::json::value &obj) {
    web::json::value genericJson = web::json::value::parse(obj.serialize());
    std::string url{};
    if (obj.has_string_field(as_wstring_on_win32("url"))) {
        url = from_wstring_on_win32(obj.at(as_wstring_on_win32("url")).as_string());
        bool generic{false};
        std::string valueProperty{};
        web::json::value value{};
        for (const auto &child : obj.as_object()) {
            auto first = from_wstring_on_win32(child.first);
            if (first == "url") {
                continue;
            }
            if (!valueProperty.empty() || !first.starts_with("value")) {
                generic = true;
                break;
            }
            valueProperty = first;
            value = child.second;
        }
        if (!generic && !valueProperty.empty()) {
            return std::make_shared<FhirValueExtension>(url, FhirValue::Parse(valueProperty, value));
        }
        genericJson.erase(as_wstring_on_win32("url"));
    }
    if (genericJson.has_field(as_wstring_on_win32("extension"))) {
        genericJson.erase(as_wstring_on_win32("extension"));
    }
    auto ext = std::make_shared<FhirGenericExtension>(url, genericJson);
    ext->ParseInline(obj);
    return ext;
}
