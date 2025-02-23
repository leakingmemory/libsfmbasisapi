//
// Created by sigsegv on 12/7/23.
//

#include <fhir/fhirextendable.h>
#include <fhir/extension.h>
#include "json.h"

bool FhirExtendable::ParseInline(const json &json) {
    if (json.contains("extension")) {
        auto extensionArr = json["extension"];
        if (extensionArr.is_array()) {
            for (const auto &ext: extensionArr) {
                extensions.emplace_back(FhirExtension::ParseObj(ext));
            }
        }
    }
    return true;
}

void FhirExtendable::ToJsonInline(json &json) const {
    FhirObject::ToJsonInline(json);
    if (!extensions.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &ext : extensions) {
            arr.push_back(ext->ToJsonObj());
        }
        json["extension"] = arr;
    }
}

json FhirExtendable::ToJsonObj() const {
    return FhirObject::ToJsonObj();
}

std::string FhirExtendable::ToJson() const {
    return FhirObject::ToJson();
}
