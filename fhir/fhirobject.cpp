//
// Created by sigsegv on 12/7/23.
//

#include <fhir/fhirobject.h>
#include "json.h"

void FhirObject::ToJsonInline(json &json) const {
}

json FhirObject::ToJsonObj() const {
    json json{};
    ToJsonInline(json);
    return json;
}

std::string FhirObject::ToJson() const {
    return ToJsonObj().dump();
}
