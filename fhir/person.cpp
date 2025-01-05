//
// Created by jeo on 08.12.2023.
//

#include <fhir/person.h>

#include "../win32/w32strings.h"

web::json::value FhirPerson::ToJson() const {
    auto obj = Fhir::ToJson();
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
    obj[as_wstring_on_win32("active")] = web::json::value::boolean(active);
    if (!name.empty()) {
        auto arr = web::json::value::array(name.size());
#ifdef WIN32
        decltype(name.size()) i = 0;
#else
        typeof(name.size()) i = 0;
#endif
        for (const auto &n : name) {
            arr[i++] = n.ToJson();
        }
        obj[as_wstring_on_win32("name")] = arr;
    }
    if (!gender.empty()) {
        obj[as_wstring_on_win32("gender")] = web::json::value::string(as_wstring_on_win32(gender));
    }
    if (!birthDate.empty()) {
        obj[as_wstring_on_win32("birthDate")] = web::json::value::string(as_wstring_on_win32(birthDate));
    }
    if (!address.empty()) {
        auto arr = web::json::value::array(address.size());
#ifdef WIN32
        decltype(address.size()) i = 0;
#else
        typeof(address.size()) i = 0;
#endif
        for (const auto &a : address) {
            arr[i++] = a.ToJson();
        }
        obj[as_wstring_on_win32("address")] = arr;
    }
    return obj;
}

FhirPerson FhirPerson::Parse(const web::json::value &obj) {
    FhirPerson practitioner{};

    if (!practitioner.ParseInline(obj)) {
        throw std::exception();
    }

    if(obj.has_array_field(as_wstring_on_win32("identifier"))) {
        auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for(const auto &identifierVal : arr) {
            practitioner.identifiers.push_back(FhirIdentifier::Parse(identifierVal));
        }
    }

    if(obj.has_boolean_field(as_wstring_on_win32("active"))) {
        practitioner.active = obj.at(as_wstring_on_win32("active")).as_bool();
    }

    if(obj.has_array_field(as_wstring_on_win32("name"))) {
        for (const auto &n : obj.at(as_wstring_on_win32("name")).as_array()) {
            practitioner.name.emplace_back(FhirName::Parse(n));
        }
    }

    if(obj.has_string_field(as_wstring_on_win32("gender"))) {
        practitioner.gender = from_wstring_on_win32(obj.at(as_wstring_on_win32("gender")).as_string());
    }

    if(obj.has_string_field(as_wstring_on_win32("birthDate"))) {
        practitioner.birthDate = from_wstring_on_win32(obj.at(as_wstring_on_win32("birthDate")).as_string());
    }

    if (obj.has_array_field(as_wstring_on_win32("address"))) {
        for (const auto &a : obj.at(as_wstring_on_win32("address")).as_array()) {
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
