//
// Created by jeo on 08.12.2023.
//

#include <fhir/composition.h>

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
        json["mode"] = web::json::value::string(mode);
    }
    if (!dateTime.empty()) {
        json["time"] = web::json::value::string(dateTime);
    }
    if (party.IsSet()) {
        json["party"] = party.ToJson();
    }
    return json;
}

FhirAttester FhirAttester::Parse(const web::json::value &obj) {
    FhirAttester attester{};
    if (obj.has_string_field("mode")) {
        attester.mode = obj.at("mode").as_string();
    }
    if (obj.has_string_field("time")) {
        attester.dateTime = obj.at("time").as_string();
    }
    if (obj.has_object_field("party")) {
        attester.party = FhirReference::Parse(obj.at("party"));
    }
    return attester;
}

web::json::value FhirComposition::ToJson() const {
    auto obj = Fhir::ToJson();
    if (identifier.IsSet()) {
        obj["identifier"] = identifier.ToJson();
    }
    if (type.IsSet()) {
        obj["type"] = type.ToJson();
    }
    if (subject.IsSet()) {
        obj["subject"] = subject.ToJson();
    }
    if (!authors.empty()) {
        auto arr = web::json::value::array(authors.size());
        typeof(authors.size()) i = 0;
        for (const auto &a : authors) {
            arr[i++] = a.ToJson();
        }
        obj["author"] = arr;
    }
    if (!title.empty()) {
        obj["title"] = web::json::value::string(title);
    }
    if (!confidentiality.empty()) {
        obj["confidentiality"] = web::json::value::string(confidentiality);
    }
    if (!sections.empty()) {
        auto arr = web::json::value::array(sections.size());
        typeof(sections.size()) i = 0;
        for (const auto &s : sections) {
            arr[i++] = s.ToJson();
        }
        obj["section"] = arr;
    }
    if (relatesTo.IsSet()) {
        auto rel = web::json::value::object();
        if (!relatesToCode.empty()) {
            rel["code"] = web::json::value::string(relatesToCode);
        }
        rel["targetIdentifier"] = relatesTo.ToJson();
        obj["relatesTo"] = rel;
    }
    if (!attester.empty()) {
        auto att = web::json::value::array(attester.size());
        typeof(attester.size()) j = 0;
        for (const auto &at: attester) {
            att[j++] = at.ToJson();
        }
        obj["attester"] = att;
    }
    return obj;
}

FhirComposition FhirComposition::Parse(const web::json::value &obj) {
    FhirComposition comp{};

    if (!comp.ParseInline(obj)) {
        throw std::exception();
    }

    if(obj.has_object_field("identifier"))
        comp.identifier = FhirIdentifier::Parse(obj.at("identifier"));

    if(obj.has_object_field("type"))
        comp.type = FhirCodeableConcept::Parse(obj.at("type"));

    if(obj.has_object_field("subject"))
        comp.subject = FhirReference::Parse(obj.at("subject"));

    if(obj.has_array_field("author")) {
        web::json::array authors_arr = obj.at("author").as_array();

        for(int i=0; i<authors_arr.size(); i++) {
            comp.authors.push_back(FhirReference::Parse(authors_arr[i]));
        }
    }

    if(obj.has_string_field("title"))
        comp.title = obj.at("title").as_string();

    if(obj.has_string_field("confidentiality"))
        comp.confidentiality = obj.at("confidentiality").as_string();

    if(obj.has_array_field("section")) {
        web::json::array sections_arr = obj.at("section").as_array();

        for(int i=0; i<sections_arr.size(); i++) {
            comp.sections.push_back(FhirCompositionSection::Parse(sections_arr[i]));
        }
    }

    if (obj.has_object_field("relatesTo")) {
        auto rel = obj.at("relatesTo");
        if (rel.has_string_field("code")) {
            comp.relatesToCode = rel.at("code").as_string();
        }
        if (rel.has_object_field("targetIdentifier")) {
            comp.relatesTo = FhirIdentifier::Parse(rel.at("targetIdentifier"));
        }
    }

    if (obj.has_array_field("attester")) {
        web::json::array attester_arr = obj.at("attester").as_array();

        for (int i = 0; i < attester_arr.size(); i++) {
            comp.attester.push_back(FhirAttester::Parse(attester_arr[i]));
        }
    }

    return comp;
}
