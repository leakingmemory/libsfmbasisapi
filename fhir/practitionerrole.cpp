//
// Created by sigsegv on 1/13/24.
//

#include <fhir/practitionerrole.h>

#include "../win32/w32strings.h"

web::json::value FhirPractitionerRole::ToJson() const {
    auto json = Fhir::ToJson();
    if (practitioner.IsSet()) {
        json[as_wstring_on_win32("practitioner")] = practitioner.ToJson();
    }
    if (organization.IsSet()) {
        json[as_wstring_on_win32("organization")] = organization.ToJson();
    }
    auto codeArray = web::json::value::array();
    auto i = 0;
    for (const auto &codeable : code) {
        codeArray[i++] = codeable.ToJson();
    }
    json[as_wstring_on_win32("code")] = codeArray;
    return json;
}

FhirPractitionerRole FhirPractitionerRole::Parse(const web::json::value &obj) {
    std::vector<FhirCodeableConcept> codes{};
    if (obj.has_array_field(as_wstring_on_win32("code"))) {
        auto code = obj.at(as_wstring_on_win32("code")).as_array();
        for (const auto &item : code) {
            auto codeable = FhirCodeableConcept::Parse(item);
            if (codeable.IsSet()) {
                codes.emplace_back(codeable);
            }
        }
    }
    FhirReference practitioner{};
    if (obj.has_object_field(as_wstring_on_win32("practitioner"))) {
        auto reference = FhirReference::Parse(obj.at(as_wstring_on_win32("practitioner")));
        if (reference.IsSet()) {
            practitioner = reference;
        }
    }
    FhirReference organization{};
    if (obj.has_object_field(as_wstring_on_win32("organization"))) {
        auto reference = FhirReference::Parse(obj.at(as_wstring_on_win32("organization")));
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