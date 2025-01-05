//
// Created by jeo on 08.12.2023.
//

#include <fhir/parameters.h>

#include "../win32/w32strings.h"

void FhirParameters::AddParameter(const std::string &name, const std::shared_ptr<Fhir> &parameter) {
    parameters.emplace_back(name, parameter);
}

void FhirParameters::AddParameter(const std::string &name, const std::shared_ptr<FhirValue> &parameter) {
    parameters.emplace_back(name, parameter);
}

void FhirParameters::AddParameter(const std::string &name, const std::vector<std::shared_ptr<FhirParameter>> &part) {
    parameters.emplace_back(name, part);
}

web::json::value FhirParameters::ToJson() const {
    auto obj = Fhir::ToJson();
    auto arr = web::json::value::array(parameters.size());
#ifdef WIN32
    decltype(parameters.size()) i = 0;
#else
    typeof(parameters.size()) i = 0;
#endif
    for (const auto &parameter : parameters) {
        arr[i++] = parameter.ToJson();
    }
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("Parameters"));
    obj[as_wstring_on_win32("parameter")] = arr;
    return obj;
}

FhirParameters FhirParameters::Parse(const web::json::value &obj) {
    FhirParameters parameters{};
    if (!parameters.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_array_field(as_wstring_on_win32("parameter"))) {
        for (const auto &parameter : obj.at(as_wstring_on_win32("parameter")).as_array()) {
            parameters.parameters.emplace_back(FhirParameter::Parse(parameter));
        }
    }
    return parameters;
}