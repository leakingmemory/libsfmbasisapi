//
// Created by jeo on 08.12.2023.
//

#include <fhir/parameter.h>
#include <fhir/fhir.h>
#include "json.h"

json FhirParameter::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    obj["name"] = name;
    if (resource) {
        obj["resource"] = resource->ToJsonObj();
    }
    if (value) {
        obj[value->GetPropertyName()] = value->ToJsonObj();
    }
    if (!part.empty()) {
        auto arr = nlohmann::json::array();
        int i = 0;
        for (const auto &p : part) {
            arr.push_back(p->ToJsonObj());
        }
        obj["part"] = arr;
    }
    return obj;
}

FhirParameter FhirParameter::Parse(const json &obj) {
    FhirParameter parameter{};
    for (const auto &prop : obj.items()) {
        auto key = prop.key();
        if (key == "name") {
            parameter.name = prop.value();
        } else if (key == "resource") {
            parameter.resource = Fhir::ParseObj(prop.value());
        } else if (key.starts_with("value")) {
            parameter.value = FhirValue::ParseObj(key, prop.value());
        } else if (key == "part") {
            for (const auto &part : prop.value()) {
                std::shared_ptr<FhirParameter> p = std::make_shared<FhirParameter>(FhirParameter::Parse(part));
                parameter.part.emplace_back(p);
            }
        } else {
            throw std::exception();
        }
    }
    return parameter;
}