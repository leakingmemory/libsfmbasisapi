cmake_minimum_required(VERSION 3.27)
project(libsfmbasisapi)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CPPLEVEL 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_compile_options("/I${NLOHMANN_INCLUDE_DIR}")
else()
    add_compile_options(-fPIC)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    add_compile_options(-I/usr/local/include)
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
set_target_properties(sfmbasisapi PROPERTIES SOVERSION 9 VERSION 9.0.0)
add_dependencies(sfmbasisapi "cpplevel.h")

target_link_libraries(sfmbasisapi PRIVATE libfhir)
target_include_directories(sfmbasisapi PRIVATE include)
target_include_directories(sfmbasisapi PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(sfmbasisapi PRIVATE nhnfhir)

install(TARGETS sfmbasisapi
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cpplevel.h"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sfmbasisapi/fhir)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sfmbasisapi)

enable_testing()
add_subdirectory(tests)