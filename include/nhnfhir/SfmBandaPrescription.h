//
// Created by sigsegv on 2/7/25.
//

#ifndef LIBSFMBASISAPI_SFMBANDAPRESCRIPTION_H
#define LIBSFMBASISAPI_SFMBANDAPRESCRIPTION_H

#include "../fhir/fhirbasic.h"

class SfmBandaPrescription : public FhirBasic {
public:
    SfmBandaPrescription();
    SfmBandaPrescription(const FhirBasic &);
    SfmBandaPrescription(FhirBasic &&);
    void SetProductGroup(const FhirCodeableConcept &codeable);
    FhirCodeableConcept GetProductGroup() const;
    std::string GetDisplay() const override;
};

#endif //LIBSFMBASISAPI_SFMBANDAPRESCRIPTION_H
