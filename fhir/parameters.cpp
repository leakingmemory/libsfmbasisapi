//
// Created by jeo on 08.12.2023.
//

#include <fhir/parameters.h>
#include "json.h"

void FhirParameters::AddParameter(const std::string &name, const std::shared_ptr<Fhir> &parameter) {
    parameters.emplace_back(name, parameter);
}

void FhirParameters::AddParameter(const std::string &name, const std::shared_ptr<FhirValue> &parameter) {
    parameters.emplace_back(name, parameter);
}

void FhirParameters::AddParameter(const std::string &name, const std::vector<std::shared_ptr<FhirParameter>> &part) {
    parameters.emplace_back(name, part);
}

json FhirParameters::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    auto arr = nlohmann::json::array();
    decltype(parameters.size()) i = 0;
    for (const auto &parameter : parameters) {
        arr.push_back(parameter.ToJsonObj());
    }
    obj["resourceType"] = "Parameters";
    obj["parameter"] = arr;
    return obj;
}

FhirParameters FhirParameters::ParseObj(const json &obj) {
    FhirParameters parameters{};
    if (!parameters.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.contains("parameter")) {
        auto arr = obj["parameter"];
        if (arr.is_array()) {
            for (const auto &parameter: arr) {
                parameters.parameters.emplace_back(FhirParameter::Parse(parameter));
            }
        }
    }
    return parameters;
}

FhirParameters FhirParameters::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}