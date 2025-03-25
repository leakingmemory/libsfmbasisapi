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
#include <fhir/meddispense.h>
#include "json.h"

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

std::shared_ptr<Fhir> Fhir::ParseObj(const json &obj) {
    if (!obj.contains("resourceType")) {
        throw FhirParseException("No resourceType");
    }
    std::string resourceType = obj["resourceType"];
    if (resourceType == "Medication") {
        return std::make_shared<FhirMedication>(FhirMedication::ParseObj(obj));
    }
    if (resourceType == "MedicationStatement") {
        return std::make_shared<FhirMedicationStatement>(FhirMedicationStatement::ParseObj(obj));
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
        return std::make_shared<FhirBundle>(FhirBundle::ParseObj(obj));
    }
    if (resourceType == "Parameters") {
        return std::make_shared<FhirParameters>(FhirParameters::ParseObj(obj));
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
        return std::make_shared<FhirOperationOutcome>(FhirOperationOutcome::ParseObj(obj));
    }
    if (resourceType == "MedicationDispense") {
        return std::make_shared<FhirMedicationDispense>(FhirMedicationDispense::ParseObj(obj));
    }
    std::string error{"Unknown resourceType: "};
    error.append(resourceType);
    throw FhirParseException(error);
}

std::shared_ptr<Fhir> Fhir::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}