//
// Created by jeo on 08.12.2023.
//

#include <fhir/parameter.h>
#include <fhir/fhir.h>

web::json::value FhirParameter::ToJson() const {
    auto obj = FhirObject::ToJson();
    obj["name"] = web::json::value::string(name);
    if (resource) {
        obj["resource"] = resource->ToJson();
    }
    if (value) {
        obj[value->GetPropertyName()] = value->ToJson();
    }
    if (!part.empty()) {
        auto arr = web::json::value::array();
        int i = 0;
        for (const auto &p : part) {
            arr[i++] = p->ToJson();
        }
        obj["part"] = arr;
    }
    return obj;
}

FhirParameter FhirParameter::Parse(const web::json::value &obj) {
    FhirParameter parameter{};
    for (const auto &prop : obj.as_object()) {
        const auto &key = prop.first;
        if (key == "name") {
            parameter.name = prop.second.as_string();
        } else if (key == "resource") {
            parameter.resource = Fhir::Parse(prop.second);
        } else if (key.starts_with("value")) {
            parameter.value = FhirValue::Parse(key, prop.second);
        } else if (key == "part") {
            for (const auto &part : prop.second.as_array()) {
                std::shared_ptr<FhirParameter> p = std::make_shared<FhirParameter>(FhirParameter::Parse(part));
                parameter.part.emplace_back(p);
            }
        } else {
            throw std::exception();
        }
    }
    return parameter;
}