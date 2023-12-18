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
    if (!obj.has_string_field("resourceType")) {
        throw FhirParseException("No resourceType");
    }
    auto resourceType = obj.at("resourceType").as_string();
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
    std::string error{"Unknown resourceType: "};
    error.append(resourceType);
    throw FhirParseException(error);
}

std::string Fhir::GetDisplay() const {
    return !id.empty() ? id : "Display";
}
