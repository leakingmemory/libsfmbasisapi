//
// Created by jeo on 08.12.2023.
//

#include <fhir/substance.h>

#include "../win32/w32strings.h"

web::json::value FhirSubstance::ToJson() const {
    auto obj = Fhir::ToJson();
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("Substance"));
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
    if (code.IsSet()) {
        obj[as_wstring_on_win32("code")] = code.ToJson();
    }
    return obj;
}

FhirSubstance FhirSubstance::Parse(const web::json::value &obj) {
    FhirSubstance substance{};
    if (!substance.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_field(as_wstring_on_win32("identifier"))) {
        auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for (const auto &val : arr) {
            substance.identifiers.emplace_back(FhirIdentifier::Parse(val));
        }
    }
    if (obj.has_field(as_wstring_on_win32("code"))) {
        substance.code = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("code")));
    }
    return substance;
}