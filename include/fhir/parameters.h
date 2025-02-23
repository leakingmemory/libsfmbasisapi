//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_PARAMETERS_H
#define SFMBASISFAKER_PARAMETERS_H

#include "parameter.h"
#include "fhir.h"

class FhirParameters : public Fhir {
    friend Fhir;
private:
    std::vector<FhirParameter> parameters{};
public:
    [[nodiscard]] std::vector<FhirParameter> GetParameters() const {
        return parameters;
    }
    void AddParameter(const std::string &name, const std::shared_ptr<Fhir> &parameter);
    void AddParameter(const std::string &name, const std::shared_ptr<FhirValue> &parameter);
    void AddParameter(const std::string &name, const std::vector<std::shared_ptr<FhirParameter>> &part);
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirParameters ParseObj(const json &obj);
public:
    static FhirParameters ParseJson(const std::string &);
};

#endif //SFMBASISFAKER_PARAMETERS_H
