//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_ORGANIZATION_H
#define SFMBASISFAKER_ORGANIZATION_H

#include "value.h"
#include "fhir.h"

class FhirOrganization : public Fhir {
    friend Fhir;
private:
    std::vector<FhirIdentifier> identifiers{};
    std::string name{};
public:
    [[nodiscard]] std::vector<FhirIdentifier> GetIdentifiers() const {
        return identifiers;
    }
    void SetIdentifiers(const std::vector<FhirIdentifier> &newIdentifiers) {
        identifiers = newIdentifiers;
    }
    [[nodiscard]] std::string GetName() const {
        return name;
    }
    void SetName(const std::string &n) {
        name = n;
    }
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirOrganization Parse(const json &obj);
public:
    std::string GetDisplay() const override;
};

#endif //SFMBASISFAKER_ORGANIZATION_H
