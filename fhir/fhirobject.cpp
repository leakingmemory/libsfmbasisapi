//
// Created by sigsegv on 12/7/23.
//

#include <fhir/fhirobject.h>

void FhirObject::ToJsonInline(web::json::value &json) const {
}

web::json::value FhirObject::ToJson() const {
    auto json = web::json::value::object();
    ToJsonInline(json);
    return json;
}
