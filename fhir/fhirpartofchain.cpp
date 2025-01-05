//
// Created by sigsegv on 9/6/24.
//

#include <fhir/fhirpartofchain.h>

#include "../win32/w32strings.h"

void FhirPartOfChain::ToJsonInline(web::json::value &json) const {
    if (!partOf.empty()) {
        auto arr = web::json::value::array(partOf.size());
        auto i = 0;
        for (const auto &part: partOf) {
            arr[i++] = part.ToJson();
        }
        json[as_wstring_on_win32("partOf")] = arr;
    }
    if (!basedOn.empty()) {
        auto arr = web::json::value::array(basedOn.size());
        auto i = 0;
        for (const auto &part: basedOn) {
            arr[i++] = part.ToJson();
        }
        json[as_wstring_on_win32("basedOn")] = arr;
    }
}

void FhirPartOfChain::ParseInline(const web::json::value &json) {
    if (json.has_array_field(as_wstring_on_win32("partOf"))) {
        auto arr = json.at(as_wstring_on_win32("partOf")).as_array();
        for (const auto &item : arr) {
            if (item.is_object()) {
                auto ref = FhirReference::Parse(item);
                partOf.emplace_back(ref);
            }
        }
    }
    if (json.has_array_field(as_wstring_on_win32("basedOn"))) {
        auto arr = json.at(as_wstring_on_win32("basedOn")).as_array();
        for (const auto &item : arr) {
            if (item.is_object()) {
                auto ref = FhirReference::Parse(item);
                basedOn.emplace_back(ref);
            }
        }
    }
}
