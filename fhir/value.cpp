//
// Created by jeo on 12/7/23.
//

#include <fhir/value.h>
#include "json.h"

std::string FhirString::GetPropertyName() const {
    return PropertyName();
}

json FhirString::ToJsonObj() const {
    json v{};
    v = value;
    return v;
}

std::shared_ptr<FhirString> FhirString::Parse(const json &value) {
    std::string str = value;
    return std::make_shared<FhirString>(str);
}

std::string FhirCode::GetPropertyName() const {
    return PropertyName();
}

std::shared_ptr<FhirCode> FhirCode::Parse(const json &value) {
    std::string str = value;
    return std::make_shared<FhirCode>(str);
}

std::shared_ptr<FhirValue> FhirValue::ParseObj(const std::string &propertyName, const json &property) {
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
        return std::make_shared<FhirReference>(FhirReference::ParseObj(property));
    }
    if (propertyName == FhirDateValue::PropertyName()) {
        return FhirDateValue::Parse(property);
    }
    if (propertyName == FhirQuantityValue::PropertyName()) {
        return FhirQuantityValue::Parse(property);
    }
    if (propertyName == FhirCode::PropertyName()) {
        return FhirCode::Parse(property);
    }
    throw FhirValueException(propertyName, "Value property not known");
}

std::shared_ptr<FhirValue> FhirValue::ParseJson(const std::string &propertyName, const std::string &property) {
    return ParseObj(propertyName, nlohmann::json::parse(property));
}

json FhirCoding::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (!system.empty())
        obj["system"] = system;
    if (!code.empty())
        obj["code"] = code;
    if (!display.empty())
        obj["display"] = display;
    return obj;
}

FhirCoding FhirCoding::ParseObj(const json &obj) {
    std::string system{};
    if (obj.contains("system")) {
        system = obj["system"];
    }
    std::string code{};
    if (obj.contains("code")) {
        code = obj["code"];
    }
    std::string display{};
    if (obj.contains("display")) {
        display = obj["display"];
    }
    return {std::move(system), std::move(code), std::move(display)};
}

FhirCoding FhirCoding::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

json FhirCodeableConcept::ToJsonObj() const {
    auto obj = FhirExtendable::ToJsonObj();
    FhirExtendable::ToJsonInline(obj);
    auto jsonCoding = nlohmann::json::array();
    bool hasCodings{false};
    for (const auto &c : coding) {
        jsonCoding.push_back(c.ToJsonObj());
        hasCodings = true;
    }
    if (hasCodings || text.empty()) {
        obj["coding"] = jsonCoding;
    }
    if (!text.empty()) {
        obj["text"] = text;
    }
    return obj;
}


FhirCodeableConcept FhirCodeableConcept::Parse(const json &obj) {
    std::vector<FhirCoding> coding{};
    std::string text{};
    if (obj.is_object()) {
        if (obj.contains("coding")) {
            auto codingIn = obj["coding"];
            if (codingIn.is_array()) {
                for (const auto &c: codingIn) {
                    coding.emplace_back(FhirCoding::ParseObj(c));
                }
            }
        }
        if (obj.contains("text") && obj["text"].is_string()) {
            text = obj["text"];
        }
    }
    FhirCodeableConcept codeableConcept{std::move(coding), std::move(text)};
    codeableConcept.ParseInline(obj);
    return codeableConcept;
}

std::string FhirCodingValue::GetPropertyName() const {
    return PropertyName();
}

json FhirCodingValue::ToJsonObj() const {
    return FhirCoding::ToJsonObj();
}

std::shared_ptr<FhirCodingValue> FhirCodingValue::Parse(const json &obj) {
    return std::make_shared<FhirCodingValue>(FhirCoding::ParseObj(obj));
}

std::string FhirCodeableConceptValue::GetPropertyName() const {
    return PropertyName();
}

json FhirCodeableConceptValue::ToJsonObj() const {
    return FhirCodeableConcept::ToJsonObj();
}

std::shared_ptr<FhirCodeableConceptValue> FhirCodeableConceptValue::Parse(const json &obj) {
    return std::make_shared<FhirCodeableConceptValue>(FhirCodeableConcept::Parse(obj));
}

std::string FhirCodeableConceptValue::ToJson() const {
    return ToJsonObj().dump();
}

json FhirQuantity::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    obj["value"] = GetValue();
    if (!unit.empty()) {
        obj["unit"] = unit;
    }
    return obj;
}

FhirQuantity FhirQuantity::ParseObj(const json &obj) {
    std::string unit{};
    if (obj.contains("unit")) {
        unit = obj["unit"];
    }
    if (obj.contains("value")) {
        return FhirQuantity(obj["value"], unit);
    } else if (!unit.empty()) {
        return FhirQuantity(0.0, unit);
    } else {
        return {};
    }
}

FhirQuantity FhirQuantity::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

std::string FhirQuantityValue::GetPropertyName() const {
    return PropertyName();
}

json FhirQuantityValue::ToJsonObj() const {
    return FhirQuantity::ToJsonObj();
}

std::shared_ptr<FhirQuantityValue> FhirQuantityValue::Parse(const json &obj) {
    return std::make_shared<FhirQuantityValue>(FhirQuantity::ParseObj(obj));
}

json FhirRatio::ToJsonObj() const {
    auto obj = FhirExtendable::ToJsonObj();
    if (numerator.IsSet()) {
        auto num = numerator.ToJsonObj();
        obj["numerator"] = static_cast<const nlohmann::json &>(num);
    }
    if (denominator.IsSet()) {
        auto den = denominator.ToJsonObj();
        obj["denominator"] = static_cast<const nlohmann::json &>(den);
    }
    FhirExtendable::ToJsonInline(obj);
    return obj;
}

FhirRatio FhirRatio::ParseObj(const json &obj) {
    FhirQuantity numerator{};
    if (obj.contains("numerator")) {
        numerator = FhirQuantity::ParseObj(obj["numerator"]);
    }
    FhirQuantity denominator{};
    if (obj.contains("denominator")) {
        denominator = FhirQuantity::ParseObj(obj["denominator"]);
    }
    FhirRatio ratio{std::move(numerator), std::move(denominator)};
    ratio.ParseInline(obj);
    return ratio;
}

FhirRatio FhirRatio::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

std::string FhirReference::GetPropertyName() const {
    return PropertyName();
}

json FhirReference::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (identifier.IsSet()) {
        obj["identifier"] = identifier.ToJsonObj();
    }
    if (!reference.empty()) {
        obj["reference"] = reference;
    }
    if (!type.empty()) {
        obj["type"] = type;
    }
    if (!display.empty()) {
        obj["display"] = display;
    }
    return obj;
}

FhirReference FhirReference::ParseObj(const json &obj) {
    FhirIdentifier identifier{};
    if (obj.contains("identifier")) {
        identifier = FhirIdentifier::ParseObj(obj["identifier"]);
    }

    std::string reference{};
    if (obj.contains("reference")) {
        reference = obj["reference"];
    }

    std::string type{};
    if (obj.contains("type")) {
        type = obj["type"];
    }

    std::string display{};
    if (obj.contains("display")) {
        display = obj["display"];
    }

    return {std::move(identifier), std::move(reference), std::move(type), std::move(display)};
}

FhirReference FhirReference::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

json FhirIdentifier::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    obj["use"] = use;
    if (type.IsSet()) {
        auto t = type.ToJsonObj();
        obj["type"] = static_cast<const nlohmann::json &>(t);
    }
    if (!system.empty()) {
        obj["system"] = system;
    }
    obj["value"] = value;
    return obj;
}

FhirIdentifier FhirIdentifier::ParseObj(const json &obj) {
    std::string use{};
    if (obj.contains("use")) {
        use = obj["use"];
    }

    FhirCodeableConcept type{};
    if (obj.contains("type")) {
        type = FhirCodeableConcept::Parse(obj["type"]);
    }

    std::string system{};
    if (obj.contains("system")) {
        system = obj["system"];
    }

    std::string value{};
    if (obj.contains("value")) {
        value = obj["value"];
    }

    return {std::move(type), std::move(use), std::move(system), std::move(value)};
}

FhirIdentifier FhirIdentifier::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

json FhirLink::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (!relation.empty()) {
        obj["relation"] = relation;
    }
    if (!url.empty()) {
        obj["url"] = url;
    }
    return obj;
}

FhirLink FhirLink::ParseObj(const json &obj) {
    std::string relation{};
    if (obj.contains("relation")) {
        relation = obj["relation"];
    }

    std::string url{};
    if (obj.contains("url")) {
        url = obj["url"];
    }

    return {std::move(relation), std::move(url)};
}

FhirLink FhirLink::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

json FhirName::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (!use.empty()) {
        obj["use"] = use;
    }
    if (!family.empty()) {
        obj["family"] = family;
    }
    if (!given.empty()) {
        auto arr = nlohmann::json::array();
        arr.push_back(given);
        obj["given"] = arr;
    }
    return obj;
}

FhirName FhirName::ParseObj(const json &obj) {
    FhirName name{};

    if (obj.contains("use")) {
        name.use = obj["use"];
    }
    if (obj.contains("family")) {
        name.family = obj["family"];
    }
    if (obj.contains("given")) {
        auto arr = obj["given"];
        name.given = arr.is_array() && arr.size() > 0 ? arr[0] : "";
    }

    return name;
}

FhirName FhirName::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}

std::string FhirName::GetDisplay() const {
    std::string display{given};
    if (!display.empty() && !family.empty()) {
        display.append(" ");
    }
    display.append(family);
    return display;
}

json FhirAddress::ToJsonObj() const {
    auto obj = FhirObject::ToJsonObj();
    if (!type.empty()) {
        obj["type"] = type;
    }
    if (!city.empty()) {
        obj["city"] = city;
    }
    if (!postalCode.empty()) {
        obj["postalCode"] = postalCode;
    }
    if (!lines.empty()) {
        auto arr = nlohmann::json::array();
        decltype(lines.size()) i = 0;
        for (const auto &line : lines) {
            arr.push_back(line);
        }
        obj["line"] = arr;
    }
    if (!use.empty()) {
        obj["use"] = use;
    }
    return obj;
}

FhirAddress FhirAddress::Parse(const json &obj) {
    std::string type{};
    if (obj.contains("type")) {
        type = obj["type"];
    }

    std::string city{};
    if (obj.contains("city")) {
        city = obj["city"];
    }

    std::string postalCode{};
    if (obj.contains("postalCode")) {
        postalCode = obj["postalCode"];
    }

    std::vector<std::string> lines{};
    if (obj.contains("line")) {
        auto lineArr = obj["line"];
        if (lineArr.is_array()) {
            for (const auto &line: lineArr) {
                lines.emplace_back(line);
            }
        }
    }

    std::string use{};
    if (obj.contains("use")) {
        use = obj["use"];
    }

    return {std::move(lines), std::move(use), std::move(type), std::move(city), std::move(postalCode)};
}

std::string FhirDateTimeValue::PropertyName() {
    return "valueDateTime";
}

std::string FhirDateTimeValue::GetPropertyName() const {
    return PropertyName();
}

json FhirDateTimeValue::ToJsonObj() const {
    json v{};
    v = dateTime;
    return v;
}

std::shared_ptr<FhirDateTimeValue> FhirDateTimeValue::Parse(const json &obj) {
    auto dateTimeValue = std::make_shared<FhirDateTimeValue>();
    dateTimeValue->dateTime = obj;
    return dateTimeValue;
}

std::string FhirBooleanValue::PropertyName() {
    return "valueBoolean";
}

std::string FhirBooleanValue::GetPropertyName() const {
    return PropertyName();
}

json FhirBooleanValue::ToJsonObj() const {
    json v{};
    v = value;
    return v;
}

std::shared_ptr<FhirBooleanValue> FhirBooleanValue::Parse(const json &obj) {
    auto value = std::make_shared<FhirBooleanValue>();
    value->value = obj;
    return value;
}

std::string FhirIntegerValue::PropertyName() {
    return "valueInteger";
}

std::string FhirIntegerValue::GetPropertyName() const {
    return PropertyName();
}

json FhirIntegerValue::ToJsonObj() const {
    json v{};
    v = value;
    return v;
}

std::shared_ptr<FhirIntegerValue> FhirIntegerValue::Parse(const json &obj) {
    auto integerValue = std::make_shared<FhirIntegerValue>();
    integerValue->value = obj;
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

json FhirDecimalValue::ToJsonObj() const {
    json v{};
    v = GetValue();
    return v;
}

std::shared_ptr<FhirDecimalValue> FhirDecimalValue::Parse(const json &obj) {
    if (obj.is_number()) {
        double num = obj;
        return std::make_shared<FhirDecimalValue>(num);
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

json FhirDateValue::ToJsonObj() const {
    json v{};
    v = date;
    return v;
}

std::shared_ptr<FhirDateValue> FhirDateValue::Parse(const json &obj) {
    if (obj.is_string()) {
        std::string str = obj;
        return std::make_shared<FhirDateValue>(str);
    } else {
        return {};
    }
}
