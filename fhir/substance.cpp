//
// Created by jeo on 08.12.2023.
//

#include <fhir/substance.h>
#include "json.h"

json FhirSubstance::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    obj["resourceType"] = "Substance";
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        decltype(identifiers.size()) i = 0;
        for (const auto &identifier : identifiers) {
            arr.push_back(identifier.ToJsonObj());
        }
        obj["identifier"] = arr;
    }
    if (code.IsSet()) {
        obj["code"] = code.ToJsonObj();
    }
    return obj;
}

FhirSubstance FhirSubstance::Parse(const json &obj) {
    FhirSubstance substance{};
    if (!substance.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.contains("identifier")) {
        auto arr = obj["identifier"];
        if (arr.is_array()) {
            for (const auto &val: arr) {
                substance.identifiers.emplace_back(FhirIdentifier::ParseObj(val));
            }
        }
    }
    if (obj.contains("code")) {
        substance.code = FhirCodeableConcept::Parse(obj["code"]);
    }
    return substance;
}