//
// Created by jeo on 08.12.2023.
//

#include <fhir/bundle.h>
#include <fhir/value.h>

#include "../win32/w32strings.h"

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

web::json::value FhirBundle::ToJson() const {
    auto obj = Fhir::ToJson();
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("Bundle"));
    if (!type.empty()) {
        obj[as_wstring_on_win32("type")] = web::json::value::string(as_wstring_on_win32(type));
    }
    if (!link.empty()) {
        auto arr = web::json::value::array(link.size());
#ifdef WIN32
        decltype(link.size()) i = 0;
#else
        typeof(link.size()) i = 0;
#endif
        for (const auto &l : link) {
            arr[i++] = l.ToJson();
        }
        obj[as_wstring_on_win32("link")] = arr;
    }
    obj[as_wstring_on_win32("total")] = web::json::value::number(entries.size());
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
    return obj;
}

FhirBundle FhirBundle::Parse(const web::json::value &obj) {
    FhirBundle bundle{};

    if (!bundle.ParseInline(obj)) {
        throw std::exception();
    }

    if (obj.has_string_field(as_wstring_on_win32("type"))) {
        bundle.type = from_wstring_on_win32(obj.at(as_wstring_on_win32("type")).as_string());
    }
    if (obj.has_number_field(as_wstring_on_win32("total"))) {
        bundle.total = obj.at(as_wstring_on_win32("total")).as_number().to_int32();
    }
    if (obj.has_array_field(as_wstring_on_win32("link"))) {
        for (const auto &value : obj.at(as_wstring_on_win32("link")).as_array()) {
            bundle.link.push_back(FhirLink::Parse(value));
        }
    }
    if (obj.has_array_field(as_wstring_on_win32("entry"))) {
        for (const auto &value : obj.at(as_wstring_on_win32("entry")).as_array()) {
            bundle.entries.push_back(FhirBundleEntry::Parse(value));
        }
    }

    return bundle;
}