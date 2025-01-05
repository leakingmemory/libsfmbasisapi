//
// Created by jeo on 08.12.2023.
//

#include <fhir/bundleentry.h>
#include <fhir/fhir.h>
#include <fhir/value.h>

#include "../win32/w32strings.h"

web::json::value FhirBundleEntry::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (!fullUrl.empty()) {
        obj[as_wstring_on_win32("fullUrl")] = web::json::value::string(as_wstring_on_win32(fullUrl));
    }
    if (resource) {
        obj[as_wstring_on_win32("resource")] = resource->ToJson();
    }
    return obj;
}

FhirBundleEntry FhirBundleEntry::Parse(const web::json::value &obj) {
    FhirBundleEntry entry{};
    if (obj.has_string_field(as_wstring_on_win32("fullUrl"))) {
        entry.fullUrl = from_wstring_on_win32(obj.at(as_wstring_on_win32("fullUrl")).as_string());
    }
    if (obj.has_object_field(as_wstring_on_win32("resource"))) {
        entry.resource = Fhir::Parse(obj.at(as_wstring_on_win32("resource")));
    }
    return entry;
}

FhirReference FhirBundleEntry::CreateReference(const std::string &type) const {
    return {fullUrl, type, resource ? resource->GetDisplay() : "Display"};
}