//
// Created by sigsegv on 1/13/24.
//

#ifndef LIBSFMBASISAPI_ALLERGY_H
#define LIBSFMBASISAPI_ALLERGY_H

#include "value.h"
#include "dosage.h"

class FhirReaction : public FhirObject {
private:
    std::vector<FhirCodeableConcept> manifestation{};
public:
    web::json::value ToJson() const;
    static FhirReaction Parse(const web::json::value &obj);

    std::vector<FhirCodeableConcept> GetManifestations() const {
        return manifestation;
    }

    void SetManifestation(const std::vector<FhirCodeableConcept> &manifestation) {
        this->manifestation = manifestation;
    }
};

class FhirAllergyIntolerance : public Fhir {
private:
    std::vector<FhirIdentifier> identifier{};
    std::vector<FhirReaction> reaction{};
    std::vector<std::string> category{};
    FhirCodeableConcept clinicalStatus{};
    FhirCodeableConcept code{};
    FhirCodeableConcept verificationStatus{};
    FhirReference patient{};
    FhirReference recorder{};
    std::string criticality{};
    std::string recordedDate{};
public:
    FhirAllergyIntolerance() : Fhir("AllergyIntolerance") {}
    web::json::value ToJson() const;
    static FhirAllergyIntolerance Parse(const web::json::value &obj);

    std::vector<FhirIdentifier> GetIdentifiers() const {
        return identifier;
    }

    std::vector<FhirReaction> GetReactions() const {
        return reaction;
    }

    std::vector<std::string> GetCategories() const {
        return category;
    }

    FhirCodeableConcept GetClinicalStatus() const {
        return clinicalStatus;
    }

    FhirCodeableConcept GetCode() const {
        return code;
    }

    FhirCodeableConcept GetVerificationStatus() const {
        return verificationStatus;
    }

    FhirReference GetPatient() const {
        return patient;
    }

    FhirReference GetRecorder() const {
        return recorder;
    }

    std::string GetCriticality() const {
        return criticality;
    }

    std::string GetRecordedDate() const {
        return recordedDate;
    }

    void SetIdentifiers(const std::vector<FhirIdentifier>& newIdentifiers) {
        identifier = newIdentifiers;
    }

    void SetReactions(const std::vector<FhirReaction>& newReactions) {
        reaction = newReactions;
    }

    void SetCategories(const std::vector<std::string>& newCategories) {
        category = newCategories;
    }

    void SetClinicalStatus(const FhirCodeableConcept& newStatus) {
        clinicalStatus = newStatus;
    }

    void SetCode(const FhirCodeableConcept& newCode) {
        code = newCode;
    }

    void SetVerificationStatus(const FhirCodeableConcept& newStatus) {
        verificationStatus = newStatus;
    }

    void SetPatient(const FhirReference& newPatient) {
        patient = newPatient;
    }

    void SetRecorder(const FhirReference& newRecorder) {
        recorder = newRecorder;
    }

    void SetCriticality(const std::string& newCriticality) {
        criticality = newCriticality;
    }

    void SetRecordedDate(const std::string& newDate) {
        recordedDate = newDate;
    }
};

#endif //LIBSFMBASISAPI_ALLERGY_H