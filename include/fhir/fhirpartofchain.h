//
// Created by sigsegv on 9/6/24.
//

#ifndef LIBSFMBASISAPI_FHIRPARTOFCHAIN_H
#define LIBSFMBASISAPI_FHIRPARTOFCHAIN_H

#include "value.h"
#include <vector>

class FhirPartOfChain {
private:
    std::vector<FhirReference> partOf{};
    std::vector<FhirReference> basedOn{};
protected:
    void ToJsonInline(json &json) const;
    void ParseInline(const json &json);
public:
    [[nodiscard]] std::vector<FhirReference> GetPartOf() const {
        return partOf;
    }

    void SetPartOf(const std::vector<FhirReference> &partOf) {
        this->partOf = partOf;
    }

    [[nodiscard]] std::vector<FhirReference> GetBasedOn() const {
        return basedOn;
    }

    void SetBasedOn(const std::vector<FhirReference> &basedOn) {
        this->basedOn = basedOn;
    }
};

#endif //LIBSFMBASISAPI_FHIRPARTOFCHAIN_H
