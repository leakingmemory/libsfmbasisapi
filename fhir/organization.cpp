//
// Created by jeo on 08.12.2023.
//

#include <fhir/organization.h>

#include "../win32/w32strings.h"

web::json::value FhirOrganization::ToJson() const {
    auto obj = Fhir::ToJson();
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("Organization"));
    if (!identifiers.empty()) {
        auto arr = web::json::value::array(identifiers.size());
#ifdef WIN32
        decltype(identifiers.size()) i = 0;
#else
        typeof(identifiers.size()) i = 0;
#endif
        for (const auto &identifier : identifiers) {
            arr[i++] = identifier.ToJson();
        }
        obj[as_wstring_on_win32("identifier")] = arr;
    }
    if (!name.empty()) {
        obj[as_wstring_on_win32("name")] = web::json::value::string(as_wstring_on_win32(name));
    }
    return obj;
}

FhirOrganization FhirOrganization::Parse(const web::json::value &obj) {
    FhirOrganization org{};
    if (!org.ParseInline(obj)) {
        throw std::exception();
    }

    if (obj.has_string_field(as_wstring_on_win32("name"))) {
        org.name = from_wstring_on_win32(obj.at(as_wstring_on_win32("name")).as_string());
    }
    if (obj.has_array_field(as_wstring_on_win32("identifier"))){
        auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for (const auto &identifier : arr) {
            org.identifiers.push_back(FhirIdentifier::Parse(identifier));
        }
    }
    return org;
}

std::string FhirOrganization::GetDisplay() const {
    for (const auto &id : identifiers) {
        if (id.GetUse() == "official" && id.GetSystem() == "urn:oid:2.16.578.1.12.4.1.2") {
            std::string display{"HER: "};
            display.append(id.GetValue());
            return display;
        }
    }
    return Fhir::GetDisplay();
}
