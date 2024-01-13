//
// Created by sigsegv on 1/13/24.
//

#include <fhir/allergy.h>

web::json::value FhirReaction::ToJson() const {
    web::json::value json = web::json::value::object();
    {
        auto manifestationArray = web::json::value::array();
        auto i = 0;
        for (const auto &m : manifestation) {
            if (m.IsSet()) {
                manifestationArray[i++] = m.ToJson();
            }
        }
        json["manifestation"] = manifestationArray;
    }
    return json;
}

FhirReaction FhirReaction::Parse(const web::json::value &obj) {
    FhirReaction reaction{};
    if (obj.has_array_field("manifestation")) {
        auto arr = obj.at("manifestation").as_array();
        for (const auto &v : arr) {
            reaction.manifestation.emplace_back(FhirCodeableConcept::Parse(v));
        }
    }
    return reaction;
}

web::json::value FhirAllergyIntolerance::ToJson() const {
    auto json = Fhir::ToJson();
    {
        auto arr = web::json::value::array();
        auto i = 0;
        for (const auto &v : identifier) {
            arr[i++] = v.ToJson();
        }
        json["identifier"] = arr;
    }
    {
        auto arr = web::json::value::array();
        auto i = 0;
        for (const auto &v : reaction) {
            arr[i++] = v.ToJson();
        }
        json["reaction"] = arr;
    }
    {
        auto arr = web::json::value::array();
        auto i = 0;
        for (const auto &v : category) {
            arr[i++] = web::json::value::string(v);
        }
        json["category"] = arr;
    }
    if (clinicalStatus.IsSet()) {
        json["clinicalStatus"] = clinicalStatus.ToJson();
    }
    if (code.IsSet()) {
        json["code"] = code.ToJson();
    }
    if (verificationStatus.IsSet()) {
        json["verificationStatus"] = verificationStatus.ToJson();
    }
    if (patient.IsSet()) {
        json["patient"] = patient.ToJson();
    }
    if (recorder.IsSet()) {
        json["recorder"] = recorder.ToJson();
    }
    if (!criticality.empty()) {
        json["criticality"] = web::json::value::string(criticality);
    }
    if (!recordedDate.empty()) {
        json["recordedDate"] = web::json::value::string(recordedDate);
    }
    return json;
}

FhirAllergyIntolerance FhirAllergyIntolerance::Parse(const web::json::value &obj) {
    FhirAllergyIntolerance allergyIntolerance{};
    if (!allergyIntolerance.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_array_field("identifier")) {
        auto arr = obj.at("identifier").as_array();
        for (const auto &v : arr) {
            allergyIntolerance.identifier.emplace_back(FhirIdentifier::Parse(v));
        }
    }
    if (obj.has_array_field("reaction")) {
        auto arr = obj.at("reaction").as_array();
        for (const auto &v : arr) {
            allergyIntolerance.reaction.emplace_back(FhirReaction::Parse(v));
        }
    }
    if (obj.has_array_field("category")) {
        auto arr = obj.at("category").as_array();
        for (const auto &v : arr) {
            allergyIntolerance.category.emplace_back(v.as_string());
        }
    }
    if (obj.has_object_field("clinicalStatus")) {
        allergyIntolerance.clinicalStatus = FhirCodeableConcept::Parse(obj.at("clinicalStatus"));
    }
    if (obj.has_object_field("code")) {
        allergyIntolerance.code = FhirCodeableConcept::Parse(obj.at("code"));
    }
    if (obj.has_object_field("verificationStatus")) {
        allergyIntolerance.verificationStatus = FhirCodeableConcept::Parse(obj.at("verificationStatus"));
    }
    if (obj.has_object_field("patient")) {
        allergyIntolerance.patient = FhirReference::Parse(obj.at("patient"));
    }
    if (obj.has_object_field("recorder")) {
        allergyIntolerance.recorder = FhirReference::Parse(obj.at("recorder"));
    }
    if (obj.has_string_field("criticality")) {
        allergyIntolerance.criticality = obj.at("criticality").as_string();
    }
    if (obj.has_string_field("recordedDate")) {
        allergyIntolerance.recordedDate = obj.at("recordedDate").as_string();
    }
    return allergyIntolerance;
}
