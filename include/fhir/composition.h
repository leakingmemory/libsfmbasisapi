//
// Created by jeo on 08.12.2023.
//

#ifndef SFMBASISFAKER_COMPOSITION_H
#define SFMBASISFAKER_COMPOSITION_H

#include "fhir.h"
#include "value.h"
#include "compositionsection.h"

class FhirAttester {
    friend FhirComposition;
private:
    std::string mode{};
    std::string dateTime{};
    FhirReference party{};
public:
    [[nodiscard]] std::string GetMode() const;
    void SetMode(const std::string &);
    [[nodiscard]] std::string GetDateTime() const;
    void SetDateTime(const std::string &dateTime);
    [[nodiscard]] FhirReference GetParty() const;
    void SetParty(const FhirReference &);
protected:
    [[nodiscard]] json ToJsonObj() const;
    static FhirAttester Parse(const json &obj);
};

class FhirComposition : public Fhir {
    friend Fhir;
private:
    FhirIdentifier identifier{};
    FhirCodeableConcept type{};
    FhirReference subject{};
    std::vector<FhirReference> authors{};
    std::vector<FhirCompositionSection> sections{};
    std::string title{};
    std::string confidentiality{};
    std::string relatesToCode{};
    FhirIdentifier relatesTo{};
    std::vector<FhirAttester> attester{};
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirComposition() : Fhir("Composition") {}
    [[nodiscard]] FhirIdentifier GetIdentifier() const { return identifier; }
    [[nodiscard]] FhirCodeableConcept GetType() const { return type; }
    [[nodiscard]] FhirReference GetSubject() const { return subject; }
    [[nodiscard]] std::vector<FhirReference> GetAuthors() const { return authors; }
    [[nodiscard]] std::vector<FhirCompositionSection> GetSections() const { return sections; }
    [[nodiscard]] std::string GetTitle() const { return title; }
    [[nodiscard]] std::string GetConfidentiality() const { return confidentiality; }
    [[nodiscard]] std::string GetRelatesToCode() const { return relatesToCode; }
    [[nodiscard]] FhirIdentifier GetRelatesTo() const { return relatesTo; }
    [[nodiscard]] std::vector<FhirAttester> GetAttester() const { return attester; }

    void SetIdentifier(const FhirIdentifier &identifier) { this->identifier = identifier; }
    void SetType(const FhirCodeableConcept &type) { this->type = type; }
    void SetSubject(const FhirReference &subject) { this->subject = subject; }
    void SetAuthors(const std::vector<FhirReference> &authors) { this->authors = authors; }
    void AddAuthor(const FhirReference &author) { this->authors.push_back(author); }
    void SetSections(const std::vector<FhirCompositionSection> &sections) { this->sections = sections; }
    void AddSection(const FhirCompositionSection &section) { this->sections.push_back(section); }
    void SetTitle(const std::string &title) { this->title = title; }
    void SetConfidentiality(const std::string &confidentiality) { this->confidentiality = confidentiality; }
    void SetRelatesToCode(const std::string &code) { this->relatesToCode = code; }
    void SetRelatesTo(const FhirIdentifier &relatesTo) { this->relatesTo = relatesTo; }
    void SetAttester(const std::vector<FhirAttester> &attester) { this->attester = attester; }
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirComposition Parse(const json &obj);
};

#endif //SFMBASISFAKER_COMPOSITION_H
