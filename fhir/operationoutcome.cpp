//
// Created by sigsegv on 4/15/24.
//

#include <fhir/operationoutcome.h>

web::json::value FhirOperationOutcome::ToJson() const {
    auto obj = Fhir::ToJson();
    Fhir::ToJsonInline(obj);
    if (!issue.empty()) {
        auto issueArray = web::json::value::array(issue.size());
        for (auto i = 0; i < issue.size(); i++) {
            auto issueObj = web::json::value::object();
            auto &item = issue[i];
            {
                auto code = item.GetCode();
                if (!code.empty()) {
                    issueObj["code"] = web::json::value::string(code);
                }
            }
            {
                auto details = item.GetDetails();
                if (details.IsSet()) {
                    issueObj["details"] = details.ToJson();
                }
            }
            {
                auto diagnostics = item.GetDiagnostics();
                if (!diagnostics.empty()) {
                    issueObj["diagnostics"] = web::json::value::string(diagnostics);
                }
            }
            {
                auto expression = item.GetExpression();
                if (!expression.empty()) {
                    auto expressionArray = web::json::value::array(expression.size());
                    for (typeof(expression.size()) i = 0; i < expression.size(); i++) {
                        expressionArray[i] = web::json::value::string(expression[i]);
                    }
                    issueObj["expression"] = expressionArray;
                }
            }
            {
                auto location = item.GetLocation();
                if (!location.empty()) {
                    auto locationArray = web::json::value::array(location.size());
                    for (typeof(location.size()) i = 0; i < location.size(); i++) {
                        locationArray[i] = web::json::value::string(location[i]);
                    }
                    issueObj["location"] = locationArray;
                }
            }
            {
                auto severity = item.GetSeverity();
                if (!severity.empty()) {
                    issueObj["severity"] = web::json::value::string(severity);
                }
            }
            issueArray[i] = issueObj;
        }
        obj["issue"] = issueArray;
    }
    obj["resourceType"] = web::json::value::string("OperationOutcome");
    return obj;
}

FhirOperationOutcome FhirOperationOutcome::Parse(const web::json::value &obj) {
    FhirOperationOutcome operationOutcome{};
    operationOutcome.ParseInline(obj);
    if (obj.has_array_field("issue")) {
        auto issueArray = obj.at("issue").as_array();
        for (const auto &item : issueArray) {
            if (!item.is_object()) {
                continue;
            }
            auto &issue = operationOutcome.issue.emplace_back();
            if (item.has_string_field("code")) {
                issue.SetCode(item.at("code").as_string());
            }
            if (item.has_object_field("details")) {
                auto details = FhirCodeableConcept::Parse(item.at("details"));
                issue.SetDetails(details);
            }
            if (item.has_string_field("diagnostics")) {
                issue.SetDiagnostics(item.at("diagnostics").as_string());
            }
            if (item.has_array_field("expression")) {
                auto expressionArray = item.at("expression").as_array();
                std::vector<std::string> expressions{};
                expressions.reserve(expressionArray.size());
                for (const auto &exp : expressionArray) {
                    if (exp.is_string()) {
                        expressions.emplace_back(exp.as_string());
                    }
                }
                issue.SetExpression(expressions);
            }
            if (item.has_array_field("location")) {
                auto locationArray = item.at("location").as_array();
                std::vector<std::string> locations{};
                locations.reserve(locationArray.size());
                for (const auto &exp : locationArray) {
                    if (exp.is_string()) {
                        locations.emplace_back(exp.as_string());
                    }
                }
                issue.SetLocation(locations);
            }
            if (item.has_string_field("severity")) {
                issue.SetSeverity(item.at("severity").as_string());
            }
        }
    }
    return operationOutcome;
}
