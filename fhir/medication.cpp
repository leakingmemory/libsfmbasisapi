//
// Created by jeo on 12/7/23.
//

#include <fhir/medication.h>
#include "json.h"

FhirIngredient FhirIngredient::Parse(const json &obj) {
    FhirIngredient ingredient{};
    if (!ingredient.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.contains("itemReference")) {
        ingredient.itemReference = FhirReference::ParseObj(obj["itemReference"]);
    }
    if (obj.contains("isActive")) {
        ingredient.isActive = obj["isActive"];
    }
    if (obj.contains("strength")) {
        ingredient.strength = FhirRatio::ParseObj(obj["strength"]);
    }
    return ingredient;
}

json FhirIngredient::ToJsonObj() const {
    auto val = FhirExtendable::ToJsonObj();
    if (itemReference.IsSet()) {
        val["itemReference"] = itemReference.ToJsonObj();
    }
    val["isActive"] = isActive;
    if (strength.IsSet()) {
        val["strength"] = strength.ToJsonObj();
    }
    return val;
}

FhirMedication FhirMedication::ParseObj(const json &obj) {
    FhirMedication medication{};
    if (!medication.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.contains("identifier") && obj["identifier"].is_array()) {
        const auto arr = obj["identifier"];
        for (const auto &id : arr) {
            medication.identifiers.push_back(FhirIdentifier::ParseObj(id));
        }
    }
    if (obj.contains("code") && obj["code"].is_object()) {
        medication.code = FhirCodeableConcept::Parse(obj["code"]);
    }
    if (obj.contains("form") && obj["form"].is_object()) {
        medication.form = FhirCodeableConcept::Parse(obj["form"]);
    }
    if (obj.contains("amount") && obj["amount"].is_object()) {
        medication.amount = FhirRatio::ParseObj(obj["amount"]);
    }
    if (obj.contains("ingredient") && obj["ingredient"].is_array()) {
        for (const auto &ingredient : obj["ingredient"]) {
            medication.ingredients.emplace_back(FhirIngredient::Parse(ingredient));
        }
        medication.hasIngredients = true;
    }
    return medication;
}

FhirMedication FhirMedication::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

json FhirMedication::ToJsonObj() const {
    auto val = Fhir::ToJsonObj();
    val["resourceType"] = "Medication";
    if (!identifiers.empty()) {
        auto arr = nlohmann::json::array();
        decltype(identifiers.size()) i = 0;
        for (const auto &id : identifiers) {
            arr.push_back(id.ToJsonObj());
        }
        val["identifier"] = arr;
    }
    if (code.IsSet()) {
        val["code"] = code.ToJsonObj();
    }
    if (form.IsSet()) {
        val["form"] = form.ToJsonObj();
    }
    if (amount.IsSet()) {
        val["amount"] = amount.ToJsonObj();
    }
    if (hasIngredients) {
        auto ingArr = nlohmann::json::array();
        for (size_t i = 0; i < ingredients.size(); i++) {
            ingArr.push_back(ingredients[i].ToJsonObj());
        }
        val["ingredient"] = ingArr;
    }
    return val;
}

std::string FhirMedication::GetDisplay() const {
    if (!name.empty()) {
        return name;
    }
    return Fhir::GetDisplay();
}