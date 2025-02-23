//
// Created by jeo on 12/7/23.
//

#include <fhir/fhir.h>
#include "json.h"

json FhirValueExtension::ToJsonObj() const {
    auto obj = FhirExtension::ToJsonObj();
    if (value) {
        auto sub = value->ToJsonObj();
        obj[value->GetPropertyName()] = static_cast<const nlohmann::json &>(sub);
    }
    return obj;
}

std::string FhirValueExtension::ToJson() const {
    return ToJsonObj().dump();
}

FhirGenericExtension::FhirGenericExtension(const std::string &url, const std::string &json) : FhirExtension(url), json(json) {
    auto obj = json::parse(json);
    if (obj.contains("url")) {
        SetUrl(obj["url"]);
    }
}

json FhirGenericExtension::ToJsonObj() const {
    struct json v{json::parse(json)};
    FhirExtension::ToJsonInline(v);
    return v;
}

std::string FhirGenericExtension::ToJson() const {
    return ToJsonObj().dump();
}


bool Fhir::ParseInline(const json &json) {
    if (!FhirExtendable::ParseInline(json)) {
        return false;
    }
    if (json.contains("resourceType")) {
        resourceType = json["resourceType"];
    }
    if (json.contains("id")) {
        id = json["id"];
    }
    if (json.contains("meta")) {
        auto meta = json["meta"];
        if (meta.contains("lastUpdated")) {
            lastUpdated = meta["lastUpdated"];
        }
        if (meta.contains("source")) {
            source = meta["source"];
        }
        if (meta.contains("profile")) {
            auto profileArr = meta["profile"];
            if (profileArr.is_array()) {
                for (const auto &p: profileArr) {
                    if (p.is_string()) {
                        std::string str = p;
                        profile.emplace_back(str);
                    }
                }
            }
        }
    }
    if (json.contains("timestamp")) {
        timestamp = json["timestamp"];
    }
    if (json.contains("date")) {
        date = json["date"];
    }
    if (json.contains("status")) {
        std::string s = json["status"];
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

json Fhir::ToJsonObj() const {
    auto obj = FhirExtendable::ToJsonObj();
    if (!resourceType.empty()) {
        obj["resourceType"] = resourceType;
    }
    if (!id.empty()) {
        obj["id"] = id;
    }
    if (!profile.empty()) {
        auto meta = nlohmann::json::object();
        {
            if (!lastUpdated.empty()) {
                meta["lastUpdated"] = lastUpdated;
            }
            if (!source.empty()) {
                meta["source"] = source;
            }
            auto arr = nlohmann::json::array();
            decltype(profile.size()) i = 0;
            for (const auto &p: profile) {
                arr.push_back(p);
            }
            meta["profile"] = arr;
        }
        obj["meta"] = meta;
    }
    if (!timestamp.empty()) {
        obj["timestamp"] = timestamp;
    }
    if (!date.empty()) {
        obj["date"] = date;
    }
    switch (status) {
        case FhirStatus::NOT_SET:
            break;
        case FhirStatus::ACTIVE:
            obj["status"] = "active";
            break;
        case FhirStatus::FINAL:
            obj["status"] = "final";
            break;
        case FhirStatus::COMPLETED:
            obj["status"] = "completed";
            break;
        case FhirStatus::STOPPED:
            obj["status"] = "stopped";
            break;
    }
    return obj;
}

std::string Fhir::ToJson() const {
    return ToJsonObj().dump();
}

std::string Fhir::GetDisplay() const {
    return !id.empty() ? id : "Display";
}
