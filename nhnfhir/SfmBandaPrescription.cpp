//
// Created by sigsegv on 2/7/25.
//

#include <nhnfhir/SfmBandaPrescription.h>

SfmBandaPrescription::SfmBandaPrescription() : FhirBasic() {
    {
        FhirCodeableConcept code{"urn:oid:2.16.578.1.12.4.1.1.7402", "A", "Annet"};
        SetCode(code);
    }
    SetProfile("http://ehelse.no/fhir/StructureDefinition/sfm-BandaPrescription");
}

SfmBandaPrescription::SfmBandaPrescription(const FhirBasic &basic) : FhirBasic(basic) {
}

SfmBandaPrescription::SfmBandaPrescription(FhirBasic &&basic) : FhirBasic(std::move(basic)) {
}

bool SfmBandaPrescription::CanHandle(const FhirBasic &basic) {
    auto codings = basic.GetCode().GetCoding();
    if (codings.empty() || codings[0].GetSystem() != "urn:oid:2.16.578.1.12.4.1.1.7402" || codings[0].GetCode() != "A") {
        return false;
    }
    auto profiles = basic.GetProfile();
    if (profiles.empty() || profiles[0] != "http://ehelse.no/fhir/StructureDefinition/sfm-BandaPrescription") {
        return false;
    }
    return true;
}

void SfmBandaPrescription::SetProductGroup(const FhirCodeableConcept &codeable) {
    auto value = std::make_shared<FhirCodeableConceptValue>(codeable);
    auto extensions = GetExtensions();
    std::shared_ptr<FhirExtension> extension{};
    {
        auto iterator = extensions.begin();
        while (iterator != extensions.end()) {
            auto url = (*iterator)->GetUrl();
            std::transform(url.cbegin(), url.cend(), url.begin(),
                           [](char ch) -> char { return static_cast<char>(std::tolower(ch)); });
            if (url == "http://ehelse.no/fhir/structuredefinition/sfm-reseptdocbanda") {
                extension = *iterator;
                break;
            }
            ++iterator;
        }
    }
    if (!extension) {
        extension = std::make_shared<FhirExtension>("http://ehelse.no/fhir/StructureDefinition/sfm-reseptdocbanda");
        AddExtension(extension);
    }
    extensions = extension->GetExtensions();
    bool removal{false};
    auto iterator = extensions.begin();
    while (iterator != extensions.end()) {
        auto url = (*iterator)->GetUrl();
        std::transform(url.cbegin(), url.cend(), url.begin(),
                       [](char ch) -> char { return static_cast<char>(std::tolower(ch)); });
        if (url == "productgroup") {
            auto valueExtension = std::dynamic_pointer_cast<FhirValueExtension>(*iterator);
            if (valueExtension) {
                valueExtension->SetValue(value);
                if (removal) {
                    extension->SetExtensions(extensions);
                }
                return;
            } else {
                removal = true;
                iterator = extensions.erase(iterator);
                continue;
            }
        }
        ++iterator;
    }
    if (removal) {
        extension->SetExtensions(extensions);
    }
    extension->AddExtension(std::make_shared<FhirValueExtension>("productgroup", value));
}

FhirCodeableConcept SfmBandaPrescription::GetProductGroup() const {
    auto extensions = GetExtensions();
    for (const auto &extension : extensions) {
        auto url = extension->GetUrl();
        std::transform(url.cbegin(), url.cend(), url.begin(),
                       [](char ch) -> char { return static_cast<char>(std::tolower(ch)); });
        if (url == "http://ehelse.no/fhir/structuredefinition/sfm-reseptdocbanda") {
            for (const auto &extension : extension->GetExtensions()) {
                auto url = extension->GetUrl();
                std::transform(url.cbegin(), url.cend(), url.begin(),
                               [](char ch) -> char { return static_cast<char>(std::tolower(ch)); });
                if (url == "productgroup") {
                    auto valueExtension = std::dynamic_pointer_cast<FhirValueExtension>(extension);
                    if (valueExtension) {
                        auto value = std::dynamic_pointer_cast<FhirCodeableConceptValue>(valueExtension->GetValue());
                        if (value) {
                            return *value;
                        }
                    }
                }
            }
        }
    }
    return {};
}

std::string SfmBandaPrescription::GetDisplay() const {
    auto productGroupCodings = GetProductGroup().GetCoding();
    if (!productGroupCodings.empty()) {
        auto productGroup = productGroupCodings[0].GetDisplay();
        if (!productGroup.empty()) {
            return productGroup;
        }
    }
    return Fhir::GetDisplay();
}
