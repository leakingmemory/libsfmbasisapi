cmake_minimum_required(VERSION 3.27)
project(libsfmbasisapi)

set(CMAKE_CXX_STANDARD 23)
set(CPPLEVEL 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    add_compile_options(-fPIC)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    add_compile_options(-I/usr/local/include)
endif()

find_package(cpprestsdk REQUIRED)

if (WIN32)
    message("cpprest include ${cpprestsdk_DIR}/../../../include")
    add_compile_options("/I${cpprestsdk_DIR}/../../../include")

    add_subdirectory(win32)
endif()

try_compile(CONSTEXPRSTRINGTEST "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/configtests/constexprstrtest.cpp")

if (CONSTEXPRSTRINGTEST)
    set(CONSTEXPRSTRING "true")
else()
    set(CONSTEXPRSTRING "false")
endif()

if (WIN32)
    add_custom_target("cpplevel.h"
            ALL ${CMAKE_COMMAND} -E "copy" "${CMAKE_CURRENT_SOURCE_DIR}/cpplevel.h.fallback" "${CMAKE_CURRENT_BINARY_DIR}/cpplevel.h"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cpplevel.h.fallback"
    )
else()
    add_custom_target("cpplevel.h"
            ALL "cat" "${CMAKE_CURRENT_SOURCE_DIR}/cpplevel.h.in" | sed -e "s/xCPPLEVELx/${CPPLEVEL}/" | sed -e "s/xCONSTEXPRSTRINGx/${CONSTEXPRSTRING}/" > "${CMAKE_CURRENT_BINARY_DIR}/cpplevel.h"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cpplevel.h.in"
    )
endif()

add_subdirectory(fhir)
add_subdirectory(nhnfhir)

add_library(sfmbasisapi SHARED main.cpp)
set_target_properties(sfmbasisapi PROPERTIES SOVERSION 8 VERSION 8.0.0)
add_dependencies(sfmbasisapi "cpplevel.h")

target_link_libraries(sfmbasisapi PRIVATE libfhir)
target_include_directories(sfmbasisapi PRIVATE include)
target_include_directories(sfmbasisapi PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(sfmbasisapi PRIVATE nhnfhir)
if (WIN32)
    target_link_libraries(sfmbasisapi PRIVATE win32)
    target_link_libraries(sfmbasisapi PRIVATE c:/libs/cpprest_2_10d.lib c:/libs/zlib.lib c:/libs/libssl.lib c:/libs/libcrypto.lib)
else()
    target_link_libraries(sfmbasisapi PRIVATE cpprestsdk::cpprest -lcrypto)
endif()

install(TARGETS sfmbasisapi
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cpplevel.h"
        DESTINATION include/sfmbasisapi/fhir)

install(DIRECTORY include/ DESTINATION include/sfmbasisapi)

enable_testing()
add_subdirectory(tests)