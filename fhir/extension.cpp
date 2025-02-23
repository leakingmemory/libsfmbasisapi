//
// Created by sigsegv on 12/7/23.
//

#include <fhir/extension.h>
#include <fhir/fhir.h>
#include "json.h"

void FhirExtension::ToJsonInline(json &json) const {
    FhirExtendable::ToJsonInline(json);
    if (!url.empty()) {
        json["url"] = url;
    }
}

json FhirExtension::ToJsonObj() const {
    return FhirExtendable::ToJsonObj();
}

std::string FhirExtension::ToJson() const {
    return FhirExtendable::ToJson();
}

std::shared_ptr<FhirExtension> FhirExtension::ParseObj(const json &obj) {
    auto genericJson = nlohmann::json::parse(obj.dump());
    std::string url{};
    if (obj.contains("url")) {
        url = obj["url"];
        bool generic{false};
        std::string valueProperty{};
        nlohmann::json value{};
        for (const auto &child : obj.items()) {
            auto first = child.key();
            if (first == "url") {
                continue;
            }
            if (first == "extension") {
                continue;
            }
            if (!valueProperty.empty() || !first.starts_with("value")) {
                generic = true;
                break;
            }
            valueProperty = first;
            value = child.value();
        }
        if (!generic && !valueProperty.empty()) {
            return std::make_shared<FhirValueExtension>(url, FhirValue::ParseObj(valueProperty, value));
        }
        genericJson.erase("url");
    }
    if (genericJson.contains("extension")) {
        genericJson.erase("extension");
    }
    auto ext = std::make_shared<FhirGenericExtension>(url, obj.dump());
    ext->ParseInline(obj);
    return ext;
}

std::shared_ptr<FhirExtension> FhirExtension::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}
