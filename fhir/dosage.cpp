//
// Created by sigsegv on 12/8/23.
//

#include <fhir/dosage.h>
#include "json.h"

json FhirDosage::ToJsonObj() const {
    auto obj = FhirExtendable::ToJsonObj();
    obj["sequence"] = sequence;
    obj["text"] = text;
    return obj;
}

FhirDosage FhirDosage::ParseObj(const json &obj) {
    FhirDosage dosage{};
    if (!dosage.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.contains("sequence")) {
        dosage.sequence = obj["sequence"];
    }
    if (obj.contains("text")) {
        dosage.text = obj["text"];
    }
    return dosage;
}

FhirDosage FhirDosage::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}