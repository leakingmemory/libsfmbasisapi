//
// Created by sigsegv on 12/7/23.
//

#ifndef SFMBASISFAKER_MEDSTATEMENT_H
#define SFMBASISFAKER_MEDSTATEMENT_H

#include "value.h"
#include "dosage.h"
#include "fhirpartofchain.h"

class FhirMedicationStatement : public Fhir, public FhirPartOfChain {
private:
    std::vector<FhirIdentifier> identifiers{};
    std::vector<FhirDosage> dosage{};
    FhirReference medicationReference{};
    FhirReference subject{};
    std::string effectiveDateTime{};
public:
    [[nodiscard]] web::json::value ToJson() const;
    static FhirMedicationStatement Parse(const web::json::value &obj);

    [[nodiscard]] std::vector<FhirIdentifier> GetIdentifiers() const { return identifiers; }
    [[nodiscard]] std::vector<FhirDosage> GetDosage() const { return dosage; }
    [[nodiscard]] FhirReference GetMedicationReference() const { return medicationReference; }
    [[nodiscard]] FhirReference GetSubject() const { return subject; }
    [[nodiscard]] std::string GetEffectiveDateTime() const { return effectiveDateTime; }

    void SetIdentifiers(const std::vector<FhirIdentifier> &identifiers) {
        this->identifiers = identifiers;
    }
    void AddIdentifier(const FhirIdentifier &identifier) {
        identifiers.emplace_back(identifier);
    }
    void AddDosage(const FhirDosage &dos) {
        dosage.emplace_back(dos);
    }
    void SetMedicationReference(const FhirReference &reference) {
        medicationReference = reference;
    }
    void SetSubject(const FhirReference &reference) {
        subject = reference;
    }
    void SetEffectiveDateTime(const std::string &dateTime) {
        effectiveDateTime = dateTime;
    }

    [[nodiscard]] std::string GetDisplay() const override;
};

#endif //SFMBASISFAKER_MEDSTATEMENT_H
