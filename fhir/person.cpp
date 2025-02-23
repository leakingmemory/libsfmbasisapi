//
// Created by jeo on 08.12.2023.
//

#include <fhir/person.h>
#include "json.h"

json FhirPerson::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        decltype(identifiers.size()) i = 0;
        for (const auto &identifier : identifiers) {
            arr.push_back(identifier.ToJsonObj());
        }
        obj["identifier"] = arr;
    }
    obj["active"] = active;
    if (!name.empty()) {
        auto arr = nlohmann::json::array();
        decltype(name.size()) i = 0;
        for (const auto &n : name) {
            arr.push_back(n.ToJsonObj());
        }
        obj["name"] = arr;
    }
    if (!gender.empty()) {
        obj["gender"] = gender;
    }
    if (!birthDate.empty()) {
        obj["birthDate"] = birthDate;
    }
    if (!address.empty()) {
        auto arr = nlohmann::json::array();
        decltype(address.size()) i = 0;
        for (const auto &a : address) {
            arr.push_back(a.ToJsonObj());
        }
        obj["address"] = arr;
    }
    return obj;
}

FhirPerson FhirPerson::Parse(const json &obj) {
    FhirPerson practitioner{};

    if (!practitioner.ParseInline(obj)) {
        throw std::exception();
    }

    if(obj.contains("identifier")) {
        auto arr = obj["identifier"];
        if (arr.is_array()) {
            for (const auto &identifierVal: arr) {
                practitioner.identifiers.push_back(FhirIdentifier::ParseObj(identifierVal));
            }
        }
    }

    if(obj.contains("active")) {
        practitioner.active = obj["active"];
    }

    if(obj.contains("name")) {
        for (const auto &n : obj["name"]) {
            practitioner.name.emplace_back(FhirName::ParseObj(n));
        }
    }

    if(obj.contains("gender")) {
        practitioner.gender = obj["gender"];
    }

    if(obj.contains("birthDate")) {
        practitioner.birthDate = obj["birthDate"];
    }

    if (obj.contains("address")) {
        for (const auto &a : obj["address"]) {
            practitioner.address.push_back(FhirAddress::Parse(a));
        }
    }

    return practitioner;
}

std::string FhirPerson::GetDisplay() const {
    std::string display{};
    for (const auto &n : name) {
        display = n.GetDisplay();
        if (!display.empty()) {
            for (const auto &id : identifiers) {
                if (id.GetUse() == "official" && id.GetSystem() == "urn:oid:2.16.578.1.12.4.1.4.4") {
                    display.append(", HPR: ");
                    display.append(id.GetValue());
                    break;
                }
            }
            return display;
        }
    }
    for (const auto &id : identifiers) {
        if (id.GetUse() == "official" && id.GetSystem() == "urn:oid:2.16.578.1.12.4.1.4.4") {
            display.append("HPR: ");
            display.append(id.GetValue());
            break;
        }
    }
    return display;
}
