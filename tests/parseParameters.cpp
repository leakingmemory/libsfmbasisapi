//
// Created by jeo on 08.12.2023.
//
#include <fstream>
#include <sstream>
#include "assert.h"
#include <fhir/person.h>
#include <fhir/parameters.h>

int main(int argc, char **argv) {
    AreEqual(3, argc);
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
    std::string assertions = argv[2];
    auto getmed = FhirParameters::Parse(FhirParameters::Parse(web::json::value::parse(json)).ToJson());
    if (assertions == "request") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(1, getmed.GetParameters().size());
        auto param = getmed.GetParameters().at(0);
        AreEqual("patient", param.GetName());
        auto resource = param.GetResource();
        AreEqual(true, resource.operator bool());
        auto patient = std::dynamic_pointer_cast<FhirPerson>(resource);
        AreEqual(true, patient.operator bool());
        AreEqual(1, patient->GetIdentifiers().size());
        AreEqual("06120182763", patient->GetIdentifiers().at(0).GetValue());
        AreEqual(1, patient->GetAddress().size());
        auto address = patient->GetAddress().at(0);
        AreEqual("home", address.GetUse());
        AreEqual("physical", address.GetType());
        AreEqual(1, address.GetLines().size());
        auto line = address.GetLines().at(0);
        AreEqual("Testveien 1", line);
        AreEqual("Oslo", address.GetCity());
        AreEqual("1234", address.GetPostalCode());
    } else if (assertions == "response") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(9, getmed.GetParameters().size());
    } else if (assertions == "sendmedrequest") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(1, getmed.GetParameters().size());
        auto param = getmed.GetParameters().at(0);
        AreEqual("medication", param.GetName());
    } else if (assertions == "sendmedresponse") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(2, getmed.GetParameters().size());
        std::unordered_map<std::string,FhirParameter> parameters{};
        for (auto &parameter : getmed.GetParameters()) {
            parameters.insert_or_assign(parameter.GetName(), parameter);
        }
        auto recallCountFind = parameters.find("recallCount");
        auto prescriptionCountFind = parameters.find("prescriptionCount");
        AreEqual(false, recallCountFind == parameters.end());
        AreEqual(false, prescriptionCountFind == parameters.end());
        auto recallCount = std::dynamic_pointer_cast<FhirIntegerValue>(recallCountFind->second.GetFhirValue());
        auto prescriptionCount = std::dynamic_pointer_cast<FhirIntegerValue>(prescriptionCountFind->second.GetFhirValue());
        AreEqual(true, recallCount.operator bool());
        AreEqual(true, prescriptionCount.operator bool());
        AreEqual(0, recallCount->GetValue());
        AreEqual(0, prescriptionCount->GetValue());
    } else {
        throw std::exception();
    }
}