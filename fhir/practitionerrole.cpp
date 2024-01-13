//
// Created by sigsegv on 1/13/24.
//

#include <fhir/practitionerrole.h>

web::json::value FhirPractitionerRole::ToJson() const {
    auto json = Fhir::ToJson();
    if (practitioner.IsSet()) {
        json["practitioner"] = practitioner.ToJson();
    }
    auto codeArray = web::json::value::array();
    auto i = 0;
    for (const auto &codeable : code) {
        codeArray[i++] = codeable.ToJson();
    }
    json["code"] = codeArray;
    return json;
}

FhirPractitionerRole FhirPractitionerRole::Parse(const web::json::value &obj) {
    std::vector<FhirCodeableConcept> codes{};
    if (obj.has_array_field("code")) {
        auto code = obj.at("code").as_array();
        for (const auto &item : code) {
            auto codeable = FhirCodeableConcept::Parse(item);
            if (codeable.IsSet()) {
                codes.emplace_back(codeable);
            }
        }
    }
    FhirReference practitioner{};
    if (obj.has_object_field("practitioner")) {
        auto reference = FhirReference::Parse(obj.at("practitioner"));
        if (reference.IsSet()) {
            practitioner = reference;
        }
    }
    FhirPractitionerRole practitionerRole{std::move(practitioner), std::move(codes)};
    if (!practitionerRole.ParseInline(obj)) {
        throw std::exception();
    }
    return practitionerRole;
}