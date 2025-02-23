//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_BUNDLEENTRY_H
#define SFMBASISFAKER_BUNDLEENTRY_H

#include "fhirobject.h"
#include "fhirconcepts.h"
#include <memory>

class Fhir;
class FhirReference;
class FhirBundle;

class FhirBundleEntry : public FhirObject {
    friend FhirBundle;
private:
    std::string fullUrl;
    std::shared_ptr<Fhir> resource;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirBundleEntry() : fullUrl(), resource() {}
    template <FhirSubclass T> FhirBundleEntry(const std::string &url, const std::shared_ptr<T> &entry)
        : fullUrl(url), resource(entry) {}
    template <FhirSubclass T> FhirBundleEntry(std::string &&url, const std::shared_ptr<T> &entry)
            : fullUrl(url), resource(entry) {}
    template <FhirSubclass T> static FhirBundleEntry Create(const std::string &url) {
        return FhirBundleEntry(url, std::make_shared<T>());
    }
    template <FhirSubclass T> static FhirBundleEntry Create (std::string &&url) {
        return FhirBundleEntry(std::move(url), std::make_shared<T>());
    }
    [[nodiscard]] std::string GetFullUrl() const {
        return fullUrl;
    }
    void SetFullUrl(const std::string url) {
        fullUrl = url;
    }
    [[nodiscard]] std::shared_ptr<Fhir> GetResource() const {
        return resource;
    }
    void SetResource(const std::shared_ptr<Fhir> &res) {
        resource = res;
    }
protected:
    json ToJsonObj() const;
    static FhirBundleEntry Parse(const json &obj);
public:
    FhirReference CreateReference(const std::string &type) const;
};

#endif //SFMBASISFAKER_BUNDLEENTRY_H
