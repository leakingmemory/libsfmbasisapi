//
// Created by sigsegv on 12/12/23.
//

#ifndef SFMBASISFAKER_FHIRCONCEPTS_H
#define SFMBASISFAKER_FHIRCONCEPTS_H

#include "cpplevel.h"

#include <concepts>
#include <type_traits>

class Fhir;

template <class T> concept FhirSubclass = requires (T a) {
    { a } -> std::convertible_to<const Fhir &>;
};

#if (LIBSFMBASISAPI_CPPLEVEL >= 23 && LIBSFMBASISAPI_HAS_CONSTEXPRSTRING)
#define LIBSFMBASISAPI_CONSTEXPR_STRING constexpr
#else
#define LIBSFMBASISAPI_CONSTEXPR_STRING
#endif

#endif //SFMBASISFAKER_FHIRCONCEPTS_H
