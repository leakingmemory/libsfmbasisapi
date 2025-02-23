//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_SUBSTANCE_H
#define SFMBASISFAKER_SUBSTANCE_H

#include "fhir.h"
#include "value.h"

class FhirSubstance : public Fhir {
    friend Fhir;
private:
    std::vector<FhirIdentifier> identifiers{};
    FhirCodeableConcept code{};
public:
    [[nodiscard]] std::vector<FhirIdentifier> getIdentifiers() const {
        return identifiers;
    }

    [[nodiscard]] FhirCodeableConcept getCode() const {
        return code;
    }
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirSubstance Parse(const json &obj);
};

#endif //SFMBASISFAKER_SUBSTANCE_H