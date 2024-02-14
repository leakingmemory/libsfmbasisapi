//
// Created by sigsegv on 12/7/23.
//

#include <fhir/extension.h>
#include <fhir/fhir.h>

void FhirExtension::ToJsonInline(web::json::value &json) const {
    FhirExtendable::ToJsonInline(json);
    if (!url.empty()) {
        json["url"] = web::json::value::string(url);
    }
}

web::json::value FhirExtension::ToJson() const {
    return FhirExtendable::ToJson();
}

std::shared_ptr<FhirExtension> FhirExtension::Parse(const web::json::value &obj) {
    web::json::value genericJson = web::json::value::parse(obj.serialize());
    std::string url{};
    if (obj.has_string_field("url")) {
        url = obj.at("url").as_string();
        bool generic{false};
        std::string valueProperty{};
        web::json::value value{};
        for (const auto &child : obj.as_object()) {
            if (child.first == "url") {
                continue;
            }
            if (!valueProperty.empty() || !child.first.starts_with("value")) {
                generic = true;
                break;
            }
            valueProperty = child.first;
            value = child.second;
        }
        if (!generic && !valueProperty.empty()) {
            return std::make_shared<FhirValueExtension>(url, FhirValue::Parse(valueProperty, value));
        }
        genericJson.erase("url");
    }
    if (genericJson.has_field("extension")) {
        genericJson.erase("extension");
    }
    auto ext = std::make_shared<FhirGenericExtension>(url, genericJson);
    ext->ParseInline(obj);
    return ext;
}
