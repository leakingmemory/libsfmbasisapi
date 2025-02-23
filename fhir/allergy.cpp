//
// Created by sigsegv on 1/13/24.
//

#include <fhir/allergy.h>
#include "json.h"

json FhirReaction::ToJsonObj() const {
    json json{};
    {
        auto manifestationArray = nlohmann::json::array();
        for (const auto &m : manifestation) {
            if (m.IsSet()) {
                manifestationArray.push_back(m.ToJsonObj());
            }
        }
        json["manifestation"] = manifestationArray;
    }
    return json;
}

FhirReaction FhirReaction::Parse(const json &obj) {
    FhirReaction reaction{};
    if (obj.contains("manifestation")) {
        auto arr = obj["manifestation"];
        if (arr.is_array()) {
            for (const auto &v: arr) {
                reaction.manifestation.emplace_back(FhirCodeableConcept::Parse(v));
            }
        }
    }
    return reaction;
}

json FhirAllergyIntolerance::ToJsonObj() const {
    auto json = Fhir::ToJsonObj();
    {
        auto arr = nlohmann::json::array();
        for (const auto &v : identifier) {
            arr.push_back(v.ToJsonObj());
        }
        json["identifier"] = arr;
    }
    {
        auto arr = nlohmann::json::array();
        for (const auto &v : reaction) {
            arr.push_back(v.ToJsonObj());
        }
        json["reaction"] = arr;
    }
    {
        auto arr = nlohmann::json::array();
        for (const auto &v : category) {
            arr.push_back(v);
        }
        json["category"] = arr;
    }
    if (clinicalStatus.IsSet()) {
        json["clinicalStatus"] = clinicalStatus.ToJsonObj();
    }
    if (code.IsSet()) {
        json["code"] = code.ToJsonObj();
    }
    if (verificationStatus.IsSet()) {
        json["verificationStatus"] = verificationStatus.ToJsonObj();
    }
    if (patient.IsSet()) {
        json["patient"] = patient.ToJsonObj();
    }
    if (recorder.IsSet()) {
        json["recorder"] = recorder.ToJsonObj();
    }
    if (!criticality.empty()) {
        json["criticality"] = criticality;
    }
    if (!recordedDate.empty()) {
        json["recordedDate"] = recordedDate;
    }
    return json;
}

FhirAllergyIntolerance FhirAllergyIntolerance::Parse(const json &obj) {
    FhirAllergyIntolerance allergyIntolerance{};
    if (!allergyIntolerance.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.contains("identifier")) {
        auto arr = obj["identifier"];
        if (arr.is_array()) {
            for (const auto &v: arr) {
                allergyIntolerance.identifier.emplace_back(FhirIdentifier::ParseObj(v));
            }
        }
    }
    if (obj.contains("reaction")) {
        auto arr = obj["reaction"];
        if (arr.is_array()) {
            for (const auto &v: arr) {
                allergyIntolerance.reaction.emplace_back(FhirReaction::Parse(v));
            }
        }
    }
    if (obj.contains("category")) {
        auto arr = obj["category"];
        if (arr.is_array()) {
            for (const auto &v: arr) {
                allergyIntolerance.category.emplace_back(v);
            }
        }
    }
    if (obj.contains("clinicalStatus")) {
        allergyIntolerance.clinicalStatus = FhirCodeableConcept::Parse(obj["clinicalStatus"]);
    }
    if (obj.contains("code")) {
        allergyIntolerance.code = FhirCodeableConcept::Parse(obj["code"]);
    }
    if (obj.contains("verificationStatus")) {
        allergyIntolerance.verificationStatus = FhirCodeableConcept::Parse(obj["verificationStatus"]);
    }
    if (obj.contains("patient")) {
        allergyIntolerance.patient = FhirReference::ParseObj(obj["patient"]);
    }
    if (obj.contains("recorder")) {
        allergyIntolerance.recorder = FhirReference::ParseObj(obj["recorder"]);
    }
    if (obj.contains("criticality")) {
        allergyIntolerance.criticality = obj["criticality"];
    }
    if (obj.contains("recordedDate")) {
        allergyIntolerance.recordedDate = obj["recordedDate"];
    }
    return allergyIntolerance;
}
