//
// Created by sigsegv on 12/7/23.
//

#include <fhir/fhirextendable.h>
#include <fhir/extension.h>

#include "../win32/w32strings.h"

bool FhirExtendable::ParseInline(const web::json::value &json) {
    if (json.has_array_field(as_wstring_on_win32("extension"))) {
        for (const auto &ext : json.at(as_wstring_on_win32("extension")).as_array()) {
            extensions.emplace_back(FhirExtension::Parse(ext));
        }
    }
    return true;
}

void FhirExtendable::ToJsonInline(web::json::value &json) const {
    FhirObject::ToJsonInline(json);
    if (!extensions.empty()) {
        auto arr = web::json::value::array(extensions.size());
#ifdef WIN32
        decltype(extensions.size()) i = 0;
#else
        typeof(extensions.size()) i = 0;
#endif
        for (const auto &ext : extensions) {
            arr[i++] = ext->ToJson();
        }
        json[as_wstring_on_win32("extension")] = arr;
    }
}

web::json::value FhirExtendable::ToJson() const {
    return FhirObject::ToJson();
}
