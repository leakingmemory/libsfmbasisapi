//
// Created by jeo on 12/7/23.
//

#include <fhir/value.h>

#include "../win32/w32strings.h"

std::string FhirString::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirString::ToJson() const {
    return web::json::value::string(as_wstring_on_win32(value));
}

std::shared_ptr<FhirString> FhirString::Parse(const web::json::value &value) {
    return std::make_shared<FhirString>(from_wstring_on_win32(value.as_string()));
}

std::shared_ptr<FhirValue> FhirValue::Parse(const std::string &propertyName, const web::json::value &property) {
    if (propertyName == FhirString::PropertyName()) {
        return FhirString::Parse(property);
    }
    if (propertyName == FhirCodeableConceptValue::PropertyName()) {
        return FhirCodeableConceptValue::Parse(property);
    }
    if (propertyName == FhirDateTimeValue::PropertyName()) {
        return FhirDateTimeValue::Parse(property);
    }
    if (propertyName == FhirBooleanValue::PropertyName()) {
        return FhirBooleanValue::Parse(property);
    }
    if (propertyName == FhirIntegerValue::PropertyName()) {
        return FhirIntegerValue::Parse(property);
    }
    if (propertyName == FhirDecimalValue::PropertyName()) {
        return FhirDecimalValue::Parse(property);
    }
    if (propertyName == FhirCodingValue::PropertyName()) {
        return FhirCodingValue::Parse(property);
    }
    if (propertyName == FhirReference::PropertyName()) {
        return std::make_shared<FhirReference>(FhirReference::Parse(property));
    }
    if (propertyName == FhirDateValue::PropertyName()) {
        return FhirDateValue::Parse(property);
    }
    if (propertyName == FhirQuantityValue::PropertyName()) {
        return FhirQuantityValue::Parse(property);
    }
    throw FhirValueException(propertyName, "Value property not known");
}

web::json::value FhirCoding::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (!system.empty())
        obj[as_wstring_on_win32("system")] = web::json::value::string(as_wstring_on_win32(system));
    if (!code.empty())
        obj[as_wstring_on_win32("code")] = web::json::value::string(as_wstring_on_win32(code));
    if (!display.empty())
        obj[as_wstring_on_win32("display")] = web::json::value::string(as_wstring_on_win32(display));
    return obj;
}

FhirCoding FhirCoding::Parse(const web::json::value &obj) {
    std::string system{};
    if (obj.has_string_field(as_wstring_on_win32("system"))) {
        system = from_wstring_on_win32(obj.at(as_wstring_on_win32("system")).as_string());
    }
    std::string code{};
    if (obj.has_string_field(as_wstring_on_win32("code"))) {
        code = from_wstring_on_win32(obj.at(as_wstring_on_win32("code")).as_string());
    }
    std::string display{};
    if (obj.has_string_field(as_wstring_on_win32("display"))) {
        display = from_wstring_on_win32(obj.at(as_wstring_on_win32("display")).as_string());
    }
    return {std::move(system), std::move(code), std::move(display)};
}

web::json::value FhirCodeableConcept::ToJson() const {
    auto obj = FhirExtendable::ToJson();
    FhirExtendable::ToJsonInline(obj);
    auto jsonCoding = web::json::value::array();
#ifdef WIN32
    decltype(coding.size()) i = 0;
#else
    typeof(coding.size()) i = 0;
#endif
    for (const auto &c : coding) {
        jsonCoding[i++] = c.ToJson();
    }
    if (i > 0 || text.empty()) {
        obj[as_wstring_on_win32("coding")] = jsonCoding;
    }
    if (!text.empty()) {
        obj[as_wstring_on_win32("text")] = web::json::value::string(as_wstring_on_win32(text));
    }
    return obj;
}

FhirCodeableConcept FhirCodeableConcept::Parse(const web::json::value &obj) {
    std::vector<FhirCoding> coding{};
    std::string text{};
    if (obj.is_object()) {
        if (obj.has_array_field(as_wstring_on_win32("coding"))) {
            for (const auto &c: obj.at(as_wstring_on_win32("coding")).as_array()) {
                coding.emplace_back(FhirCoding::Parse(c));
            }
        }
        if (obj.has_string_field(as_wstring_on_win32("text"))) {
            text = from_wstring_on_win32(obj.at(as_wstring_on_win32("text")).as_string());
        }
    }
    FhirCodeableConcept codeableConcept{std::move(coding), std::move(text)};
    codeableConcept.ParseInline(obj);
    return codeableConcept;
}

std::string FhirCodingValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirCodingValue::ToJson() const {
    return FhirCoding::ToJson();
}

std::shared_ptr<FhirCodingValue> FhirCodingValue::Parse(const web::json::value &obj) {
    return std::make_shared<FhirCodingValue>(FhirCoding::Parse(obj));
}

std::string FhirCodeableConceptValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirCodeableConceptValue::ToJson() const {
    return FhirCodeableConcept::ToJson();
}

std::shared_ptr<FhirCodeableConceptValue> FhirCodeableConceptValue::Parse(const web::json::value &obj) {
    return std::make_shared<FhirCodeableConceptValue>(FhirCodeableConcept::Parse(obj));
}

web::json::value FhirQuantity::ToJson() const {
    auto obj = FhirObject::ToJson();
    obj[as_wstring_on_win32("value")] = web::json::value::number(GetValue());
    obj[as_wstring_on_win32("unit")] = web::json::value::string(as_wstring_on_win32(unit));
    return obj;
}

FhirQuantity FhirQuantity::Parse(const web::json::value &obj) {
    std::string unit{};
    if (obj.has_string_field(as_wstring_on_win32("unit"))) {
        unit = from_wstring_on_win32(obj.at(as_wstring_on_win32("unit")).as_string());
    }
    if (obj.has_number_field(as_wstring_on_win32("value"))) {
        return FhirQuantity(obj.at(as_wstring_on_win32("value")).as_double(), unit);
    } else if (!unit.empty()) {
        return FhirQuantity(0.0, unit);
    } else {
        return {};
    }
}

std::string FhirQuantityValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirQuantityValue::ToJson() const {
    return FhirQuantity::ToJson();
}

std::shared_ptr<FhirQuantityValue> FhirQuantityValue::Parse(const web::json::value &obj) {
    return std::make_shared<FhirQuantityValue>(FhirQuantity::Parse(obj));
}

web::json::value FhirRatio::ToJson() const {
    auto obj = FhirExtendable::ToJson();
    if (numerator.IsSet()) {
        obj[as_wstring_on_win32("numerator")] = numerator.ToJson();
    }
    if (denominator.IsSet()) {
        obj[as_wstring_on_win32("denominator")] = denominator.ToJson();
    }
    FhirExtendable::ToJsonInline(obj);
    return obj;
}

FhirRatio FhirRatio::Parse(const web::json::value &obj) {
    FhirQuantity numerator{};
    if (obj.has_object_field(as_wstring_on_win32("numerator"))) {
        numerator = FhirQuantity::Parse(obj.at(as_wstring_on_win32("numerator")));
    }
    FhirQuantity denominator{};
    if (obj.has_object_field(as_wstring_on_win32("denominator"))) {
        denominator = FhirQuantity::Parse(obj.at(as_wstring_on_win32("denominator")));
    }
    FhirRatio ratio{std::move(numerator), std::move(denominator)};
    ratio.ParseInline(obj);
    return ratio;
}

std::string FhirReference::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirReference::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (identifier.IsSet()) {
        obj[as_wstring_on_win32("identifier")] = identifier.ToJson();
    }
    if (!reference.empty()) {
        obj[as_wstring_on_win32("reference")] = web::json::value::string(as_wstring_on_win32(reference));
    }
    if (!type.empty()) {
        obj[as_wstring_on_win32("type")] = web::json::value::string(as_wstring_on_win32(type));
    }
    if (!display.empty()) {
        obj[as_wstring_on_win32("display")] = web::json::value::string(as_wstring_on_win32(display));
    }
    return obj;
}

FhirReference FhirReference::Parse(const web::json::value &obj) {
    FhirIdentifier identifier{};
    if (obj.has_object_field(as_wstring_on_win32("identifier"))) {
        identifier = FhirIdentifier::Parse(obj.at(as_wstring_on_win32("identifier")));
    }

    std::string reference{};
    if (obj.has_string_field(as_wstring_on_win32("reference"))) {
        reference = from_wstring_on_win32(obj.at(as_wstring_on_win32("reference")).as_string());
    }

    std::string type{};
    if (obj.has_string_field(as_wstring_on_win32("type"))) {
        type = from_wstring_on_win32(obj.at(as_wstring_on_win32("type")).as_string());
    }

    std::string display{};
    if (obj.has_string_field(as_wstring_on_win32("display"))) {
        display = from_wstring_on_win32(obj.at(as_wstring_on_win32("display")).as_string());
    }

    return {std::move(identifier), std::move(reference), std::move(type), std::move(display)};
}

web::json::value FhirIdentifier::ToJson() const {
    auto obj = FhirObject::ToJson();
    obj[as_wstring_on_win32("use")] = web::json::value::string(as_wstring_on_win32(use));
    if (type.IsSet()) {
        obj[as_wstring_on_win32("type")] = type.ToJson();
    }
    if (!system.empty()) {
        obj[as_wstring_on_win32("system")] = web::json::value::string(as_wstring_on_win32(system));
    }
    obj[as_wstring_on_win32("value")] = web::json::value::string(as_wstring_on_win32(value));
    return obj;
}

FhirIdentifier FhirIdentifier::Parse(const web::json::value &obj) {
    std::string use{};
    if (obj.has_string_field(as_wstring_on_win32("use"))) {
        use = from_wstring_on_win32(obj.at(as_wstring_on_win32("use")).as_string());
    }

    FhirCodeableConcept type{};
    if (obj.has_object_field(as_wstring_on_win32("type"))) {
        type = FhirCodeableConcept::Parse(obj.at(as_wstring_on_win32("type")));
    }

    std::string system{};
    if (obj.has_string_field(as_wstring_on_win32("system"))) {
        system = from_wstring_on_win32(obj.at(as_wstring_on_win32("system")).as_string());
    }

    std::string value{};
    if (obj.has_string_field(as_wstring_on_win32("value"))) {
        value = from_wstring_on_win32(obj.at(as_wstring_on_win32("value")).as_string());
    }

    return {std::move(type), std::move(use), std::move(system), std::move(value)};
}

web::json::value FhirLink::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (!relation.empty()) {
        obj[as_wstring_on_win32("relation")] = web::json::value::string(as_wstring_on_win32(relation));
    }
    if (!url.empty()) {
        obj[as_wstring_on_win32("url")] = web::json::value::string(as_wstring_on_win32(url));
    }
    return obj;
}

FhirLink FhirLink::Parse(const web::json::value &obj) {
    std::string relation{};
    if (obj.has_string_field(as_wstring_on_win32("relation"))) {
        relation = from_wstring_on_win32(obj.at(as_wstring_on_win32("relation")).as_string());
    }

    std::string url{};
    if (obj.has_string_field(as_wstring_on_win32("url"))) {
        url = from_wstring_on_win32(obj.at(as_wstring_on_win32("url")).as_string());
    }

    return {std::move(relation), std::move(url)};
}

web::json::value FhirName::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (!use.empty()) {
        obj[as_wstring_on_win32("use")] = web::json::value::string(as_wstring_on_win32(use));
    }
    if (!family.empty()) {
        obj[as_wstring_on_win32("family")] = web::json::value::string(as_wstring_on_win32(family));
    }
    if (!given.empty()) {
        auto arr = web::json::value::array(1);
        arr[0] = web::json::value::string(as_wstring_on_win32(given));
        obj[as_wstring_on_win32("given")] = arr;
    }
    return obj;
}

FhirName FhirName::Parse(const web::json::value &obj) {
    FhirName name{};

    if (obj.has_string_field(as_wstring_on_win32("use"))) {
        name.use = from_wstring_on_win32(obj.at(as_wstring_on_win32("use")).as_string());
    }
    if (obj.has_string_field(as_wstring_on_win32("family"))) {
        name.family = from_wstring_on_win32(obj.at(as_wstring_on_win32("family")).as_string());
    }
    if (obj.has_array_field(as_wstring_on_win32("given"))) {
        name.given = from_wstring_on_win32(obj.at(as_wstring_on_win32("given")).as_array().at(0).as_string());
    }

    return name;
}

std::string FhirName::GetDisplay() const {
    std::string display{given};
    if (!display.empty() && !family.empty()) {
        display.append(" ");
    }
    display.append(family);
    return display;
}

web::json::value FhirAddress::ToJson() const {
    auto obj = FhirObject::ToJson();
    if (!type.empty()) {
        obj[as_wstring_on_win32("type")] = web::json::value::string(as_wstring_on_win32(type));
    }
    if (!city.empty()) {
        obj[as_wstring_on_win32("city")] = web::json::value::string(as_wstring_on_win32(city));
    }
    if (!postalCode.empty()) {
        obj[as_wstring_on_win32("postalCode")] = web::json::value::string(as_wstring_on_win32(postalCode));
    }
    if (!lines.empty()) {
        auto arr = web::json::value::array(lines.size());
#if WIN32
        decltype(lines.size()) i = 0;
#else
        typeof(lines.size()) i = 0;
#endif
        for (const auto &line : lines) {
            arr[i++] = web::json::value::string(as_wstring_on_win32(line));
        }
        obj[as_wstring_on_win32("line")] = arr;
    }
    if (!use.empty()) {
        obj[as_wstring_on_win32("use")] = web::json::value::string(as_wstring_on_win32(use));
    }
    return obj;
}

FhirAddress FhirAddress::Parse(const web::json::value &obj) {
    std::string type{};
    if (obj.has_string_field(as_wstring_on_win32("type"))) {
        type = from_wstring_on_win32(obj.at(as_wstring_on_win32("type")).as_string());
    }

    std::string city{};
    if (obj.has_string_field(as_wstring_on_win32("city"))) {
        city = from_wstring_on_win32(obj.at(as_wstring_on_win32("city")).as_string());
    }

    std::string postalCode{};
    if (obj.has_string_field(as_wstring_on_win32("postalCode"))) {
        postalCode = from_wstring_on_win32(obj.at(as_wstring_on_win32("postalCode")).as_string());
    }

    std::vector<std::string> lines{};
    if (obj.has_array_field(as_wstring_on_win32("line"))) {
        for (const auto &line : obj.at(as_wstring_on_win32("line")).as_array()) {
            lines.emplace_back(from_wstring_on_win32(line.as_string()));
        }
    }

    std::string use{};
    if (obj.has_string_field(as_wstring_on_win32("use"))) {
        use = from_wstring_on_win32(obj.at(as_wstring_on_win32("use")).as_string());
    }

    return {std::move(lines), std::move(use), std::move(type), std::move(city), std::move(postalCode)};
}

std::string FhirDateTimeValue::PropertyName() {
    return "valueDateTime";
}

std::string FhirDateTimeValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirDateTimeValue::ToJson() const {
    return web::json::value::string(as_wstring_on_win32(dateTime));
}

std::shared_ptr<FhirDateTimeValue> FhirDateTimeValue::Parse(const web::json::value &obj) {
    auto dateTimeValue = std::make_shared<FhirDateTimeValue>();
    dateTimeValue->dateTime = from_wstring_on_win32(obj.as_string());
    return dateTimeValue;
}

std::string FhirBooleanValue::PropertyName() {
    return "valueBoolean";
}

std::string FhirBooleanValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirBooleanValue::ToJson() const {
    return web::json::value::boolean(value);
}

std::shared_ptr<FhirBooleanValue> FhirBooleanValue::Parse(const web::json::value &obj) {
    auto value = std::make_shared<FhirBooleanValue>();
    value->value = obj.as_bool();
    return value;
}

std::string FhirIntegerValue::PropertyName() {
    return "valueInteger";
}

std::string FhirIntegerValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirIntegerValue::ToJson() const {
    return web::json::value::number(value);
}

std::shared_ptr<FhirIntegerValue> FhirIntegerValue::Parse(const web::json::value &obj) {
    auto integerValue = std::make_shared<FhirIntegerValue>();
    if constexpr (sizeof(long) == 4) {
        integerValue->value = obj.as_number().to_int32();
    } else {
        integerValue->value = obj.as_number().to_int64();
    }
    return integerValue;
}

constexpr double ceround(double value) {
    long long int rawIntVal = (long long int) value;
    double compareVal = rawIntVal;
    auto diff = value - compareVal;
    if (diff < 0.5) {
        return compareVal;
    } else {
        return compareVal + 1.0;
    }
}

constexpr double ceabs(double value) {
    if (value < 0.0) {
        return -value;
    } else {
        return value;
    }
}

constexpr void DoubleToPrecisionLongLongInt(double value, long long int &output, int &precision) {
    int p = 0;
    while (p < 5) {
        auto rounded = ceround(value);
        auto loss = ceabs(rounded - value);
        if (loss < 0.01 || p == 5) {
            output = (long long int) rounded;
            precision = p;
            return;
        }
        value *= 10.0;
        ++p;
    }
}

constexpr bool CheckDPLLI(double value, long long int output, int precision) {
    long long int c_o;
    int c_p;
    DoubleToPrecisionLongLongInt(value, c_o, c_p);
    return (c_o == output && c_p == precision);
}

static_assert(CheckDPLLI(1.0, 1, 0));
static_assert(CheckDPLLI(1.1, 11, 1));
static_assert(CheckDPLLI(1.5, 15, 1));
static_assert(CheckDPLLI(1.11, 111, 2));
static_assert(CheckDPLLI(0.1, 1, 1));

constexpr double PrecisionLongLongIntToDouble(long long int value, int precision) {
    double dval = value;
    while (precision > 0) {
        dval /= 10.0;
        --precision;
    }
    return dval;
}

constexpr bool CheckDPLLI(long long int value, int precision) {
    double dval = PrecisionLongLongIntToDouble(value, precision);
    long long int c_o;
    int c_p;
    DoubleToPrecisionLongLongInt(dval, c_o, c_p);
    return (c_o == value && c_p == precision);
}

static_assert(CheckDPLLI(1, 0));
static_assert(CheckDPLLI(11, 1));
static_assert(CheckDPLLI(15, 1));
static_assert(CheckDPLLI(111, 2));
static_assert(CheckDPLLI(1, 1));

FhirDecimalValue::FhirDecimalValue(double value) {
    DoubleToPrecisionLongLongInt(value, this->value, precision);
}

double FhirDecimalValue::GetValue() const {
    return PrecisionLongLongIntToDouble(value, precision);
}

std::string FhirDecimalValue::PropertyName() {
    return "valueDecimal";
}

std::string FhirDecimalValue::GetPropertyName() const {
    return PropertyName();
}

web::json::value FhirDecimalValue::ToJson() const {
    return web::json::value::number(GetValue());
}

std::shared_ptr<FhirDecimalValue> FhirDecimalValue::Parse(const web::json::value &obj) {
    if (obj.is_number()) {
        return std::make_shared<FhirDecimalValue>(obj.as_number().to_double());
    } else {
        return {};
    }
}

std::string FhirDateValue::PropertyName() {
    return "valueDate";
}

std::string FhirDateValue::GetPropertyName() const {
    return PropertyName();
}

std::string FhirDateValue::GetRawValue() const {
    return date;
}

void FhirDateValue::SetValue(const std::string &value) {
    date = value;
}

web::json::value FhirDateValue::ToJson() const {
    return web::json::value::string(as_wstring_on_win32(date));
}

std::shared_ptr<FhirDateValue> FhirDateValue::Parse(const web::json::value &obj) {
    if (obj.is_string()) {
        return std::make_shared<FhirDateValue>(from_wstring_on_win32(obj.as_string()));
    } else {
        return {};
    }
}
