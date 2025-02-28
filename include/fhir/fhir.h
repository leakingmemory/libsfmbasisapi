//
// Created by jeo on 12/7/23.
//

#ifndef SFMBASISFAKER_FHIR_H
#define SFMBASISFAKER_FHIR_H

#include <string>
#include <vector>
#include <memory>
#include "extension.h"
#include "fhirconcepts.h"

class FhirValueException : public std::exception {
private:
    std::string property;
    std::string error;
    std::string whatStr;
public:
    FhirValueException(const std::string &property, const std::string &error)
    : property(property), error(error), whatStr(error) {
        whatStr.append(" (");
        whatStr.append(property);
        whatStr.append(")");
    }
    const char * what() const noexcept override {
        return whatStr.c_str();
    }
};

enum class FhirStatus {
    NOT_SET,
    ACTIVE,
    FINAL,
    COMPLETED,
    STOPPED
};

class FhirValue : public FhirObject {
    friend FhirExtension;
    friend FhirParameter;
public:
    constexpr FhirValue() {}
    virtual std::string GetPropertyName() const = 0;
protected:
    static std::shared_ptr<FhirValue> ParseObj(const std::string &propertyName, const json &property);
public:
    static std::shared_ptr<FhirValue> ParseJson(const std::string &propertyName, const std::string &property);
};

class FhirValueExtension : public FhirExtension {
private:
    std::shared_ptr<FhirValue> value;
public:
    FhirValueExtension() = default;
    FhirValueExtension(const std::string &url, const std::shared_ptr<FhirValue> &value) : FhirExtension(url), value(value) {}
    FhirValueExtension(std::string &&url, std::shared_ptr<FhirValue> &&value) : FhirExtension(std::move(url)), value(std::move(value)) {}
    [[nodiscard]] std::shared_ptr<FhirValue> GetValue() const {
        return value;
    }
    void SetValue(const std::shared_ptr<FhirValue> &v) {
        value = v;
    }
    void SetValue(std::shared_ptr<FhirValue> &&v) {
        value = std::move(v);
    }
protected:
    [[nodiscard]] json ToJsonObj() const override;
public:
    [[nodiscard]] std::string ToJson() const override;
};

class FhirGenericExtension : public FhirExtension {
private:
    std::string json;
public:
    FhirGenericExtension() : json() {}
    FhirGenericExtension(const std::string &url, const std::string &json);
protected:
    struct json ToJsonObj() const override;
public:
    std::string ToJson() const override;
};

class FhirBundleEntry;
class FhirParameter;

class Fhir : public FhirExtendable {
    friend FhirBundleEntry;
    friend FhirParameter;
private:
    std::string resourceType;
    std::string id{};
    std::string lastUpdated{};
    std::string source{};
    std::vector<std::string> profile{};
    std::string timestamp{};
    std::string date{};
    FhirStatus status{FhirStatus::NOT_SET};
protected:
    bool ParseInline(const json &json);
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING Fhir() : resourceType() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit Fhir(const std::string &resourceType) : resourceType(resourceType) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit Fhir(std::string &&resourceType) : resourceType(std::move(resourceType)) {}
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<Fhir> ParseObj(const json &obj);
public:
    static std::shared_ptr<Fhir> ParseJson(const std::string &);
    std::string ToJson() const override;
    virtual std::string GetDisplay() const;
    virtual ~Fhir() = default;
    [[nodiscard]] std::string GetResourceType() const {
        return resourceType;
    }
    [[nodiscard]] std::string GetId() const {
        return id;
    }
    [[nodiscard]] std::string GetLastUpdated() const {
        return lastUpdated;
    }
    [[nodiscard]] std::string GetSource() const {
        return source;
    }
    [[nodiscard]] std::vector<std::string> GetProfile() const {
        return profile;
    }
    [[nodiscard]] std::string GetTimestamp() const {
        return timestamp;
    }
    [[nodiscard]] std::string GetDate() const {
        return date;
    }
    [[nodiscard]] FhirStatus GetStatus() const {
        return status;
    }
    void SetId(const std::string &id) {
        this->id = id;
    }
    void SetLastUpdated(const std::string &lastUpdated) {
        this->lastUpdated = lastUpdated;
    }
    void SetSource(const std::string &source) {
        this->source = source;
    }
    void SetProfile(const std::string &profile) {
        this->profile = { profile };
    }
    void SetTimestamp(const std::string ts) {
        timestamp = ts;
    }
    void SetDate(const std::string &d) {
        date = d;
    }
    void SetStatus(FhirStatus status) {
        this->status = status;
    }
};

#endif //SFMBASISFAKER_FHIR_H
