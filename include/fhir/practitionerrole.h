//
// Created by sigsegv on 1/13/24.
//

#ifndef LIBSFMBASISAPI_PRACTITIONERROLE_H
#define LIBSFMBASISAPI_PRACTITIONERROLE_H

#include "fhir.h"
#include "value.h"
#include <vector>

class FhirPractitionerRole : public Fhir {
private:
    FhirReference practitioner;
    FhirReference organization;
    std::vector<FhirCodeableConcept> code;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirPractitionerRole() : Fhir("PractitionerRole"), practitioner(), organization(), code() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirPractitionerRole(const FhirReference &practitioner, const std::vector<FhirCodeableConcept> &code) : Fhir("PractitionerRole"), practitioner(practitioner), organization(), code(code) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirPractitionerRole(const FhirReference &practitioner, const FhirReference &organization, const std::vector<FhirCodeableConcept> &code) : Fhir("PractitionerRole"), practitioner(practitioner), organization(organization), code(code) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirPractitionerRole(FhirReference &&practitioner, std::vector<FhirCodeableConcept> &&code) : Fhir("PractitionerRole"), practitioner(std::move(practitioner)), organization(), code(std::move(code)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirPractitionerRole(FhirReference &&practitioner, FhirReference &&organization, std::vector<FhirCodeableConcept> &&code) : Fhir("PractitionerRole"), practitioner(std::move(practitioner)), organization(std::move(organization)), code(std::move(code)) {}
    web::json::value ToJson() const;
    static FhirPractitionerRole Parse(const web::json::value &obj);
};

#endif //LIBSFMBASISAPI_PRACTITIONERROLE_H
