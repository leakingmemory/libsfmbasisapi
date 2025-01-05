//
// Created by jeo on 08.12.2023.
//

#include <fhir/composition.h>

#include "../win32/w32strings.h"

std::string FhirAttester::GetMode() const {
    return mode;
}

void FhirAttester::SetMode(const std::string &m) {
    mode = m;
}

std::string FhirAttester::GetDateTime() const {
    return dateTime;
}

void FhirAttester::SetDateTime(const std::string &d) {
    dateTime = d;
}

FhirReference FhirAttester::GetParty() const {
    return party;
}

void FhirAttester::SetParty(const FhirReference &p) {
    party = p;
}

web::json::value FhirAttester::ToJson() const {
    auto json = web::json::value::object();
    if (!mode.empty()) {
        json[as_wstring_on_win32("mode")] = web::json::value::string(as_wstring_on_win32(mode));
    }
    if (!dateTime.empty()) {
        json[as_wstring_on_win32("time")] = web::json::value::string(as_wstring_on_win32(dateTime));
    }
    if (party.IsSet()) {
        json[as_wstring_on_win32("party")] = party.ToJson();
    }
    return json;
}

FhirAttester FhirAttester::Parse(const web::json::value &obj) {
    FhirAttester attester{};
    if (obj.has_string_field(as_wstring_on_win32("mode"))) {
        attester.mode = from_wstring_on_win32(obj.at(as_wstring_on_win32("mode")).as_string());
    }
    if (obj.has_string_field(as_wstring_on_win32("time"))) {
        attester.dateTime = from_wstring_on_win32(obj.at(as_wstring_on_win32("time")).as_string());
    }
    if (obj.has_object_field(as_wstring_on_win32("party"))) {
        attester.party = FhirReference::Parse(obj.at(as_wstring_on_win32("party")));
    }
    return attester;
}

web::json::value FhirComposition::ToJson() const {
    auto obj = Fhir::ToJson();
    if (identifier.IsSet()) {
        obj[as_wstring_on_win32("identifier")] = identifier.ToJson();
    }
    if (type.IsSet()) {
        obj[as_wstring_on_win32("type")] = type.ToJson();
    }
    if (subject.IsSet()) {
        obj[as_wstring_on_win32("subject")] = subject.ToJson();
    }
    if (!authors.empty()) {
        auto arr = web::json::value::array(authors.size());
#ifdef WIN32
        decltype(authors.size()) i = 0;
#else
        typeof(authors.size()) i = 0;
#endif
        for (const auto &a : authors) {
            arr[i++] = a.ToJson();
        }
        obj[as_wstring_on_win32("author")] = arr;
    }
    if (!title.empty()) {
        obj[as_wstring_on_win32("title")] = web::json::value::string(as_wstring_on_win32(title));
    }
    if (!confidentiality.empty()) {
        obj[as_wstring_on_win32("confidentiality")] = web::json::value::string(as_wstring_on_win32(confidentiality));
    }
    if (!sections.empty()) {
        auto arr = web::json::value::array(sections.size());
#ifdef WIN32
        decltype(sections.size()) i = 0;
#else
        typeof(sections.size()) i = 0;
#endif
        for (const auto &s : sections) {
            arr[i++] = s.ToJson();
        }
        obj[as_wstring_on_win32("section")] = arr;
    }
    if (relatesTo.IsSet()) {
        auto rel = web::json::value::object();
        if (!relatesToCode.empty()) {
            rel[as_wstring_on_win32("code")] = web::json::value::string(as_wstring_on_win32(relatesToCode));
        }
        rel[as_wstring_on_win32("targetIdentifier")] = relatesTo.ToJson();
        obj[as_wstring_on_win32("relatesTo")] = rel;
    }
    if (!attester.empty()) {
        auto att = web::json::value::array(attester.size());
#ifdef WIN32
        decltype(attester.size()) j = 0;
#else
        typeof(attester.size()) j = 0;
#endif
        for (const auto &at: attester) {
            att[j++] = at.ToJson();
        }
        obj[as_wstring_on_win32("attester")] = att;
    }
    return obj;
}

FhirComposition FhirComposition::Parse(const web::json::value &obj) {
    FhirComposition comp{};

    if (!comp.ParseInline(obj)) {
        throw std::exception();
    }

    if(obj.has_object_field(as_wstring_on_win32("identifier")))
        comp.identifier = FhirIdentifier::Parse(obj.at(as_wstring_on_win32("identifier")));

    if(obj.has_object_field(as_wstring_on_win32("type")))
        comp.type = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("type")));

    if(obj.has_object_field(as_wstring_on_win32("subject")))
        comp.subject = FhirReference::Parse(obj.at(as_wstring_on_win32("subject")));

    if(obj.has_array_field(as_wstring_on_win32("author"))) {
        web::json::array authors_arr = obj.at(as_wstring_on_win32("author")).as_array();

        for(int i=0; i<authors_arr.size(); i++) {
            comp.authors.push_back(FhirReference::Parse(authors_arr[i]));
        }
    }

    if(obj.has_string_field(as_wstring_on_win32("title")))
        comp.title = from_wstring_on_win32(obj.at(as_wstring_on_win32("title")).as_string());

    if(obj.has_string_field(as_wstring_on_win32("confidentiality")))
        comp.confidentiality = from_wstring_on_win32(obj.at(as_wstring_on_win32("confidentiality")).as_string());

    if(obj.has_array_field(as_wstring_on_win32("section"))) {
        web::json::array sections_arr = obj.at(as_wstring_on_win32("section")).as_array();

        for(int i=0; i<sections_arr.size(); i++) {
            comp.sections.push_back(FhirCompositionSection::Parse(sections_arr[i]));
        }
    }

    if (obj.has_object_field(as_wstring_on_win32("relatesTo"))) {
        auto rel = obj.at(as_wstring_on_win32("relatesTo"));
        if (rel.has_string_field(as_wstring_on_win32("code"))) {
            comp.relatesToCode = from_wstring_on_win32(rel.at(as_wstring_on_win32("code")).as_string());
        }
        if (rel.has_object_field(as_wstring_on_win32("targetIdentifier"))) {
            comp.relatesTo = FhirIdentifier::Parse(rel.at(as_wstring_on_win32("targetIdentifier")));
        }
    }

    if (obj.has_array_field(as_wstring_on_win32("attester"))) {
        web::json::array attester_arr = obj.at(as_wstring_on_win32("attester")).as_array();

        for (int i = 0; i < attester_arr.size(); i++) {
            comp.attester.push_back(FhirAttester::Parse(attester_arr[i]));
        }
    }

    return comp;
}
