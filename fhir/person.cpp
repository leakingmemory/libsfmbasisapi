//
// Created by jeo on 08.12.2023.
//

#include <fhir/person.h>

web::json::value FhirPerson::ToJson() const {
    auto obj = Fhir::ToJson();
    if (!identifiers.empty()) {
        auto arr = web::json::value::array(identifiers.size());
        typeof(identifiers.size()) i = 0;
        for (const auto &identifier : identifiers) {
            arr[i++] = identifier.ToJson();
        }
        obj["identifier"] = arr;
    }
    obj["active"] = web::json::value::boolean(active);
    if (!name.empty()) {
        auto arr = web::json::value::array(name.size());
        typeof(name.size()) i = 0;
        for (const auto &n : name) {
            arr[i++] = n.ToJson();
        }
        obj["name"] = arr;
    }
    if (!gender.empty()) {
        obj["gender"] = web::json::value::string(gender);
    }
    if (!birthDate.empty()) {
        obj["birthDate"] = web::json::value::string(birthDate);
    }
    if (!address.empty()) {
        auto arr = web::json::value::array(address.size());
        typeof(address.size()) i = 0;
        for (const auto &a : address) {
            arr[i++] = a.ToJson();
        }
        obj["address"] = arr;
    }
    return obj;
}

FhirPerson FhirPerson::Parse(const web::json::value &obj) {
    FhirPerson practitioner{};

    if (!practitioner.ParseInline(obj)) {
        throw std::exception();
    }

    if(obj.has_array_field("identifier")) {
        auto arr = obj.at("identifier").as_array();
        for(const auto &identifierVal : arr) {
            practitioner.identifiers.push_back(FhirIdentifier::Parse(identifierVal));
        }
    }

    if(obj.has_boolean_field("active")) {
        practitioner.active = obj.at("active").as_bool();
    }

    if(obj.has_array_field("name")) {
        for (const auto &n : obj.at("name").as_array()) {
            practitioner.name.emplace_back(FhirName::Parse(n));
        }
    }

    if(obj.has_string_field("gender")) {
        practitioner.gender = obj.at("gender").as_string();
    }

    if(obj.has_string_field("birthDate")) {
        practitioner.birthDate = obj.at("birthDate").as_string();
    }

    if (obj.has_array_field("address")) {
        for (const auto &a : obj.at("address").as_array()) {
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
