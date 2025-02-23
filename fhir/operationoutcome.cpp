//
// Created by sigsegv on 4/15/24.
//

#include <fhir/operationoutcome.h>
#include "json.h"

json FhirOperationOutcome::ToJsonObj() const {
    auto obj = Fhir::ToJsonObj();
    Fhir::ToJsonInline(obj);
    if (!issue.empty()) {
        auto issueArray = nlohmann::json::array();
        for (auto i = 0; i < issue.size(); i++) {
            nlohmann::json issueObj{};
            auto &item = issue[i];
            {
                auto code = item.GetCode();
                if (!code.empty()) {
                    issueObj["code"] = code;
                }
            }
            {
                auto details = item.GetDetails();
                if (details.IsSet()) {
                    auto det = details.ToJsonObj();
                    issueObj["details"] = static_cast<const nlohmann::json &>(det);
                }
            }
            {
                auto diagnostics = item.GetDiagnostics();
                if (!diagnostics.empty()) {
                    issueObj["diagnostics"] = diagnostics;
                }
            }
            {
                auto expression = item.GetExpression();
                if (!expression.empty()) {
                    auto expressionArray = nlohmann::json::array();
                    for (decltype(expression.size()) i = 0; i < expression.size(); i++) {
                        expressionArray.push_back(expression[i]);
                    }
                    issueObj["expression"] = expressionArray;
                }
            }
            {
                auto location = item.GetLocation();
                if (!location.empty()) {
                    auto locationArray = nlohmann::json::array();
                    for (decltype(location.size()) i = 0; i < location.size(); i++) {
                        locationArray.push_back(location[i]);
                    }
                    issueObj["location"] = locationArray;
                }
            }
            {
                auto severity = item.GetSeverity();
                if (!severity.empty()) {
                    issueObj["severity"] = severity;
                }
            }
            issueArray.push_back(issueObj);
        }
        obj["issue"] = issueArray;
    }
    obj["resourceType"] = "OperationOutcome";
    return obj;
}

FhirOperationOutcome FhirOperationOutcome::ParseObj(const json &obj) {
    FhirOperationOutcome operationOutcome{};
    operationOutcome.ParseInline(obj);
    if (obj.contains("issue")) {
        auto issueArray = obj["issue"];
        if (issueArray.is_array()) {
            for (const auto &item: issueArray) {
                if (!item.is_object()) {
                    continue;
                }
                auto &issue = operationOutcome.issue.emplace_back();
                if (item.contains("code")) {
                    issue.SetCode(item["code"]);
                }
                if (item.contains("details")) {
                    auto details = FhirCodeableConcept::Parse(item["details"]);
                    issue.SetDetails(details);
                }
                if (item.contains("diagnostics")) {
                    issue.SetDiagnostics(item["diagnostics"]);
                }
                if (item.contains("expression")) {
                    auto expressionArray = item["expression"];
                    if (expressionArray.is_array()) {
                        std::vector<std::string> expressions{};
                        expressions.reserve(expressionArray.size());
                        for (const auto &exp: expressionArray) {
                            if (exp.is_string()) {
                                expressions.emplace_back(exp);
                            }
                        }
                        issue.SetExpression(expressions);
                    }
                }
                if (item.contains("location")) {
                    auto locationArray = item["location"];
                    if (locationArray.is_array()) {
                        std::vector<std::string> locations{};
                        locations.reserve(locationArray.size());
                        for (const auto &exp: locationArray) {
                            if (exp.is_string()) {
                                locations.emplace_back(exp);
                            }
                        }
                        issue.SetLocation(locations);
                    }
                }
                if (item.contains("severity")) {
                    issue.SetSeverity(item["severity"]);
                }
            }
        }
    }
    return operationOutcome;
}

FhirOperationOutcome FhirOperationOutcome::ParseJson(const std::string &str) {
    return ParseObj(nlohmann::json::parse(str));
}
