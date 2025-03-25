
add_executable(valuetest valuetest.cpp assert.cpp)
add_dependencies(valuetest "cpplevel.h")
target_include_directories(valuetest PRIVATE ../include)
target_include_directories(valuetest PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(valuetest PRIVATE libfhir)

add_test(NAME ValueTest COMMAND valuetest)

add_executable(parseMedication assert.cpp parseMedication.cpp)
add_dependencies(parseMedication "cpplevel.h")
target_include_directories(parseMedication PRIVATE ../include)
target_include_directories(parseMedication PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(parseMedication PRIVATE libfhir)

add_test(NAME ParseMedicationMagistral COMMAND parseMedication "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/magistral/magistral-medication.json" magistral)

add_executable(parseMedicationStatement assert.cpp parseMedicationStatement.cpp)
add_dependencies(parseMedicationStatement "cpplevel.h")
target_include_directories(parseMedicationStatement PRIVATE ../include)
target_include_directories(parseMedicationStatement PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(parseMedicationStatement PRIVATE libfhir)

add_test(NAME ParseMedicationStatementMagistral COMMAND parseMedicationStatement "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/magistral/magistral-medication-statement.json" magistral)

add_executable(parseBundle assert.cpp parseBundle.cpp)
add_dependencies(parseBundle "cpplevel.h")
target_include_directories(parseBundle PRIVATE ../include)
target_include_directories(parseBundle PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(parseBundle PRIVATE libfhir)

add_test(NAME ParseBundleMagistral COMMAND parseBundle "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/magistral/magistral-bundle.json" magistral)

add_executable(parseParameters assert.cpp parseParameters.cpp)
add_dependencies(parseParameters "cpplevel.h")
target_include_directories(parseParameters PRIVATE ../include)
target_include_directories(parseParameters PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(parseParameters PRIVATE libfhir)

add_test(NAME ParseGetmedReq COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/requests/getmed.json" request)
add_test(NAME ParseGetmedResp COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/magistral/magistral-getmed-response.json" response)
add_test(NAME ParseGetmedResp2 COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/getmedex1.json" response)
add_test(NAME ParseGetmedResp3 COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/getmedex2.json" response)
add_test(NAME ParseGetmedResp4 COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/getmedex3.json" response)
add_test(NAME ParseGetmedCrash20240721 COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/getmed-crash-20240721.json" response)
add_test(NAME ParseGetmedSendmedCrash20250225 COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/getmed-sendmedcrash-20250225.json" response)
add_test(NAME ParseSendmedReq COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/requests/sendmed.json" sendmedrequest)
add_test(NAME ParseSendmedResp COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/sendmed.json" sendmedresponse)
add_test(NAME ParseSendmedResp2 COMMAND parseParameters "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/sendmed2.json" sendmedresponse2)

add_executable(fhirResourceTypeTest assert.cpp fhirResourceType.cpp)
add_dependencies(fhirResourceTypeTest "cpplevel.h")
target_include_directories(fhirResourceTypeTest PRIVATE ../include)
target_include_directories(fhirResourceTypeTest PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(fhirResourceTypeTest PRIVATE libfhir)

add_test(NAME FhirResourceTypeTest COMMAND fhirResourceTypeTest)

add_executable(parseOperationOutcome assert.cpp parseOperationOutcome.cpp)
add_dependencies(parseOperationOutcome "cpplevel.h")
target_include_directories(parseOperationOutcome PRIVATE ../include)
target_include_directories(parseOperationOutcome PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
target_link_libraries(parseOperationOutcome PRIVATE libfhir)

add_test(NAME OperationOutcomeTest COMMAND parseOperationOutcome "${CMAKE_SOURCE_DIR}/tests/data/nhnfhir/responses/errors.json")
