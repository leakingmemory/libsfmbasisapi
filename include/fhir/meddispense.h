//
// Created by sigsegv on 3/20/25.
//

#ifndef LIBSFMBASISAPI_MEDDISPENSE_H
#define LIBSFMBASISAPI_MEDDISPENSE_H

#include "fhir.h"
#include "value.h"
#include "dosage.h"
#include <vector>

class Fhir;

struct FhirMedicationDispensePerformer {
    FhirReference actor;
    FhirCodeableConcept function;
};

class FhirMedicationDispense : public Fhir {
    friend Fhir;
private:
    std::vector<FhirReference> authorizingPrescription{};
    std::vector<FhirDosage> dosageInstruction{};
    std::vector<FhirMedicationDispensePerformer> performer{};
    std::vector<FhirIdentifier> identifiers{};
    FhirReference medicationReference{};
    FhirReference subject{};
    FhirQuantity quantity{};
    std::string whenHandedOver{};
public:
    // Getter and Setter for authorizingPrescription
    [[nodiscard]] std::vector<FhirReference> GetAuthorizingPrescription() const {
        return authorizingPrescription;
    }

    void SetAuthorizingPrescription(const std::vector<FhirReference> &prescriptions) {
        authorizingPrescription = prescriptions;
    }

    void AddAuthorizingPrescription(const FhirReference &prescription) {
        authorizingPrescription.emplace_back(prescription);
    }

    // Getter and Setter for dosageInstruction
    [[nodiscard]] std::vector<FhirDosage> GetDosageInstruction() const {
        return dosageInstruction;
    }

    void SetDosageInstruction(const std::vector<FhirDosage> &dosages) {
        dosageInstruction = dosages;
    }

    void AddDosageInstruction(const FhirDosage &dosage) {
        dosageInstruction.emplace_back(dosage);
    }

    // Getter and Setter for performer
    [[nodiscard]] std::vector<FhirMedicationDispensePerformer> GetPerformer() const {
        return performer;
    }

    void SetPerformer(const std::vector<FhirMedicationDispensePerformer> &performers) {
        performer = performers;
    }

    void AddPerformer(const FhirMedicationDispensePerformer &performerInstance) {
        performer.emplace_back(performerInstance);
    }

    // Getter and Setter for identifiers
    [[nodiscard]] std::vector<FhirIdentifier> GetIdentifiers() const {
        return identifiers;
    }

    void SetIdentifiers(const std::vector<FhirIdentifier> &ids) {
        identifiers = ids;
    }

    void AddIdentifier(const FhirIdentifier &id) {
        identifiers.emplace_back(id);
    }

    // Getter and Setter for medicationReference
    [[nodiscard]] FhirReference GetMedicationReference() const {
        return medicationReference;
    }

    void SetMedicationReference(const FhirReference &medicationRef) {
        medicationReference = medicationRef;
    }

    // Getter and Setter for subject
    [[nodiscard]] FhirReference GetSubject() const {
        return subject;
    }

    void SetSubject(const FhirReference &subj) {
        subject = subj;
    }

    // Getter and Setter for quantity
    [[nodiscard]] FhirQuantity GetQuantity() const {
        return quantity;
    }

    void SetQuantity(const FhirQuantity &qty) {
        quantity = qty;
    }

    // Getter and Setter for whenHandedOver
    [[nodiscard]] std::string GetWhenHandedOver() const {
        return whenHandedOver;
    }

    void SetWhenHandedOver(const std::string &when) {
        whenHandedOver = when;
    }

protected:
    json ToJsonObj() const;
    static FhirMedicationDispense ParseObj(const json &obj);
public:
    static FhirMedicationDispense ParseJson(const std::string &);
    std::string GetDisplay() const override;
};

#endif //LIBSFMBASISAPI_MEDDISPENSE_H
