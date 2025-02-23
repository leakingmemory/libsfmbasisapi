//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_PARAMETER_H
#define SFMBASISFAKER_PARAMETER_H

#include "fhirobject.h"
#include <vector>
#include <memory>

class Fhir;
class FhirValue;
class FhirParameters;

class FhirParameter : public FhirObject {
    friend FhirParameters;
private:
    std::shared_ptr<Fhir> resource;
    std::shared_ptr<FhirValue> value;
    std::vector<std::shared_ptr<FhirParameter>> part;
    std::string name;
public:
    FhirParameter() : resource(), value(), part(), name() {}
    FhirParameter(const std::string &name, const std::shared_ptr<Fhir> &resource) : resource(resource), value(), part(), name(name) {}
    FhirParameter(const std::string &name, const std::shared_ptr<FhirValue> &value) : resource(), value(value), part(), name(name) {}
    FhirParameter(const std::string &name, const std::vector<std::shared_ptr<FhirParameter>> &part) : resource(), value(), part(part), name(name) {}
    [[nodiscard]] std::shared_ptr<Fhir> GetResource() const { return resource; }
    [[nodiscard]] std::shared_ptr<FhirValue> GetFhirValue() const { return value; }
    [[nodiscard]] std::vector<std::shared_ptr<FhirParameter>> GetPart() const { return part; }
    [[nodiscard]] std::string GetName() const { return name; }
protected:
    [[nodiscard]] json ToJsonObj() const;
    static FhirParameter Parse(const json &obj);
};

#endif //SFMBASISFAKER_PARAMETER_H