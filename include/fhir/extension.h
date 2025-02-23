//
// Created by sigsegv on 12/7/23.
//

#ifndef SFMBASISFAKER_EXTENSION_H
#define SFMBASISFAKER_EXTENSION_H

#include "fhirextendable.h"

class FhirExtension : public FhirExtendable {
    friend FhirExtendable;
private:
    std::string url;
public:
    FhirExtension() : url() {}
    explicit FhirExtension(const std::string &url) : url(url) {}
    explicit FhirExtension(std::string &&url) : url(std::move(url)) {}
    virtual ~FhirExtension() = default;
protected:
    void ToJsonInline(json &json) const override;
    [[nodiscard]] virtual json ToJsonObj() const override;
    static std::shared_ptr<FhirExtension> ParseObj(const json &);
public:
    static std::shared_ptr<FhirExtension> ParseJson(const std::string &);
    [[nodiscard]] std::string ToJson() const override;
    [[nodiscard]] std::string GetUrl() const {
        return url;
    }
    void SetUrl(const std::string &url) {
        this->url = url;
    }
};

#endif //SFMBASISFAKER_EXTENSION_H
