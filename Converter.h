#pragma once

#include <memory>
#include <string>

#include "CK2_ProvinceCollection.h"
#include "CK2_TitleCollection.h"

class Converter
{
  public:
    void ReadSave(const std::string& saveFileName);

    void CreateMod(const std::string& name, const std::string& modPath, const std::string& eu4Path);

  private:
    std::unique_ptr<CK2::ProvinceCollection> sourceProvinces;
    std::unique_ptr<CK2::TitleCollection> sourceTitles;
};