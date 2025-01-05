//
// Created by jeo on 12/7/23.
//

#include <fhir/medication.h>

#include "../win32/w32strings.h"

FhirIngredient FhirIngredient::Parse(const web::json::value &obj) {
    FhirIngredient ingredient{};
    if (!ingredient.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_object_field(as_wstring_on_win32("itemReference"))) {
        ingredient.itemReference = FhirReference::Parse(obj.at(as_wstring_on_win32("itemReference")));
    }
    if (obj.has_boolean_field(as_wstring_on_win32("isActive"))) {
        ingredient.isActive = obj.at(as_wstring_on_win32("isActive")).as_bool();
    }
    if (obj.has_object_field(as_wstring_on_win32("strength"))) {
        ingredient.strength = FhirRatio::Parse(obj.at(as_wstring_on_win32("strength")));
    }
    return ingredient;
}

web::json::value FhirIngredient::ToJson() const {
    web::json::value val = FhirExtendable::ToJson();
    if (itemReference.IsSet()) {
        val[as_wstring_on_win32("itemReference")] = itemReference.ToJson();
    }
    val[as_wstring_on_win32("isActive")] = web::json::value::boolean(isActive);
    if (strength.IsSet()) {
        val[as_wstring_on_win32("strength")] = strength.ToJson();
    }
    return val;
}

FhirMedication FhirMedication::Parse(const web::json::value &obj) {
    FhirMedication medication{};
    if (!medication.ParseInline(obj)) {
        throw std::exception();
    }
    if (obj.has_field(as_wstring_on_win32("identifier"))) {
        const auto arr = obj.at(as_wstring_on_win32("identifier")).as_array();
        for (const auto &id : arr) {
            medication.identifiers.push_back(FhirIdentifier::Parse(id));
        }
    }
    if (obj.has_object_field(as_wstring_on_win32("code"))) {
        medication.code = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("code")));
    }
    if (obj.has_object_field(as_wstring_on_win32("form"))) {
        medication.form = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("form")));
    }
    if (obj.has_object_field(as_wstring_on_win32("amount"))) {
        medication.amount = FhirRatio::Parse(obj.at(as_wstring_on_win32("amount")));
    }
    if (obj.has_array_field(as_wstring_on_win32("ingredient"))) {
        for (const auto &ingredient : obj.at(as_wstring_on_win32("ingredient")).as_array()) {
            medication.ingredients.emplace_back(FhirIngredient::Parse(ingredient));
        }
        medication.hasIngredients = true;
    }
    return medication;
}

web::json::value FhirMedication::ToJson() const {
    web::json::value val = Fhir::ToJson();
    val[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("Medication"));
    if (!identifiers.empty()) {
        auto arr = web::json::value::array(identifiers.size());
#ifdef WIN32
        decltype(identifiers.size()) i = 0;
#else
        typeof(identifiers.size()) i = 0;
#endif
        for (const auto &id : identifiers) {
            arr[i++] = id.ToJson();
        }
        val[as_wstring_on_win32("identifier")] = arr;
    }
    if (code.IsSet()) {
        val[as_wstring_on_win32("code")] = code.ToJson();
    }
    if (form.IsSet()) {
        val[as_wstring_on_win32("form")] = form.ToJson();
    }
    if (amount.IsSet()) {
        val[as_wstring_on_win32("amount")] = amount.ToJson();
    }
    if (hasIngredients) {
        web::json::value ingArr = web::json::value::array(ingredients.size());
        for (size_t i = 0; i < ingredients.size(); i++) {
            ingArr[i] = ingredients[i].ToJson();
        }
        val[as_wstring_on_win32("ingredient")] = ingArr;
    }
    return val;
}

std::string FhirMedication::GetDisplay() const {
    if (!name.empty()) {
        return name;
    }
    return Fhir::GetDisplay();
}