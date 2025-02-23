//
// Created by sigsegv on 1/13/24.
//

#include <fhir/fhirbasic.h>
#include "json.h"

json FhirBasic::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    obj["resourceType"] = "Basic";
    if (subject.IsSet()) {
        obj["subject"] = subject.ToJsonObj();
    }
    if (author.IsSet()) {
        obj["author"] = author.ToJsonObj();
    }
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &id : identifiers) {
            arr.push_back(id.ToJsonObj());
        }
        obj["identifier"] = arr;
    }
    if (code.IsSet()) {
        obj["code"] = code.ToJsonObj();
    }
    FhirPartOfChain::ToJsonInline(obj);
    return obj;
}

FhirBasic FhirBasic::Parse(const json &obj) {
    FhirBasic fhirBasic{};

    if (!fhirBasic.Fhir::ParseInline(obj)) {
        throw std::exception();
    }

    fhirBasic.FhirPartOfChain::ParseInline(obj);

    if (obj.contains("subject")) {
        fhirBasic.subject = FhirReference::ParseObj(obj["subject"]);
    }
    if (obj.contains("author")) {
        fhirBasic.author = FhirReference::ParseObj(obj["author"]);
    }
    if (obj.contains("identifier")) {
        const auto arr = obj["identifier"];
        if (arr.is_array()) {
            for (const auto &id: arr) {
                fhirBasic.identifiers.push_back(FhirIdentifier::ParseObj(id));
            }
        }
    }
    if (obj.contains("code")) {
        fhirBasic.code = FhirCodeableConcept::Parse(obj["code"]);
    }

    return fhirBasic;
}
