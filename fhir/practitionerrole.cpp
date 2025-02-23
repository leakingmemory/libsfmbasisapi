//
// Created by sigsegv on 1/13/24.
//

#include <fhir/practitionerrole.h>
#include "json.h"

json FhirPractitionerRole::ToJsonObj() const {
    auto json = Fhir::ToJsonObj();
    if (practitioner.IsSet()) {
        json["practitioner"] = practitioner.ToJsonObj();
    }
    if (organization.IsSet()) {
        json["organization"] = organization.ToJsonObj();
    }
    auto codeArray = nlohmann::json::array();
    for (const auto &codeable : code) {
        codeArray.push_back(codeable.ToJsonObj());
    }
    json["code"] = codeArray;
    return json;
}

FhirPractitionerRole FhirPractitionerRole::Parse(const json &obj) {
    std::vector<FhirCodeableConcept> codes{};
    if (obj.contains("code")) {
        auto code = obj["code"];
        if (code.is_array()) {
            for (const auto &item: code) {
                auto codeable = FhirCodeableConcept::Parse(item);
                if (codeable.IsSet()) {
                    codes.emplace_back(codeable);
                }
            }
        }
    }
    FhirReference practitioner{};
    if (obj.contains("practitioner")) {
        auto reference = FhirReference::ParseObj(obj["practitioner"]);
        if (reference.IsSet()) {
            practitioner = reference;
        }
    }
    FhirReference organization{};
    if (obj.contains("organization")) {
        auto reference = FhirReference::ParseObj(obj["organization"]);
        if (reference.IsSet()) {
            organization = reference;
        }
    }
    FhirPractitionerRole practitionerRole{std::move(practitioner), std::move(organization), std::move(codes)};
    if (!practitionerRole.ParseInline(obj)) {
        throw std::exception();
    }
    return practitionerRole;
}