
add_library(nhnfhir OBJECT KjRfErrorCode.cpp SfmBandaPrescription.cpp)

add_dependencies(nhnfhir "cpplevel.h")

target_include_directories(nhnfhir PRIVATE ../include)
target_include_directories(nhnfhir PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/..")
