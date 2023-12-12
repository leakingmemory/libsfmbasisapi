cmake_minimum_required(VERSION 3.27)
project(libsfmbasisapi)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-fPIC)

find_package(cpprestsdk REQUIRED)

add_subdirectory(fhir)
add_subdirectory(nhnfhir)

add_library(sfmbasisapi SHARED main.cpp)
set_target_properties(sfmbasisapi PROPERTIES SOVERSION 1 VERSION 1.0.0)

target_link_libraries(sfmbasisapi PRIVATE libfhir)
target_include_directories(sfmbasisapi PRIVATE include)

target_link_libraries(sfmbasisapi PRIVATE nhnfhir)
target_link_libraries(sfmbasisapi PRIVATE cpprestsdk::cpprest -lcrypto)

install(TARGETS sfmbasisapi
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include/sfmbasisapi)

enable_testing()
add_subdirectory(tests)