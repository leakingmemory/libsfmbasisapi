//
// Created by sigsegv on 12/8/23.
//

#include <fhir/medstatement.h>
#include "json.h"

json FhirMedicationStatement::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    obj["resourceType"] = "MedicationStatement";
    if (medicationReference.IsSet()) {
        obj["medicationReference"] = medicationReference.ToJsonObj();
    }
    if (subject.IsSet()) {
        obj["subject"] = subject.ToJsonObj();
    }
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        decltype(identifiers.size()) i = 0;
        for (const auto &id : identifiers) {
            arr.push_back(id.ToJsonObj());
        }
        obj["identifier"] = arr;
    }
    if (!dosage.empty()) {
        auto arr = nlohmann::json::array();
        decltype(dosage.size()) i = 0;
        for (const auto &d : dosage) {
            arr.push_back(d.ToJsonObj());
        }
        obj["dosage"] = arr;
    }
    if (!effectiveDateTime.empty()) {
        obj["effectiveDateTime"] = effectiveDateTime;
    }
    FhirPartOfChain::ToJsonInline(obj);
    return obj;
}

FhirMedicationStatement FhirMedicationStatement::ParseObj(const json &obj) {
    FhirMedicationStatement medStatement{};

    if (!medStatement.Fhir::ParseInline(obj)) {
        throw std::exception();
    }

    medStatement.FhirPartOfChain::ParseInline(obj);

    if (obj.contains("medicationReference")) {
        medStatement.medicationReference = FhirReference::ParseObj(obj["medicationReference"]);
    }
    if (obj.contains("subject")) {
        medStatement.subject = FhirReference::ParseObj(obj["subject"]);
    }
    if (obj.contains("identifier")) {
        const auto arr = obj["identifier"];
        for (const auto &id : arr) {
            medStatement.identifiers.push_back(FhirIdentifier::ParseObj(id));
        }
    }
    if (obj.contains("dosage")) {
        auto arr = obj["dosage"];
        for (const auto &d : arr) {
            medStatement.dosage.push_back(FhirDosage::ParseObj(d));
        }
    }
    if (obj.contains("effectiveDateTime")) {
        medStatement.effectiveDateTime = obj["effectiveDateTime"];
    }

    return medStatement;
}

FhirMedicationStatement FhirMedicationStatement::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

std::string FhirMedicationStatement::GetDisplay() const {
    auto display = medicationReference.GetDisplay();
    if (!display.empty()) {
        return display;
    }
    return Fhir::GetDisplay();
}
