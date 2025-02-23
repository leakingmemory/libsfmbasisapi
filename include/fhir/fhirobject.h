//
// Created by sigsegv on 12/7/23.
//

#ifndef SFMBASISFAKER_FHIROBJECT_H
#define SFMBASISFAKER_FHIROBJECT_H

#include <string>

struct json;
class FhirParameter;
class FhirValueExtension;

class FhirObject {
    friend FhirParameter;
    friend FhirValueExtension;
public:
    constexpr FhirObject() {}
    virtual ~FhirObject() = default;
protected:
    virtual void ToJsonInline(json &json) const;
    virtual json ToJsonObj() const;
public:
    [[nodiscard]] virtual std::string ToJson() const;
};

#endif //SFMBASISFAKER_FHIROBJECT_H
