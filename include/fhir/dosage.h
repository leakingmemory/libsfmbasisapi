//
// Created by sigsegv on 12/8/23.
//

#ifndef SFMBASISFAKER_DOSAGE_H
#define SFMBASISFAKER_DOSAGE_H

#include "fhirextendable.h"

class FhirMedicationStatement;

class FhirDosage : public FhirExtendable {
    friend FhirMedicationStatement;
private:
    std::string text;
    int sequence;
public:
    FhirDosage() : text(""), sequence(0) {}
    explicit FhirDosage(const std::string& text, int sequence)
        : text(text), sequence(sequence) {}

    std::string GetText() const { return text; }
    int GetSequence() const { return sequence; }

protected:
    json ToJsonObj() const;
    static FhirDosage ParseObj(const json &obj);
public:
    static FhirDosage ParseJson(const std::string &);
};

#endif //SFMBASISFAKER_DOSAGE_H
