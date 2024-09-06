//
// Created by sigsegv on 1/13/24.
//

#include <fhir/fhirbasic.h>

web::json::value FhirBasic::ToJson() const {
    auto obj = Fhir::ToJson();
    obj["resourceType"] = web::json::value::string("Basic");
    if (subject.IsSet()) {
        obj["subject"] = subject.ToJson();
    }
    if (!identifiers.empty()) {
        auto arr = web::json::value::array(identifiers.size());
        typeof(identifiers.size()) i = 0;
        for (const auto &id : identifiers) {
            arr[i++] = id.ToJson();
        }
        obj["identifier"] = arr;
    }
    if (code.IsSet()) {
        obj["code"] = code.ToJson();
    }
    FhirPartOfChain::ToJsonInline(obj);
    return obj;
}

FhirBasic FhirBasic::Parse(const web::json::value &obj) {
    FhirBasic fhirBasic{};

    if (!fhirBasic.Fhir::ParseInline(obj)) {
        throw std::exception();
    }

    fhirBasic.FhirPartOfChain::ParseInline(obj);

    if (obj.has_field("subject")) {
        fhirBasic.subject = FhirReference::Parse(obj.at("subject"));
    }
    if (obj.has_field("identifier")) {
        const auto arr = obj.at("identifier").as_array();
        for (const auto &id : arr) {
            fhirBasic.identifiers.push_back(FhirIdentifier::Parse(id));
        }
    }
    if (obj.has_field("code")) {
        fhirBasic.code = FhirCodeableConcept::Parse(obj.at("code"));
    }

    return fhirBasic;
}
