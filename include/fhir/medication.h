//
// Created by jeo on 12/7/23.
//

#ifndef SFMBASISFAKER_MEDICATION_H
#define SFMBASISFAKER_MEDICATION_H

#include "value.h"

class FhirIngredient : public FhirExtendable {
private:
    FhirReference itemReference{};
    FhirRatio strength{};
    bool isActive{false};
public:
    static FhirIngredient Parse(const web::json::value &);
    web::json::value ToJson() const;
    [[nodiscard]] FhirReference GetItemReference() const {
        return itemReference;
    }
    [[nodiscard]] FhirRatio GetStrength() const {
        return strength;
    }
    bool IsActive() const {
        return isActive;
    }

    void SetItemReference(const FhirReference &itemReference) {
        this->itemReference = itemReference;
    }

    void SetStrength(const FhirRatio &strength) {
        this->strength = strength;
    }

    void SetActive(bool isActive) {
        this->isActive = isActive;
    }
};

class FhirMedication : public Fhir {
    FhirCodeableConcept code{};
    FhirCodeableConcept form{};
    FhirRatio amount{};
    std::vector<FhirIngredient> ingredients{};
    bool hasIngredients{false};
public:
    static FhirMedication Parse(const web::json::value &);
    web::json::value ToJson() const;
    [[nodiscard]] FhirCodeableConcept GetCode() const {
        return code;
    }
    [[nodiscard]] FhirCodeableConcept GetForm() const {
        return form;
    }
    [[nodiscard]] FhirRatio GetAmount() const {
        return amount;
    }
    [[nodiscard]] std::vector<FhirIngredient> GetIngredients() const {
        return ingredients;
    }

    void SetCode(const FhirCodeableConcept &code) {
        this->code = code;
    }

    void SetForm(const FhirCodeableConcept &form) {
        this->form = form;
    }

    void SetAmount(const FhirRatio &amount) {
        this->amount = amount;
    }

    void SetIngredients(const std::vector<FhirIngredient> &ingredients) {
        this->ingredients = ingredients;
    }
};

#endif //SFMBASISFAKER_MEDICATION_H
