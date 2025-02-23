//
// Created by sigsegv on 12/7/23.
//

#ifndef SFMBASISFAKER_FHIREXTENDABLE_H
#define SFMBASISFAKER_FHIREXTENDABLE_H

#include "fhirobject.h"
#include "fhirconcepts.h"
#include <vector>

class FhirExtension;

class FhirExtendable : public FhirObject {
private:
    std::vector<std::shared_ptr<FhirExtension>> extensions{};
protected:
    bool ParseInline(const json &json);
    void ToJsonInline(json &json) const override;
    [[nodiscard]] json ToJsonObj() const override;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirExtendable() {}
    virtual ~FhirExtendable() = default;
    [[nodiscard]] std::string ToJson() const override;
    [[nodiscard]] std::vector<std::shared_ptr<FhirExtension>> GetExtensions() const {
        return extensions;
    }
    void SetExtensions(const std::vector<std::shared_ptr<FhirExtension>> &exts) {
        extensions = exts;
    }
    void SetExtensions(std::vector<std::shared_ptr<FhirExtension>> &&exts) {
        extensions = std::move(exts);
    }
    void AddExtension(const std::shared_ptr<FhirExtension> &extension) {
        extensions.emplace_back(extension);
    }
};

#endif //SFMBASISFAKER_FHIREXTENDABLE_H
