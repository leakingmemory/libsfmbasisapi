//
// Created by jeo on 08.12.2023.
//

#include <fhir/bundleentry.h>
#include <fhir/fhir.h>
#include <fhir/value.h>
#include "json.h"

json FhirBundleEntry::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (!fullUrl.empty()) {
        obj["fullUrl"] = fullUrl;
    }
    if (resource) {
        auto res = resource->ToJsonObj();
        obj["resource"] = static_cast<const nlohmann::json &>(res);
    }
    return obj;
}

FhirBundleEntry FhirBundleEntry::Parse(const json &obj) {
    FhirBundleEntry entry{};
    if (obj.contains("fullUrl")) {
        entry.fullUrl = obj["fullUrl"];
    }
    if (obj.contains("resource")) {
        entry.resource = Fhir::ParseObj(obj["resource"]);
    }
    return entry;
}

FhirReference FhirBundleEntry::CreateReference(const std::string &type) const {
    return {fullUrl, type, resource ? resource->GetDisplay() : "Display"};
}