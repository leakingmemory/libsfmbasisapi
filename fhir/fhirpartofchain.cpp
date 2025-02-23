//
// Created by sigsegv on 9/6/24.
//

#include <fhir/fhirpartofchain.h>
#include "json.h"

void FhirPartOfChain::ToJsonInline(json &json) const {
    if (!partOf.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &part: partOf) {
            arr.push_back(part.ToJsonObj());
        }
        json["partOf"] = arr;
    }
    if (!basedOn.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &part: basedOn) {
            arr.push_back(part.ToJsonObj());
        }
        json["basedOn"] = arr;
    }
}

void FhirPartOfChain::ParseInline(const json &json) {
    if (json.contains("partOf")) {
        auto arr = json["partOf"];
        if (arr.is_array()) {
            for (const auto &item: arr) {
                if (item.is_object()) {
                    auto ref = FhirReference::ParseObj(item);
                    partOf.emplace_back(ref);
                }
            }
        }
    }
    if (json.contains("basedOn")) {
        auto arr = json["basedOn"];
        if (arr.is_array()) {
            for (const auto &item: arr) {
                if (item.is_object()) {
                    auto ref = FhirReference::ParseObj(item);
                    basedOn.emplace_back(ref);
                }
            }
        }
    }
}
