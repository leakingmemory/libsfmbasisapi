//
// Created by sigsegv on 4/15/24.
//

#include <fhir/operationoutcome.h>

#include "../win32/w32strings.h"

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
                    issueObj[as_wstring_on_win32("code")] = web::json::value::string(as_wstring_on_win32(code));
                }
            }
            {
                auto details = item.GetDetails();
                if (details.IsSet()) {
                    issueObj[as_wstring_on_win32("details")] = details.ToJson();
                }
            }
            {
                auto diagnostics = item.GetDiagnostics();
                if (!diagnostics.empty()) {
                    issueObj[as_wstring_on_win32("diagnostics")] = web::json::value::string(as_wstring_on_win32(diagnostics));
                }
            }
            {
                auto expression = item.GetExpression();
                if (!expression.empty()) {
                    auto expressionArray = web::json::value::array(expression.size());
#ifdef WIN32
                    for (decltype(expression.size()) i = 0; i < expression.size(); i++) {
#else
                    for (typeof(expression.size()) i = 0; i < expression.size(); i++) {
#endif
                        expressionArray[i] = web::json::value::string(as_wstring_on_win32(expression[i]));
                    }
                    issueObj[as_wstring_on_win32("expression")] = expressionArray;
                }
            }
            {
                auto location = item.GetLocation();
                if (!location.empty()) {
                    auto locationArray = web::json::value::array(location.size());
#ifdef WIN32
                    for (decltype(location.size()) i = 0; i < location.size(); i++) {
#else
                    for (typeof(location.size()) i = 0; i < location.size(); i++) {
#endif
                        locationArray[i] = web::json::value::string(as_wstring_on_win32(location[i]));
                    }
                    issueObj[as_wstring_on_win32("location")] = locationArray;
                }
            }
            {
                auto severity = item.GetSeverity();
                if (!severity.empty()) {
                    issueObj[as_wstring_on_win32("severity")] = web::json::value::string(as_wstring_on_win32(severity));
                }
            }
            issueArray[i] = issueObj;
        }
        obj[as_wstring_on_win32("issue")] = issueArray;
    }
    obj[as_wstring_on_win32("resourceType")] = web::json::value::string(as_wstring_on_win32("OperationOutcome"));
    return obj;
}

FhirOperationOutcome FhirOperationOutcome::Parse(const web::json::value &obj) {
    FhirOperationOutcome operationOutcome{};
    operationOutcome.ParseInline(obj);
    if (obj.has_array_field(as_wstring_on_win32("issue"))) {
        auto issueArray = obj.at(as_wstring_on_win32("issue")).as_array();
        for (const auto &item : issueArray) {
            if (!item.is_object()) {
                continue;
            }
            auto &issue = operationOutcome.issue.emplace_back();
            if (item.has_string_field(as_wstring_on_win32("code"))) {
                issue.SetCode(from_wstring_on_win32(item.at(as_wstring_on_win32("code")).as_string()));
            }
            if (item.has_object_field(as_wstring_on_win32("details"))) {
                auto details = FhirCodeableConcept::Parse(item.at(as_wstring_on_win32("details")));
                issue.SetDetails(details);
            }
            if (item.has_string_field(as_wstring_on_win32("diagnostics"))) {
                issue.SetDiagnostics(from_wstring_on_win32(item.at(as_wstring_on_win32("diagnostics")).as_string()));
            }
            if (item.has_array_field(as_wstring_on_win32("expression"))) {
                auto expressionArray = item.at(as_wstring_on_win32("expression")).as_array();
                std::vector<std::string> expressions{};
                expressions.reserve(expressionArray.size());
                for (const auto &exp : expressionArray) {
                    if (exp.is_string()) {
                        expressions.emplace_back(from_wstring_on_win32(exp.as_string()));
                    }
                }
                issue.SetExpression(expressions);
            }
            if (item.has_array_field(as_wstring_on_win32("location"))) {
                auto locationArray = item.at(as_wstring_on_win32("location")).as_array();
                std::vector<std::string> locations{};
                locations.reserve(locationArray.size());
                for (const auto &exp : locationArray) {
                    if (exp.is_string()) {
                        locations.emplace_back(from_wstring_on_win32(exp.as_string()));
                    }
                }
                issue.SetLocation(locations);
            }
            if (item.has_string_field(as_wstring_on_win32("severity"))) {
                issue.SetSeverity(from_wstring_on_win32(item.at(as_wstring_on_win32("severity")).as_string()));
            }
        }
    }
    return operationOutcome;
}
