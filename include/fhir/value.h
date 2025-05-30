//
// Created by jeo on 12/7/23.
//

#ifndef SFMBASISFAKER_VALUE_H
#define SFMBASISFAKER_VALUE_H

#include "fhir.h"
#include <cmath>

class FhirString : public FhirValue {
    friend FhirValue;
private:
    std::string value;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirString() noexcept : value() {}
    explicit LIBSFMBASISAPI_CONSTEXPR_STRING FhirString(const std::string &value) noexcept : value(value) {}
    explicit LIBSFMBASISAPI_CONSTEXPR_STRING FhirString(std::string &&value) noexcept : value(std::move(value)) {}
    static std::string PropertyName() {
        return "valueString";
    }
    std::string GetPropertyName() const override;
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<FhirString> Parse(const json &value);
public:
    std::string GetValue() const {
        return value;
    }
};

class FhirCode : public FhirString {
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCode() noexcept : FhirString() {}
    explicit LIBSFMBASISAPI_CONSTEXPR_STRING FhirCode(const std::string &value) noexcept : FhirString(value) {}
    explicit LIBSFMBASISAPI_CONSTEXPR_STRING FhirCode(std::string &&value) noexcept : FhirString(std::move(value)) {}
    static std::string PropertyName() {
        return "valueCode";
    }
    std::string GetPropertyName() const override;
    static std::shared_ptr<FhirCode> Parse(const json &value);
};

class FhirCodeableConcept;

class FhirCoding : public FhirObject {
    friend FhirCodeableConcept;
private:
    std::string system;
    std::string code;
    std::string display;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCoding() : system(), code(), display() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCoding(const std::string &system, const std::string &code, const std::string &display) :
        system(system), code(code), display(display) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCoding(std::string &&system, std::string &&code, std::string &&display) :
            system(std::move(system)), code(std::move(code)), display(std::move(display)) {}
protected:
    json ToJsonObj() const override;
    static FhirCoding ParseObj(const json &obj);
public:
    static FhirCoding ParseJson(const std::string &);
    std::string GetSystem() const {
        return system;
    }
    std::string GetCode() const {
        return code;
    }
    std::string GetDisplay() const {
        return display;
    }
};

class FhirIdentifier;
class FhirMedication;
class FhirCompositionSection;
class FhirComposition;
class FhirSubstance;
class FhirBasic;
class FhirPractitionerRole;
class FhirReaction;
class FhirAllergyIntolerance;
class FhirOperationOutcome;
class FhirMedicationDispense;

class FhirCodeableConcept : public FhirExtendable {
    friend FhirIdentifier;
    friend FhirMedication;
    friend FhirCompositionSection;
    friend FhirComposition;
    friend FhirSubstance;
    friend FhirBasic;
    friend FhirPractitionerRole;
    friend FhirReaction;
    friend FhirAllergyIntolerance;
    friend FhirOperationOutcome;
    friend FhirMedicationDispense;
private:
    std::vector<FhirCoding> coding;
    std::string text;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCodeableConcept() : coding(), text() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConcept(const std::vector<FhirCoding> &coding) : coding(coding), text() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConcept(std::vector<FhirCoding> &&coding) : coding(std::move(coding)), text() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConcept(std::vector<FhirCoding> &&coding, std::string &&text) : coding(std::move(coding)), text(std::move(text)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConcept(const std::string &system, const std::string &code, const std::string &name)
    : coding({{system, code, name}}), text() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConcept(std::string &&system, std::string &&code, std::string &&name)
            : coding({{std::move(system), std::move(code), std::move(name)}}), text() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConcept(const std::string &text) : coding(), text(text) {}
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirCodeableConcept Parse(const json &obj);
public:
    [[nodiscard]] std::vector<FhirCoding> GetCoding() const {
        return coding;
    }
    [[nodiscard]] std::string GetText() const {
        return text;
    }
    [[nodiscard]] bool IsSet() const {
        return !coding.empty() || !text.empty();
    }
};

class FhirCodingValue : public FhirValue, public FhirCoding {
    friend FhirValue;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCodingValue() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodingValue(const std::string &system, const std::string &code, const std::string &display) : FhirCoding(system, code, display) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodingValue(std::string &&system, std::string &&code, std::string &&display) : FhirCoding(std::move(system), std::move(code), std::move(display)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodingValue(const FhirCoding &cc) : FhirCoding(cc) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodingValue(FhirCoding &&cc) : FhirCoding(std::move(cc)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING static std::string PropertyName() {
        return "valueCoding";
    }
    std::string GetPropertyName() const override;
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static std::shared_ptr<FhirCodingValue> Parse(const json &obj);
};

class FhirCodeableConceptValue : public FhirValue, public FhirCodeableConcept {
    friend FhirValue;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirCodeableConceptValue() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConceptValue(const std::vector<FhirCoding> &coding) : FhirCodeableConcept(coding) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConceptValue(std::vector<FhirCoding> &&coding) : FhirCodeableConcept(coding) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConceptValue(const std::string &text) : FhirCodeableConcept(text) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConceptValue(const FhirCodeableConcept &cc) : FhirCodeableConcept(cc) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirCodeableConceptValue(FhirCodeableConcept &&cc) : FhirCodeableConcept(std::move(cc)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING static std::string PropertyName() {
        return "valueCodeableConcept";
    }
    std::string GetPropertyName() const override;
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static std::shared_ptr<FhirCodeableConceptValue> Parse(const json &obj);
public:
    [[nodiscard]] std::string ToJson() const override;
};

class FhirRatio;
class FhirMedicationDispense;

class FhirQuantity : public FhirObject {
    friend FhirRatio;
    friend FhirMedicationDispense;
private:
    std::string unit;
    long milliValue;
    bool isSet;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirQuantity() : unit(), milliValue(0), isSet(false) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirQuantity(double value, const std::string &unit) : unit(unit), milliValue((long) floor(value * ((double)1000.0))), isSet(true) {}
    [[nodiscard]] std::string GetUnit() const {
        return unit;
    }
    [[nodiscard]] double GetValue() const {
        return ((double) milliValue) / ((double)1000.0);
    }
    bool IsSet() const {
        return isSet;
    }
protected:
    json ToJsonObj() const;
    static FhirQuantity ParseObj(const json &obj);
public:
    static FhirQuantity ParseJson(const std::string &);
};

class FhirQuantityValue : public FhirValue, public FhirQuantity {
    friend FhirValue;
public:
    explicit LIBSFMBASISAPI_CONSTEXPR_STRING FhirQuantityValue(const FhirQuantity &q) : FhirQuantity(q) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING static std::string PropertyName() {
        return "valueQuantity";
    }
    std::string GetPropertyName() const override;
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static std::shared_ptr<FhirQuantityValue> Parse(const json &obj);
};

class FhirIngredient;

class FhirRatio : public FhirExtendable {
    friend FhirIngredient;
    friend FhirMedication;
private:
    FhirQuantity numerator;
    FhirQuantity denominator;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirRatio() : numerator(), denominator() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirRatio(const FhirQuantity &numerator, const FhirQuantity &denominator)
            : numerator(numerator), denominator(denominator) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirRatio(FhirQuantity &&numerator, FhirQuantity &&denominator)
            : numerator(std::move(numerator)), denominator(std::move(denominator)) {}
    [[nodiscard]] FhirQuantity GetNumerator() const {
        return numerator;
    }
    [[nodiscard]] FhirQuantity GetDenominator() const {
        return denominator;
    }
    bool IsSet() const {
        return numerator.IsSet() || denominator.IsSet();
    }
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirRatio ParseObj(const json &obj);
public:
    static FhirRatio ParseJson(const std::string &);
};

class FhirReference;
class FhirMedication;
class FhirMedicationStatement;
class FhirComposition;
class FhirPerson;
class FhirSubstance;
class FhirOrganization;
class FhirBasic;
class FhirAllergyIntolerance;
class FhirMedicationDispense;

class FhirIdentifier : public FhirObject {
    friend FhirReference;
    friend FhirMedication;
    friend FhirMedicationStatement;
    friend FhirComposition;
    friend FhirPerson;
    friend FhirSubstance;
    friend FhirOrganization;
    friend FhirBasic;
    friend FhirAllergyIntolerance;
    friend FhirMedicationDispense;
private:
    FhirCodeableConcept type;
    std::string use;
    std::string system;
    std::string value;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier() : type(), use(), system(), value() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(const std::string &use, const std::string &value)
            : type(), use(use), system(), value(value) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(std::string &&use, std::string &&value)
            : type(), use(std::move(use)), system(), value(std::move(value)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(const std::string &use, const std::string &system, const std::string &value)
            : type(), use(use), system(system), value(value) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(std::string &&use, std::string &&system, std::string &&value)
            : type(), use(use), system(system), value(value) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(const FhirCodeableConcept &type, const std::string &use, const std::string &value)
        : type(type), use(use), system(), value(value) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(FhirCodeableConcept &&type, std::string &&use, std::string &&value)
        : type(std::move(type)), use(std::move(use)), system(), value(std::move(value)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(const FhirCodeableConcept &type, const std::string &use, const std::string &system, const std::string &value)
            : type(type), use(use), system(system), value(value) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirIdentifier(FhirCodeableConcept &&type, std::string &&use, std::string &&system, std::string &&value)
            : type(std::move(type)), use(std::move(use)), system(std::move(system)), value(std::move(value)) {}
    [[nodiscard]] std::string GetUse() const {
        return use;
    }
    [[nodiscard]] FhirCodeableConcept GetType() const {
        return type;
    }
    [[nodiscard]] std::string GetSystem() const {
        return system;
    }
    [[nodiscard]] std::string GetValue() const {
        return value;
    }
    bool IsSet() const {
        return !use.empty() || type.IsSet() || !system.empty() || !value.empty();
    }
protected:
    json ToJsonObj() const;
    static FhirIdentifier ParseObj(const json &obj);
public:
    static FhirIdentifier ParseJson(const std::string &);
};

class FhirIngredient;
class FhirMedicationStatement;
class FhirCompositionSection;
class FhirAttester;
class FhirComposition;
class FhirBasic;
class FhirPractitionerRole;
class FhirPartOfChain;
class FhirMedicationDispense;

class FhirReference : public FhirValue {
    friend FhirIngredient;
    friend FhirMedicationStatement;
    friend FhirValue;
    friend FhirCompositionSection;
    friend FhirAttester;
    friend FhirComposition;
    friend FhirBasic;
    friend FhirPractitionerRole;
    friend FhirAllergyIntolerance;
    friend FhirPartOfChain;
    friend FhirMedicationDispense;
private:
    FhirIdentifier identifier;
    std::string reference;
    std::string type;
    std::string display;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirReference() : identifier(), reference(), type(), display() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirReference(const FhirIdentifier &identifier, const std::string &reference, const std::string &type, const std::string &display)
            : identifier(identifier), reference(reference), type(type), display(display) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirReference(FhirIdentifier &&identifier, std::string &&reference, std::string &&type, std::string &&display)
            : identifier(std::move(identifier)), reference(std::move(reference)), type(std::move(type)), display(std::move(display)) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirReference(const std::string &reference, const std::string &type, const std::string &display)
            : identifier(), reference(reference), type(type), display(display) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirReference(std::string &&reference, std::string &&type, std::string &&display)
            : identifier(), reference(std::move(reference)), type(std::move(type)), display(std::move(display)) {}

    [[nodiscard]] std::string GetReference() const {
        return reference;
    }
    [[nodiscard]] std::string GetType() const {
        return type;
    }
    [[nodiscard]] std::string GetDisplay() const {
        return display;
    }
    [[nodiscard]] bool IsSet() const {
        return identifier.IsSet() || !reference.empty() || !type.empty() || !display.empty();
    }

    static std::string PropertyName() {
        return "valueReference";
    }
    std::string GetPropertyName() const override;

protected:
    json ToJsonObj() const override;
    static FhirReference ParseObj(const json &obj);
public:
    static FhirReference ParseJson(const std::string &);
};

class FhirBundle;

class FhirLink : public FhirObject {
    friend FhirBundle;
private:
    std::string relation;
    std::string url;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirLink() : relation(), url() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirLink(const std::string& relation, const std::string& url) : relation(relation), url(url) {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirLink(std::string&& relation, std::string&& url) : relation(std::move(relation)), url(std::move(url)) {}
    [[nodiscard]] std::string GetRelation() const {
        return relation;
    }
    [[nodiscard]] std::string GetUrl() const {
        return url;
    }
    bool IsSet() const {
        return !relation.empty() || !url.empty();
    }
protected:
    json ToJsonObj() const;
    static FhirLink ParseObj(const json &obj);
public:
    static FhirLink ParseJson(const std::string &);
};

class FhirName : public FhirObject {
    friend FhirPerson;
private:
    std::string use{};
    std::string family{};
    std::string given{};
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirName() : use(), family(), given() {}

    LIBSFMBASISAPI_CONSTEXPR_STRING FhirName(const std::string &use, const std::string &family, const std::string &given)
    : use(use), family(family), given(given) {}

    LIBSFMBASISAPI_CONSTEXPR_STRING FhirName(std::string &&use, std::string &&family, std::string &&given)
    : use(std::move(use)), family(std::move(family)), given(std::move(given)) {}

    [[nodiscard]] std::string GetUse() const {
        return use;
    }
    [[nodiscard]] std::string GetFamily() const {
        return family;
    }
    [[nodiscard]] std::string GetGiven() const {
        return given;
    }
    bool IsSet() const {
        return !use.empty() || !family.empty() || !given.empty();
    }
protected:
    json ToJsonObj() const;
    static FhirName ParseObj(const json &obj);
public:
    static FhirName ParseJson(const std::string &);
    std::string GetDisplay() const;
};

class FhirAddress : public FhirObject {
    friend FhirPerson;
private:
    std::vector<std::string> lines{};
    std::string use{};
    std::string type{};
    std::string city{};
    std::string postalCode{};
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirAddress() = default;

    LIBSFMBASISAPI_CONSTEXPR_STRING FhirAddress(const std::vector<std::string> &lines, const std::string &use, const std::string &type, const std::string &city, const std::string &postalCode):
        lines(lines), use(use), type(type), city(city), postalCode(postalCode) {}

    LIBSFMBASISAPI_CONSTEXPR_STRING FhirAddress(std::vector<std::string> &&lines, std::string &&use, std::string &&type, std::string &&city, std::string &&postalCode):
        lines(std::move(lines)), use(std::move(use)), type(std::move(type)), city(std::move(city)), postalCode(std::move(postalCode)) {}

    [[nodiscard]] std::vector<std::string> GetLines() const {
        return lines;
    }
    [[nodiscard]] std::string GetUse() const {
        return use;
    }
    [[nodiscard]] std::string GetType() const {
        return type;
    }
    [[nodiscard]] std::string GetCity() const {
        return city;
    }
    [[nodiscard]] std::string GetPostalCode() const {
        return postalCode;
    }

protected:
    json ToJsonObj() const;
    static FhirAddress Parse(const json &obj);
};

class FhirDateTimeValue : public FhirValue {
    friend FhirValue;
private:
    std::string dateTime;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirDateTimeValue() : dateTime() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirDateTimeValue(const std::string &dateTime) : dateTime(dateTime) {}
    [[nodiscard]] std::string GetDateTime() const {
        return dateTime;
    }
    void SetDateTime(const std::string &dateTime) {
        this->dateTime = dateTime;
    }
    static std::string PropertyName();
    std::string GetPropertyName() const override;
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<FhirDateTimeValue> Parse(const json &obj);
};

class FhirBooleanValue : public FhirValue {
    friend FhirValue;
private:
    bool value;
public:
    constexpr FhirBooleanValue() : value(false) {}
    explicit constexpr FhirBooleanValue(bool value) : value(value) {}
    bool IsTrue() const {
        return value;
    }
    void SetValue(bool value) {
        this->value = value;
    }
    static std::string PropertyName();
    std::string GetPropertyName() const override;
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<FhirBooleanValue> Parse(const json &obj);
};

class FhirIntegerValue : public FhirValue {
    friend FhirValue;
private:
    long value;
public:
    constexpr FhirIntegerValue() : value(0) {}
    constexpr FhirIntegerValue(long value) : value(value) {}
    long GetValue() const {
        return value;
    }
    void SetValue(long value) {
        this->value = value;
    }
    static std::string PropertyName();
    std::string GetPropertyName() const override;
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<FhirIntegerValue> Parse(const json &obj);
};

class FhirDecimalValue : public FhirValue {
    friend FhirValue;
private:
    long long int value;
    int precision;
public:
    constexpr FhirDecimalValue() : value(0), precision(0) {}
    constexpr explicit FhirDecimalValue(long long int value) : value(value), precision(0) {}
    explicit FhirDecimalValue(double value);
    double GetValue() const;
    static std::string PropertyName();
    std::string GetPropertyName() const override;
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<FhirDecimalValue> Parse(const json &obj);
};

class FhirDateValue : public FhirValue {
    friend FhirValue;
private:
    std::string date;
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirDateValue() : date() {}
    LIBSFMBASISAPI_CONSTEXPR_STRING explicit FhirDateValue(const std::string &date) : date(date) {}
    static std::string PropertyName();
    std::string GetPropertyName() const override;
    std::string GetRawValue() const;
    void SetValue(const std::string &value);
protected:
    json ToJsonObj() const override;
    static std::shared_ptr<FhirDateValue> Parse(const json &obj);
};


#endif //SFMBASISFAKER_VALUE_H
