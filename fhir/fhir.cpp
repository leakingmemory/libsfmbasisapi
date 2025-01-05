//
// Created by jeo on 12/7/23.
//

#include <fhir/fhir.h>
#ifdef WIN32
#include "../win32/w32strings.h"
#endif

web::json::value FhirValueExtension::ToJson() const {
    auto obj = FhirExtension::ToJson();
    if (value) {
        obj[as_wstring_on_win32(value->GetPropertyName())] = value->ToJson();
    }
    return obj;
}

FhirGenericExtension::FhirGenericExtension(const std::string &url, const web::json::value &json) : FhirExtension(url), json(json) {
    if (json.has_string_field(as_wstring_on_win32("url"))) {
        SetUrl(from_wstring_on_win32(json.at(as_wstring_on_win32("url")).as_string()));
    }
}

web::json::value FhirGenericExtension::ToJson() const {
    web::json::value v = web::json::value::parse(json.serialize());
    FhirExtension::ToJsonInline(v);
    return v;
}


bool Fhir::ParseInline(const web::json::value &json) {
    if (!FhirExtendable::ParseInline(json)) {
        return false;
    }
    if (json.has_string_field(as_wstring_on_win32("resourceType"))) {
        resourceType = from_wstring_on_win32(json.at(as_wstring_on_win32("resourceType")).as_string());
    }
    if (json.has_string_field(as_wstring_on_win32("id"))) {
        id = from_wstring_on_win32(json.at(as_wstring_on_win32("id")).as_string());
    }
    if (json.has_object_field(as_wstring_on_win32("meta"))) {
        auto meta = json.at(as_wstring_on_win32("meta"));
        if (meta.has_string_field(as_wstring_on_win32("lastUpdated"))) {
            lastUpdated = from_wstring_on_win32(meta.at(as_wstring_on_win32("lastUpdated")).as_string());
        }
        if (meta.has_string_field(as_wstring_on_win32("source"))) {
            source = from_wstring_on_win32(meta.at(as_wstring_on_win32("source")).as_string());
        }
        if (meta.has_array_field(as_wstring_on_win32("profile"))) {
            for (const auto &p : meta.at(as_wstring_on_win32("profile")).as_array()) {
                if (p.is_string()) {
                    profile.emplace_back(from_wstring_on_win32(p.as_string()));
                }
            }
        }
    }
    if (json.has_string_field(as_wstring_on_win32("timestamp"))) {
        timestamp = from_wstring_on_win32(json.at(as_wstring_on_win32("timestamp")).as_string());
    }
    if (json.has_string_field(as_wstring_on_win32("date"))) {
        date = from_wstring_on_win32(json.at(as_wstring_on_win32("date")).as_string());
    }
    if (json.has_string_field(as_wstring_on_win32("status"))) {
        auto s = from_wstring_on_win32(json.at(as_wstring_on_win32("status")).as_string());
        if (s == "active") {
            status = FhirStatus::ACTIVE;
        } else if (s == "final") {
            status = FhirStatus::FINAL;
        } else if (s == "completed") {
            status = FhirStatus::COMPLETED;
        } else if (s == "stopped") {
            status = FhirStatus::STOPPED;
        } else {
            throw std::exception();
        }
    }
    return true;
}

web::json::value Fhir::ToJson() const {
    auto obj = FhirExtendable::ToJson();
    if (!resourceType.empty()) {
        obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32(resourceType));
    }
    if (!id.empty()) {
        obj[as_wstring_on_win32("id")] = web::json::value::string(as_wstring_on_win32(id));
    }
    if (!profile.empty()) {
        auto meta = web::json::value::object();
        {
            if (!lastUpdated.empty()) {
                meta[as_wstring_on_win32("lastUpdated")] = web::json::value::string(as_wstring_on_win32(lastUpdated));
            }
            if (!source.empty()) {
                meta[as_wstring_on_win32("source")] = web::json::value::string(as_wstring_on_win32(source));
            }
            auto arr = web::json::value::array(profile.size());
#ifdef WIN32
            decltype(profile.size()) i = 0;
#else
            typeof(profile.size()) i = 0;
#endif
            for (const auto &p: profile) {
                arr[i++] = web::json::value::string(as_wstring_on_win32(p));
            }
            meta[as_wstring_on_win32("profile")] = arr;
        }
        obj[as_wstring_on_win32("meta")] = meta;
    }
    if (!timestamp.empty()) {
        obj[as_wstring_on_win32("timestamp")] = web::json::value::string(as_wstring_on_win32(timestamp));
    }
    if (!date.empty()) {
        obj[as_wstring_on_win32("date")] = web::json::value::string(as_wstring_on_win32(date));
    }
    switch (status) {
        case FhirStatus::NOT_SET:
            break;
        case FhirStatus::ACTIVE:
            obj[as_wstring_on_win32("status")] = web::json::value::string(as_wstring_on_win32("active"));
            break;
        case FhirStatus::FINAL:
            obj[as_wstring_on_win32("status")] = web::json::value::string(as_wstring_on_win32("final"));
            break;
        case FhirStatus::COMPLETED:
            obj[as_wstring_on_win32("status")] = web::json::value::string(as_wstring_on_win32("completed"));
            break;
        case FhirStatus::STOPPED:
            obj[as_wstring_on_win32("status")] = web::json::value::string(as_wstring_on_win32("stopped"));
            break;
    }
    return obj;
}

std::string Fhir::GetDisplay() const {
    return !id.empty() ? id : "Display";
}
