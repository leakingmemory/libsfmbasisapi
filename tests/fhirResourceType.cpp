//
// Created by sigsegv on 12/18/23.
//

#include <fhir/parameters.h>
#include <fhir/medstatement.h>
#include <fhir/composition.h>
#include <fhir/person.h>
#include <fhir/organization.h>
#include <fhir/substance.h>
#include <fhir/bundle.h>
#include <fhir/medication.h>
#include "assert.h"

template <class T> void TestResourceType() {
    T parameters{};
    auto json = parameters.ToJson();
    auto deserialized = Fhir::ParseJson(json);
    auto parametersDeserialized = std::dynamic_pointer_cast<T>(deserialized);
    AreEqual(true, parametersDeserialized.operator bool());
}

int main(int argc, char **argv) {
    TestResourceType<FhirParameters>();
    TestResourceType<FhirMedicationStatement>();
    TestResourceType<FhirComposition>();
    TestResourceType<FhirPatient>();
    TestResourceType<FhirPractitioner>();
    TestResourceType<FhirOrganization>();
    TestResourceType<FhirSubstance>();
    TestResourceType<FhirBundle>();
    TestResourceType<FhirMedication>();
}