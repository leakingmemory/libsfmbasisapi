//
// Created by sigsegv on 12/8/23.
//

#include <fhir/medstatement.h>

#include "../win32/w32strings.h"

web::json::value FhirMedicationStatement::ToJson() const {
    auto obj = Fhir::ToJson();
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("MedicationStatement"));
    if (medicationReference.IsSet()) {
        obj[as_wstring_on_win32("medicationReference")] = medicationReference.ToJson();
    }
    if (subject.IsSet()) {
        obj[as_wstring_on_win32("subject")] = subject.ToJson();
    }
    if (!identifiers.empty()) {
        auto arr = web::json::value::array(identifiers.size());
#ifdef WIN32
        decltype(identifiers.size()) i = 0;
#else
        typeof(identifiers.size()) i = 0;
#endif
        for (const auto &id : identifiers) {
            arr[i++] = id.ToJson();
        }
        obj[as_wstring_on_win32("identifier")] = arr;
    }
    if (!dosage.empty()) {
        auto arr = web::json::value::array(dosage.size());
#ifdef WIN32
        decltype(dosage.size()) i = 0;
#else
        typeof(dosage.size()) i = 0;
#endif
        for (const auto &d : dosage) {
            arr[i++] = d.ToJson();
        }
        obj[as_wstring_on_win32("dosage")] = arr;
    }
    if (!effectiveDateTime.empty()) {
        obj[as_wstring_on_win32("effectiveDateTime")] = web::json::value::string(as_wstring_on_win32(effectiveDateTime));
    }
    FhirPartOfChain::ToJsonInline(obj);
    return obj;
}

FhirMedicationStatement FhirMedicationStatement::Parse(const web::json::value &obj) {
    FhirMedicationStatement medStatement{};

    if (!medStatement.Fhir::ParseInline(obj)) {
        throw std::exception();
    }

    medStatement.FhirPartOfChain::ParseInline(obj);

    if (obj.has_object_field(as_wstring_on_win32("medicationReference"))) {
        medStatement.medicationReference = FhirReference::Parse(obj.at(as_wstring_on_win32("medicationReference")));
    }
    if (obj.has_field(as_wstring_on_win32("subject"))) {
        medStatement.subject = FhirReference::Parse(obj.at(as_wstring_on_win32("subject")));
    }
    if (obj.has_field(as_wstring_on_win32("identifier"))) {
        const auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for (const auto &id : arr) {
            medStatement.identifiers.push_back(FhirIdentifier::Parse(id));
        }
    }
    if (obj.has_field(as_wstring_on_win32("dosage"))) {
        auto arr = obj.at(as_wstring_on_win32("dosage")).as_array();
        for (const auto &d : arr) {
            medStatement.dosage.push_back(FhirDosage::Parse(d));
        }
    }
    if (obj.has_string_field(as_wstring_on_win32("effectiveDateTime"))) {
        medStatement.effectiveDateTime = from_wstring_on_win32(obj.at(as_wstring_on_win32("effectiveDateTime")).as_string());
    }

    return medStatement;
}

std::string FhirMedicationStatement::GetDisplay() const {
    auto display = medicationReference.GetDisplay();
    if (!display.empty()) {
        return display;
    }
    return Fhir::GetDisplay();
}
