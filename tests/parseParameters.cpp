//
// Created by jeo on 08.12.2023.
//
#include <fstream>
#include <sstream>
#include "assert.h"
#include <fhir/person.h>
#include <fhir/parameters.h>
#include <map>

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
    auto getmed = FhirParameters::ParseJson(FhirParameters::ParseJson(json).ToJson());
    if (assertions == "request") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(1, getmed.GetParameters().size());
        auto param = getmed.GetParameters().at(0);
        AreEqual("patient", param.GetName());
    } else if (assertions == "request2") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(3, getmed.GetParameters().size());
        auto param = getmed.GetParameters().at(0);
        AreEqual("patient", param.GetName());
        auto resource = param.GetResource();
        AreEqual(true, resource.operator bool());
        auto patient = std::dynamic_pointer_cast<FhirPerson>(resource);
        AreEqual(true, patient.operator bool());
        AreEqual(1, patient->GetIdentifiers().size());
        AreEqual("22056322705", patient->GetIdentifiers().at(0).GetValue());
        AreEqual(1, patient->GetAddress().size());
        auto address = patient->GetAddress().at(0);
        AreEqual("home", address.GetUse());
        AreEqual("physical", address.GetType());
        AreEqual(0, address.GetLines().size());
        AreEqual("Fauske", address.GetCity());
        AreEqual("8200", address.GetPostalCode());
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
    } else if (assertions == "sendmedresponse2") {
        AreEqual("Parameters", getmed.GetResourceType());
        AreEqual(3, getmed.GetParameters().size());
        std::unordered_map<std::string,FhirParameter> parameters{};
        for (auto &parameter : getmed.GetParameters()) {
            parameters.insert_or_assign(parameter.GetName(), parameter);
        }
        auto recallCountFind = parameters.find("recallCount");
        auto prescriptionCountFind = parameters.find("prescriptionCount");
        auto prescriptionOperationResultFind = parameters.find("prescriptionOperationResult");
        AreEqual(false, recallCountFind == parameters.end());
        AreEqual(false, prescriptionCountFind == parameters.end());
        AreEqual(false, prescriptionOperationResultFind == parameters.end());
        auto recallCount = std::dynamic_pointer_cast<FhirIntegerValue>(recallCountFind->second.GetFhirValue());
        auto prescriptionCount = std::dynamic_pointer_cast<FhirIntegerValue>(prescriptionCountFind->second.GetFhirValue());
        auto prescriptionOperationResultVector = prescriptionOperationResultFind->second.GetPart();
        AreEqual(true, recallCount.operator bool());
        AreEqual(true, prescriptionCount.operator bool());
        AreEqual(false, prescriptionOperationResultVector.empty());
        AreEqual(0, recallCount->GetValue());
        AreEqual(1, prescriptionCount->GetValue());
        std::map<std::string,std::shared_ptr<FhirValue>> prescriptionOperationResult{};
        for (const auto &part : prescriptionOperationResultVector) {
            auto value = part->GetFhirValue();
            if (value) {
                prescriptionOperationResult.insert_or_assign(part->GetName(), value);
            }
        }
        auto reseptIdFind = prescriptionOperationResult.find("reseptID");
        auto resultCodeFind = prescriptionOperationResult.find("resultCode");
        AreEqual(false, reseptIdFind == prescriptionOperationResult.end());
        AreEqual(false, resultCodeFind == prescriptionOperationResult.end());
        auto reseptId = std::dynamic_pointer_cast<FhirString>(reseptIdFind->second);
        auto resultCode = std::dynamic_pointer_cast<FhirCodingValue>(resultCodeFind->second);
        AreEqual(true, reseptId.operator bool());
        AreEqual(true, resultCode.operator bool());
        AreEqual("b733fb1b-d3f4-4802-8c2d-2981bf2fac2d", reseptId->GetValue());
        AreEqual("0", resultCode->GetCode());
    } else {
        throw std::exception();
    }
}