//
// Created by jeo on 08.12.2023.
//

#include <fhir/organization.h>
#include "json.h"

json FhirOrganization::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    obj["resourceType"] = "Organization";
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        decltype(identifiers.size()) i = 0;
        for (const auto &identifier : identifiers) {
            arr.push_back(identifier.ToJsonObj());
        }
        obj["identifier"] = arr;
    }
    if (!name.empty()) {
        obj["name"] = name;
    }
    return obj;
}

FhirOrganization FhirOrganization::Parse(const json &obj) {
    FhirOrganization org{};
    if (!org.ParseInline(obj)) {
        throw std::exception();
    }

    if (obj.contains("name")) {
        org.name = obj["name"];
    }
    if (obj.contains("identifier")) {
        auto arr = obj["identifier"];
        if (arr.is_array()) {
            for (const auto &identifier: arr) {
                org.identifiers.push_back(FhirIdentifier::ParseObj(identifier));
            }
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
