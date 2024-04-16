//
// Created by sigsegv on 4/15/24.
//

#include <fhir/operationoutcome.h>
#include <fhir/fhir.h>
#include <fstream>
#include <sstream>
#include "assert.h"

int main(int argc, char **argv) {
    AreEqual(2, argc);
    std::string json{};
    {
        std::string filename = argv[1];
        std::ifstream input{filename};
        if (!input.is_open()) {
            throw std::exception();
        }
        std::stringstream sstr{};
        sstr << input.rdbuf();
        json = sstr.str();
        input.close();
    }
    auto operationOutcome = FhirOperationOutcome::Parse(Fhir::Parse(web::json::value::parse(json))->ToJson());
    AreEqual("OperationOutcome", operationOutcome.GetResourceType());
    AreEqual("3af258ec-235e-43d0-be4d-08ac01bad64c", operationOutcome.GetId());
    auto issues = operationOutcome.GetIssue();
    AreEqual(3, issues.size());
    auto first = issues[0];
    auto second = issues[1];
    auto third = issues[2];
    AreEqual("processing", first.GetCode());
    AreEqual("Please use the id '3af258ec-235e-43d0-be4d-08ac01bad64c' and contact our support team if the problem persists.", first.GetDiagnostics());
    AreEqual("error", first.GetSeverity());
    AreEqual("invalid", second.GetCode());
    AreEqual("Medication.extension:medicationdetails.extension:name missing or invalid", second.GetDiagnostics());
    AreEqual(1, second.GetExpression().size());
    AreEqual(1, second.GetLocation().size());
    AreEqual("error", second.GetSeverity());
    AreEqual("informational", third.GetCode());
    AreEqual("TraceId: 555003cfdfa14bb25c417c672d28fb31 (Also include this value in support requests)", third.GetDetails().GetText());
    AreEqual("information", third.GetSeverity());
}
