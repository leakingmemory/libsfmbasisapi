//
// Created by sigsegv on 1/13/24.
//

#ifndef LIBSFMBASISAPI_FHIRBASIC_H
#define LIBSFMBASISAPI_FHIRBASIC_H

#include "value.h"
#include "dosage.h"
#include "fhirpartofchain.h"

class FhirBasic : public Fhir, public FhirPartOfChain {
private:
    std::vector<FhirIdentifier> identifiers{};
    FhirCodeableConcept code{};
    FhirReference subject{};
    FhirReference author{};
public:
    FhirBasic() : Fhir("Basic") {}

    web::json::value ToJson() const;
    static FhirBasic Parse(const web::json::value &obj);

    [[nodiscard]] std::vector<FhirIdentifier> GetIdentifiers() const { return identifiers; }
    [[nodiscard]] FhirCodeableConcept GetCode() const { return code; }
    [[nodiscard]] FhirReference GetSubject() const { return subject; }
    [[nodiscard]] FhirReference GetAuthor() const { return author; }
    void SetIdentifiers(const std::vector<FhirIdentifier> &identifiers) {
        this->identifiers = identifiers;
    }
    void SetCode(const FhirCodeableConcept &code) {
        this->code = code;
    }
    void SetSubject(const FhirReference &subject) {
        this->subject = subject;
    }
    void SetAuthor(const FhirReference &author) {
        this->author = author;
    }
};

#endif //LIBSFMBASISAPI_FHIRBASIC_H
