//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_BUNDLE_H
#define SFMBASISFAKER_BUNDLE_H

#include "value.h"
#include "bundleentry.h"

class FhirBundle : public Fhir {
    friend Fhir;
private:
    std::vector<FhirLink> link{};
    std::vector<FhirBundleEntry> entries{};
    std::string type{};
    int total{0};
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirBundle() : Fhir("Bundle") {}
    void SetType(const std::string &type) {
        this->type = type;
    }
    void AddLink(const std::string &relation, const std::string &url);
    void AddLink(std::string &&relation, std::string &&url);
    void AddEntry(const FhirBundleEntry &entry);
    void AddEntry(FhirBundleEntry &&entry);
    void SetEntries(const std::vector<FhirBundleEntry> &entries);
    [[nodiscard]] std::vector<FhirLink> GetLink() const { return link; }
    [[nodiscard]] std::vector<FhirBundleEntry> GetEntries() const { return entries; }
    [[nodiscard]] std::string GetType() const {
        return type;
    }
    int GetTotal() const { return total; }

protected:
    json ToJsonObj() const override;
    static FhirBundle ParseObj(const json &obj);
public:
    static FhirBundle ParseJson(const std::string &);
};

#endif //SFMBASISFAKER_BUNDLE_H
