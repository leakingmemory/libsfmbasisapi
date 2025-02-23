//
// Created by sigsegv on 4/15/24.
//

#ifndef LIBSFMBASISAPI_OPERATIONOUTCOME_H
#define LIBSFMBASISAPI_OPERATIONOUTCOME_H

#include "fhirextendable.h"
#include "value.h"

class FhirIssue {
private:
    std::string code{};
    std::string diagnostics{};
    std::vector<std::string> expression{};
    std::vector<std::string> location{};
    std::string severity;
    FhirCodeableConcept details{};
public:

    [[nodiscard]] std::string GetCode() const {
        return code;
    }

    void SetCode(const std::string &code_) {
        code = code_;
    }

    [[nodiscard]] std::string GetDiagnostics() const {
        return diagnostics;
    }

    void SetDiagnostics(const std::string &diagnostics_) {
        diagnostics = diagnostics_;
    }

    [[nodiscard]] std::vector <std::string> GetExpression() const {
        return expression;
    }

    void SetExpression(const std::vector<std::string> &expression_) {
        expression = expression_;
    }

    [[nodiscard]] std::vector <std::string> GetLocation() const {
        return location;
    }

    void SetLocation(const std::vector<std::string> &location_) {
        location = location_;
    }

    [[nodiscard]] std::string GetSeverity() const {
        return severity;
    }

    void SetSeverity(const std::string &severity_) {
        severity = severity_;
    }

    [[nodiscard]] FhirCodeableConcept GetDetails() const {
        return details;
    }

    void SetDetails(const FhirCodeableConcept &details_) {
        details = details_;
    }
};

class FhirOperationOutcome : public Fhir {
    friend Fhir;
private:
    std::vector<FhirIssue> issue{};
public:
    LIBSFMBASISAPI_CONSTEXPR_STRING FhirOperationOutcome() = default;
protected:
    [[nodiscard]] json ToJsonObj() const override;
    static FhirOperationOutcome ParseObj(const json &obj);
public:
    static FhirOperationOutcome ParseJson(const std::string &);
    ~FhirOperationOutcome() override = default;
    [[nodiscard]] std::vector<FhirIssue> GetIssue() const {
        return issue;
    }
    void SetIssue(const std::vector<FhirIssue> &issue) {
        this->issue = issue;
    }
};

#endif //LIBSFMBASISAPI_OPERATIONOUTCOME_H
