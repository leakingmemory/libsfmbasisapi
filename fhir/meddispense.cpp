//
// Created by sigsegv on 3/24/25.
//

#include <fhir/meddispense.h>
#include "json.h"

json FhirMedicationDispense::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    obj["resourceType"] = "MedicationDispense";
    if (medicationReference.IsSet()) {
        auto ref = medicationReference.ToJsonObj();
        obj["medicationReference"] = static_cast<const nlohmann::json &>(ref);
    }
    if (subject.IsSet()) {
        auto ref = subject.ToJsonObj();
        obj["subject"] = static_cast<const nlohmann::json &>(ref);
    }
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &id : identifiers) {
            auto ident = id.ToJsonObj();
            arr.push_back(static_cast<const nlohmann::json &>(ident));
        }
        obj["identifier"] = arr;
    }
    if (!dosageInstruction.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &d : dosageInstruction) {
            auto dos = d.ToJsonObj();
            arr.push_back(static_cast<const nlohmann::json &>(dos));
        }
        obj["dosageInstruction"] = arr;
    }
    if (!authorizingPrescription.empty()) {
        auto arr = nlohmann::json::array();
        for (const auto &p : authorizingPrescription) {
            auto ref = p.ToJsonObj();
            arr.push_back(static_cast<const nlohmann::json &>(ref));
        }
        obj["authorizingPrescription"] = arr;
    }
    if (!performer.empty()) {
        auto performers = nlohmann::json::array();
        for (const auto &p : performer) {
            auto performer = nlohmann::json::object();
            if (p.actor.IsSet()) {
                auto actor = p.actor.ToJsonObj();
                performer["actor"] = static_cast<const nlohmann::json &>(actor);
            } else if (!p.function.IsSet()) {
                continue;
            }
            if (p.function.IsSet()) {
                auto func = p.function.ToJsonObj();
                performer["function"] = static_cast<const nlohmann::json &>(func);
            }
            performers.push_back(performer);
        }
        obj["performer"] = performers;
    }
    if (quantity.IsSet()) {
        auto quant = quantity.ToJsonObj();
        obj["quantity"] = static_cast<const nlohmann::json &>(quant);
    }
    if (!whenHandedOver.empty()) {
        obj["whenHandedOver"] = whenHandedOver;
    }
    return obj;
}

FhirMedicationDispense FhirMedicationDispense::ParseObj(const json &obj) {
    FhirMedicationDispense medDispense{};
    if (!medDispense.Fhir::ParseInline(obj)) {
        throw std::exception();
    }

    if (obj.contains("medicationReference")) {
        medDispense.medicationReference = FhirReference::ParseObj(obj["medicationReference"]);
    }
    if (obj.contains("subject")) {
        medDispense.subject = FhirReference::ParseObj(obj["subject"]);
    }
    if (obj.contains("identifier")) {
        const auto arr = obj["identifier"];
        for (const auto &id : arr) {
            medDispense.identifiers.push_back(FhirIdentifier::ParseObj(id));
        }
    }
    if (obj.contains("dosageInstruction")) {
        auto arr = obj["dosageInstruction"];
        for (const auto &d : arr) {
            medDispense.dosageInstruction.push_back(FhirDosage::ParseObj(d));
        }
    }
    if (obj.contains("authorizingPrescription")) {
        auto arr = obj["authorizingPrescription"];
        for (const auto &a : arr) {
            auto ref = FhirReference::ParseObj(a);
            medDispense.authorizingPrescription.emplace_back(std::move(ref));
        }
    }
    if (obj.contains("performer")) {
        auto arr = obj["performer"];
        for (const auto &p : arr) {
            FhirReference actor{};
            FhirCodeableConcept function{};
            if (p.contains("actor")) {
                actor = FhirReference::ParseObj(p["actor"]);
            }
            if (p.contains("function")) {
                function = FhirCodeableConcept::Parse(p["function"]);
            }
            FhirMedicationDispensePerformer performer{.actor = std::move(actor), .function = std::move(function)};
            if (!performer.actor.IsSet() && !performer.function.IsSet()) {
                continue;
            }
            medDispense.performer.emplace_back(std::move(performer));
        }
    }
    if (obj.contains("quantity")) {
        medDispense.quantity = FhirQuantity::ParseObj(obj["quantity"]);
    }
    if (obj.contains("whenHandedOver")) {
        medDispense.whenHandedOver = obj["whenHandedOver"];
    }
    return medDispense;
}

FhirMedicationDispense FhirMedicationDispense::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

std::string FhirMedicationDispense::GetDisplay() const {
    auto display = medicationReference.GetDisplay();
    if (!display.empty()) {
        return display;
    }
    return Fhir::GetDisplay();
}
