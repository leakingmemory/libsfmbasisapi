//
// Created by sigsegv on 1/13/24.
//

#include <fhir/allergy.h>

#include "../win32/w32strings.h"

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
        json[as_wstring_on_win32("manifestation")] = manifestationArray;
    }
    return json;
}

FhirReaction FhirReaction::Parse(const web::json::value &obj) {
    FhirReaction reaction{};
    if (obj.has_array_field(as_wstring_on_win32("manifestation"))) {
        auto arr = obj.at(as_wstring_on_win32("manifestation")).as_array();
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
        json[as_wstring_on_win32("identifier")] = arr;
    }
    {
        auto arr = web::json::value::array();
        auto i = 0;
        for (const auto &v : reaction) {
            arr[i++] = v.ToJson();
        }
        json[as_wstring_on_win32("reaction")] = arr;
    }
    {
        auto arr = web::json::value::array();
        auto i = 0;
        for (const auto &v : category) {
            arr[i++] = web::json::value::string(as_wstring_on_win32(v));
        }
        json[as_wstring_on_win32("category")] = arr;
    }
    if (clinicalStatus.IsSet()) {
        json[as_wstring_on_win32("clinicalStatus")] = clinicalStatus.ToJson();
    }
    if (code.IsSet()) {
        json[as_wstring_on_win32("code")] = code.ToJson();
    }
    if (verificationStatus.IsSet()) {
        json[as_wstring_on_win32("verificationStatus")] = verificationStatus.ToJson();
    }
    if (patient.IsSet()) {
        json[as_wstring_on_win32("patient")] = patient.ToJson();
    }
    if (recorder.IsSet()) {
        json[as_wstring_on_win32("recorder")] = recorder.ToJson();
    }
    if (!criticality.empty()) {
        json[as_wstring_on_win32("criticality")] = web::json::value::string(as_wstring_on_win32(criticality));
    }
    if (!recordedDate.empty()) {
        json[as_wstring_on_win32("recordedDate")] = web::json::value::string(as_wstring_on_win32(recordedDate));
    }
    return json;
}

FhirAllergyIntolerance FhirAllergyIntolerance::Parse(const web::json::value &obj) {
    FhirAllergyIntolerance allergyIntolerance{};
    if (!allergyIntolerance.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_array_field(as_wstring_on_win32("identifier"))) {
        auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for (const auto &v : arr) {
            allergyIntolerance.identifier.emplace_back(FhirIdentifier::Parse(v));
        }
    }
    if (obj.has_array_field(as_wstring_on_win32("reaction"))) {
        auto arr = obj.at(as_wstring_on_win32("reaction")).as_array();
        for (const auto &v : arr) {
            allergyIntolerance.reaction.emplace_back(FhirReaction::Parse(v));
        }
    }
    if (obj.has_array_field(as_wstring_on_win32("category"))) {
        auto arr = obj.at(as_wstring_on_win32("category")).as_array();
        for (const auto &v : arr) {
            allergyIntolerance.category.emplace_back(from_wstring_on_win32(v.as_string()));
        }
    }
    if (obj.has_object_field(as_wstring_on_win32("clinicalStatus"))) {
        allergyIntolerance.clinicalStatus = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("clinicalStatus")));
    }
    if (obj.has_object_field(as_wstring_on_win32("code"))) {
        allergyIntolerance.code = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("code")));
    }
    if (obj.has_object_field(as_wstring_on_win32("verificationStatus"))) {
        allergyIntolerance.verificationStatus = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("verificationStatus")));
    }
    if (obj.has_object_field(as_wstring_on_win32("patient"))) {
        allergyIntolerance.patient = FhirReference::Parse(obj.at(as_wstring_on_win32("patient")));
    }
    if (obj.has_object_field(as_wstring_on_win32("recorder"))) {
        allergyIntolerance.recorder = FhirReference::Parse(obj.at(as_wstring_on_win32("recorder")));
    }
    if (obj.has_string_field(as_wstring_on_win32("criticality"))) {
        allergyIntolerance.criticality = from_wstring_on_win32(obj.at(as_wstring_on_win32("criticality")).as_string());
    }
    if (obj.has_string_field(as_wstring_on_win32("recordedDate"))) {
        allergyIntolerance.recordedDate = from_wstring_on_win32(obj.at(as_wstring_on_win32("recordedDate")).as_string());
    }
    return allergyIntolerance;
}
