//
// Created by sigsegv on 12/7/23.
//

#ifndef SFMBASISFAKER_FHIROBJECT_H
#define SFMBASISFAKER_FHIROBJECT_H

#include <cpprest/json.h>

class FhirObject {
public:
    constexpr FhirObject() {}
    virtual ~FhirObject() = default;
    virtual void ToJsonInline(web::json::value &json) const;
    virtual web::json::value ToJson() const;
};

#endif //SFMBASISFAKER_FHIROBJECT_H
