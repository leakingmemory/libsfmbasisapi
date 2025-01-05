//
// Created by sigsegv on 1/13/24.
//

#include <fhir/fhirbasic.h>

#include "../win32/w32strings.h"

web::json::value FhirBasic::ToJson() const {
    auto obj = Fhir::ToJson();
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("Basic"));
    if (subject.IsSet()) {
        obj[as_wstring_on_win32("subject")] = subject.ToJson();
    }
    if (author.IsSet()) {
        obj[as_wstring_on_win32("author")] = author.ToJson();
    }
    if (!identifiers.empty()) {
        auto arr = web::json::value::array(identifiers.size());
#ifdef WIN32
        decltype(identifiers.size()) i = 0;
#else
        typeof(identifiers.size()) i = 0;
#endif
        for (const auto &id : identifiers) {
            arr[i++] = id.ToJson();
        }
        obj[as_wstring_on_win32("identifier")] = arr;
    }
    if (code.IsSet()) {
        obj[as_wstring_on_win32("code")] = code.ToJson();
    }
    FhirPartOfChain::ToJsonInline(obj);
    return obj;
}

FhirBasic FhirBasic::Parse(const web::json::value &obj) {
    FhirBasic fhirBasic{};

    if (!fhirBasic.Fhir::ParseInline(obj)) {
        throw std::exception();
    }

    fhirBasic.FhirPartOfChain::ParseInline(obj);

    if (obj.has_field(as_wstring_on_win32("subject"))) {
        fhirBasic.subject = FhirReference::Parse(obj.at(as_wstring_on_win32("subject")));
    }
    if (obj.has_field(as_wstring_on_win32("author"))) {
        fhirBasic.author = FhirReference::Parse(obj.at(as_wstring_on_win32("author")));
    }
    if (obj.has_field(as_wstring_on_win32("identifier"))) {
        const auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for (const auto &id : arr) {
            fhirBasic.identifiers.push_back(FhirIdentifier::Parse(id));
        }
    }
    if (obj.has_field(as_wstring_on_win32("code"))) {
        fhirBasic.code = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("code")));
    }

    return fhirBasic;
}
