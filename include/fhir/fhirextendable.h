//
// Created by sigsegv on 12/7/23.
//

#ifndef SFMBASISFAKER_FHIREXTENDABLE_H
#define SFMBASISFAKER_FHIREXTENDABLE_H

#include "fhirobject.h"
#include "fhirconcepts.h"

class FhirExtension;

class FhirExtendable : public FhirObject {
private:
    std::vector<std::shared_ptr<FhirExtension>> extensions{};
protected:
    bool ParseInline(const web::json::value &json);
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirExtendable() {}
    void ToJsonInline(web::json::value &json) const override;
    web::json::value ToJson() const;
    virtual ~FhirExtendable() = default;
    [[nodiscard]] std::vector<std::shared_ptr<FhirExtension>> GetExtensions() const {
        return extensions;
    }
    void AddExtension(const std::shared_ptr<FhirExtension> &extension) {
        extensions.emplace_back(extension);
    }
};

#endif //SFMBASISFAKER_FHIREXTENDABLE_H
