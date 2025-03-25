add_library(libfhir OBJECT fhir.cpp value.cpp medication.cpp fhirextendable.cpp extension.cpp fhirobject.cpp dosage.cpp
        medstatement.cpp bundleentry.cpp fhirparser.cpp bundle.cpp compositionsection.cpp composition.cpp person.cpp
        organization.cpp substance.cpp parameter.cpp parameters.cpp practitionerrole.cpp fhirbasic.cpp
        allergy.cpp operationoutcome.cpp fhirpartofchain.cpp json.h json.cpp meddispense.cpp)
add_dependencies(libfhir "cpplevel.h")

target_include_directories(libfhir PRIVATE "../include")
target_include_directories(libfhir PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
