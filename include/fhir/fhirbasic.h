//
// Created by sigsegv on 1/13/24.
//

#ifndef LIBSFMBASISAPI_FHIRBASIC_H
#define LIBSFMBASISAPI_FHIRBASIC_H

#include "value.h"
#include "dosage.h"

class FhirBasic : public Fhir {
private:
    std::vector<FhirIdentifier> identifiers{};
    FhirReference subject{};
public:
    FhirBasic() : Fhir("Basic") {}

    web::json::value ToJson() const;
    static FhirBasic Parse(const web::json::value &obj);

    std::vector<FhirIdentifier> GetIdentifiers() const { return identifiers; }
    FhirReference GetSubject() const { return subject; }
};

#endif //LIBSFMBASISAPI_FHIRBASIC_H
