//
// Created by jeo on 08.12.2023.
//

#include <fhir/bundle.h>
#include <fhir/value.h>
#include "json.h"

void FhirBundle::AddLink(const std::string &relation, const std::string &url) {
    link.emplace_back(relation, url);
}

void FhirBundle::AddLink(std::string &&relation, std::string &&url) {
    link.emplace_back(relation, url);
}

void FhirBundle::AddEntry(const FhirBundleEntry &entry) {
    entries.emplace_back(entry);
}

void FhirBundle::AddEntry(FhirBundleEntry &&entry) {
    entries.emplace_back(std::move(entry));
}

void FhirBundle::SetEntries(const std::vector<FhirBundleEntry> &entries) {
    this->entries = entries;
}

json FhirBundle::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    obj["resourceType"] = "Bundle";
    if (!type.empty()) {
        obj["type"] = type;
    }
    if (!link.empty()) {
        auto arr = nlohmann::json::array();
        decltype(link.size()) i = 0;
        for (const auto &l : link) {
            arr.push_back(l.ToJsonObj());
        }
        obj["link"] = arr;
    }
    obj["total"] = entries.size();
    auto arr = nlohmann::json::array();
    decltype(entries.size()) i = 0;
    for (const auto &e : entries) {
        arr.push_back(e.ToJsonObj());
    }
    obj["entry"] = arr;
    return obj;
}

FhirBundle FhirBundle::ParseObj(const json &obj) {
    FhirBundle bundle{};

    if (!bundle.ParseInline(obj)) {
        throw std::exception();
    }

    if (obj.contains("type")) {
        bundle.type = obj["type"];
    }
    if (obj.contains("total")) {
        bundle.total = obj["total"];
    }
    if (obj.contains("link")) {
        for (const auto &value : obj["link"]) {
            bundle.link.push_back(FhirLink::ParseObj(value));
        }
    }
    if (obj.contains("entry")) {
        for (const auto &value : obj["entry"]) {
            bundle.entries.push_back(FhirBundleEntry::Parse(value));
        }
    }

    return bundle;
}

FhirBundle FhirBundle::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}