//
// Created by jeo on 08.12.2023.
//

#include <fhir/compositionsection.h>
#include "json.h"

json FhirCompositionSection::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (!title.empty()) {
        obj["title"] = title;
    }
    if (code.IsSet()) {
        obj["code"] = code.ToJsonObj();
    }
    if (!textStatus.empty() || !textXhtml.empty()) {
        auto text = nlohmann::json::object();
        if (!textStatus.empty()) {
            text["status"] = textStatus;
        }
        if (!textXhtml.empty()) {
            text["div"] = textXhtml;
        }
        obj["text"] = text;
    }
    if (!entries.empty()) {
        auto arr = nlohmann::json::array();
        decltype(entries.size()) i = 0;
        for (const auto &e : entries) {
            arr.push_back(e.ToJsonObj());
        }
        obj["entry"] = arr;
    } else if (emptyReason.IsSet()) {
        obj["emptyReason"] = emptyReason.ToJsonObj();
    }
    return obj;
}

FhirCompositionSection FhirCompositionSection::Parse(const json &obj) {
    auto section = FhirCompositionSection();

    if (obj.contains("title")) {
        section.title = obj["title"];
    }

    if (obj.contains("code")) {
        section.code = FhirCodeableConcept::Parse(obj["code"]);
    }

    if (obj.contains("text")) {
        auto text = obj["text"];
        if (text.contains("status")) {
            section.textStatus = text["status"];
        }
        if (text.contains("div")) {
            section.textXhtml = text["div"];
        }
    }

    if (obj.contains("entry")) {
        auto arr = obj["entry"];
        for (const auto &e : arr) {
            section.entries.push_back(FhirReference::ParseObj(e));
        }
    } else if (obj.contains("emptyReason")) {
        section.emptyReason = FhirCodeableConcept::Parse(obj["emptyReason"]);
    }

    return section;
}