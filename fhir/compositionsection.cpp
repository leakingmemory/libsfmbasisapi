//
// Created by jeo on 08.12.2023.
//

#include <fhir/compositionsection.h>

#include "../win32/w32strings.h"

web::json::value FhirCompositionSection::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (!title.empty()) {
        obj[as_wstring_on_win32("title")] = web::json::value::string(as_wstring_on_win32(title));
    }
    if (code.IsSet()) {
        obj[as_wstring_on_win32("code")] = code.ToJson();
    }
    if (!textStatus.empty() || !textXhtml.empty()) {
        auto text = web::json::value::object();
        if (!textStatus.empty()) {
            text[as_wstring_on_win32("status")] = web::json::value::string(as_wstring_on_win32(textStatus));
        }
        if (!textXhtml.empty()) {
            text[as_wstring_on_win32("div")] = web::json::value::string(as_wstring_on_win32(textXhtml));
        }
        obj[as_wstring_on_win32("text")] = text;
    }
    if (!entries.empty()) {
        auto arr = web::json::value::array(entries.size());
#ifdef WIN32
        decltype(entries.size()) i = 0;
#else
        typeof(entries.size()) i = 0;
#endif
        for (const auto &e : entries) {
            arr[i++] = e.ToJson();
        }
        obj[as_wstring_on_win32("entry")] = arr;
    } else if (emptyReason.IsSet()) {
        obj[as_wstring_on_win32("emptyReason")] = emptyReason.ToJson();
    }
    return obj;
}

FhirCompositionSection FhirCompositionSection::Parse(const web::json::value &obj) {
    auto section = FhirCompositionSection();

    if (obj.has_string_field(as_wstring_on_win32("title"))) {
        section.title = from_wstring_on_win32(obj.at(as_wstring_on_win32("title")).as_string());
    }

    if (obj.has_object_field(as_wstring_on_win32("code"))) {
        section.code = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("code")));
    }

    if (obj.has_object_field(as_wstring_on_win32("text"))) {
        auto text = obj.at(as_wstring_on_win32("text"));
        if (text.has_string_field(as_wstring_on_win32("status"))) {
            section.textStatus = from_wstring_on_win32(text.at(as_wstring_on_win32("status")).as_string());
        }
        if (text.has_string_field(as_wstring_on_win32("div"))) {
            section.textXhtml = from_wstring_on_win32(text.at(as_wstring_on_win32("div")).as_string());
        }
    }

    if (obj.has_array_field(as_wstring_on_win32("entry"))) {
        auto arr = obj.at(as_wstring_on_win32("entry")).as_array();
        for (const auto &e : arr) {
            section.entries.push_back(FhirReference::Parse(e));
        }
    } else if (obj.has_object_field(as_wstring_on_win32("emptyReason"))) {
        section.emptyReason = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("emptyReason")));
    }

    return section;
}