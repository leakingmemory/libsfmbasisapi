//
// Created by jeo on 08.12.2023.
//

#include <fhir/composition.h>
#include "json.h"

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

json FhirAttester::ToJsonObj() const {
    struct json json{};
    if (!mode.empty()) {
        json["mode"] = mode;
    }
    if (!dateTime.empty()) {
        json["time"] = dateTime;
    }
    if (party.IsSet()) {
        json["party"] = party.ToJsonObj();
    }
    return json;
}

FhirAttester FhirAttester::Parse(const json &obj) {
    FhirAttester attester{};
    if (obj.contains("mode")) {
        attester.mode = obj["mode"];
    }
    if (obj.contains("time")) {
        attester.dateTime = obj["time"];
    }
    if (obj.contains("party")) {
        attester.party = FhirReference::ParseObj(obj["party"]);
    }
    return attester;
}

json FhirComposition::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    if (identifier.IsSet()) {
        obj["identifier"] = identifier.ToJsonObj();
    }
    if (type.IsSet()) {
        obj["type"] = type.ToJsonObj();
    }
    if (subject.IsSet()) {
        obj["subject"] = subject.ToJsonObj();
    }
    if (!authors.empty()) {
        auto arr = nlohmann::json::array();
        decltype(authors.size()) i = 0;
        for (const auto &a : authors) {
            arr.push_back(a.ToJsonObj());
        }
        obj["author"] = arr;
    }
    if (!title.empty()) {
        obj["title"] = title;
    }
    if (!confidentiality.empty()) {
        obj["confidentiality"] = confidentiality;
    }
    if (!sections.empty()) {
        auto arr = nlohmann::json::array();
        decltype(sections.size()) i = 0;
        for (const auto &s : sections) {
            arr.push_back(s.ToJsonObj());
        }
        obj["section"] = arr;
    }
    if (relatesTo.IsSet()) {
        auto rel = nlohmann::json::object();
        if (!relatesToCode.empty()) {
            rel["code"] = relatesToCode;
        }
        rel["targetIdentifier"] = relatesTo.ToJsonObj();
        obj["relatesTo"] = rel;
    }
    if (!attester.empty()) {
        auto att = nlohmann::json::array();
        decltype(attester.size()) j = 0;
        for (const auto &at: attester) {
            att.push_back(at.ToJsonObj());
        }
        obj["attester"] = att;
    }
    return obj;
}

FhirComposition FhirComposition::Parse(const json &obj) {
    FhirComposition comp{};

    if (!comp.ParseInline(obj)) {
        throw std::exception();
    }

    if(obj.contains("identifier"))
        comp.identifier = FhirIdentifier::ParseObj(obj["identifier"]);

    if(obj.contains("type"))
        comp.type = FhirCodeableConcept::Parse(obj["type"]);

    if(obj.contains("subject"))
        comp.subject = FhirReference::ParseObj(obj["subject"]);

    if(obj.contains("author")) {
        auto authors_arr = obj["author"];

        if (authors_arr.is_array()) {
            for (int i = 0; i < authors_arr.size(); i++) {
                comp.authors.push_back(FhirReference::ParseObj(authors_arr[i]));
            }
        }
    }

    if(obj.contains("title"))
        comp.title = obj["title"];

    if(obj.contains("confidentiality"))
        comp.confidentiality = obj["confidentiality"];

    if(obj.contains("section")) {
        auto sections_arr = obj["section"];
        if (sections_arr.is_array()) {
            for (int i = 0; i < sections_arr.size(); i++) {
                comp.sections.push_back(FhirCompositionSection::Parse(sections_arr[i]));
            }
        }
    }

    if (obj.contains("relatesTo")) {
        auto rel = obj["relatesTo"];
        if (rel.contains("code")) {
            comp.relatesToCode = rel["code"];
        }
        if (rel.contains("targetIdentifier")) {
            comp.relatesTo = FhirIdentifier::ParseObj(rel["targetIdentifier"]);
        }
    }

    if (obj.contains("attester")) {
        auto attester_arr = obj["attester"];
        if (attester_arr.is_array()) {
            for (int i = 0; i < attester_arr.size(); i++) {
                comp.attester.push_back(FhirAttester::Parse(attester_arr[i]));
            }
        }
    }

    return comp;
}
