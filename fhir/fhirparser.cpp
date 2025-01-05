//
// Created by jeo on 08.12.2023.
//

#include <fhir/fhir.h>
#include <fhir/medication.h>
#include <fhir/medstatement.h>
#include <fhir/composition.h>
#include <fhir/person.h>
#include <fhir/organization.h>
#include <fhir/substance.h>
#include <fhir/bundle.h>
#include <fhir/parameters.h>
#include <fhir/practitionerrole.h>
#include <fhir/fhirbasic.h>
#include <fhir/allergy.h>
#include <fhir/operationoutcome.h>

#include "../win32/w32strings.h"

class FhirParseException : public std::exception {
private:
    std::string error{};
public:
    FhirParseException(const std::string &error) : error(error) {}
    const char * what() const noexcept override;
};

const char *FhirParseException::what() const noexcept {
    return error.c_str();
}

std::shared_ptr<Fhir> Fhir::Parse(const web::json::value &obj) {
    if (!obj.has_string_field(as_wstring_on_win32("resourceType"))) {
        throw FhirParseException("No resourceType");
    }
    auto resourceType = from_wstring_on_win32(obj.at(as_wstring_on_win32("resourceType")).as_string());
    if (resourceType == "Medication") {
        return std::make_shared<FhirMedication>(FhirMedication::Parse(obj));
    }
    if (resourceType == "MedicationStatement") {
        return std::make_shared<FhirMedicationStatement>(FhirMedicationStatement::Parse(obj));
    }
    if (resourceType == "Composition") {
        return std::make_shared<FhirComposition>(FhirComposition::Parse(obj));
    }
    if (resourceType == "Practitioner") {
        return std::make_shared<FhirPractitioner>(FhirPerson::Parse(obj));
    }
    if (resourceType == "Patient") {
        return std::make_shared<FhirPatient>(FhirPerson::Parse(obj));
    }
    if (resourceType == "Organization") {
        return std::make_shared<FhirOrganization>(FhirOrganization::Parse(obj));
    }
    if (resourceType == "Substance") {
        return std::make_shared<FhirSubstance>(FhirSubstance::Parse(obj));
    }
    if (resourceType == "Bundle") {
        return std::make_shared<FhirBundle>(FhirBundle::Parse(obj));
    }
    if (resourceType == "Parameters") {
        return std::make_shared<FhirParameters>(FhirParameters::Parse(obj));
    }
    if (resourceType == "PractitionerRole") {
        return std::make_shared<FhirPractitionerRole>(FhirPractitionerRole::Parse(obj));
    }
    if (resourceType == "Basic") {
        return std::make_shared<FhirBasic>(FhirBasic::Parse(obj));
    }
    if (resourceType == "AllergyIntolerance") {
        return std::make_shared<FhirAllergyIntolerance>(FhirAllergyIntolerance::Parse(obj));
    }
    if (resourceType == "OperationOutcome") {
        return std::make_shared<FhirOperationOutcome>(FhirOperationOutcome::Parse(obj));
    }
    std::string error{"Unknown resourceType: "};
    error.append(resourceType);
    throw FhirParseException(error);
}
