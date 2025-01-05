//
// Created by sigsegv on 12/8/23.
//

#include <fhir/dosage.h>

#include "../win32/w32strings.h"

web::json::value FhirDosage::ToJson() const {
    auto obj = FhirExtendable::ToJson();
    obj[as_wstring_on_win32("sequence")] = web::json::value::number(sequence);
    obj[as_wstring_on_win32("text")] = web::json::value::string(as_wstring_on_win32(text));
    return obj;
}

FhirDosage FhirDosage::Parse(const web::json::value &obj) {
    FhirDosage dosage{};
    if (!dosage.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_number_field(as_wstring_on_win32("sequence"))) {
        dosage.sequence = obj.at(as_wstring_on_win32("sequence")).as_number().to_int32();
    }
    if (obj.has_string_field(as_wstring_on_win32("text"))) {
        dosage.text = from_wstring_on_win32(obj.at(as_wstring_on_win32("text")).as_string());
    }
    return dosage;
}