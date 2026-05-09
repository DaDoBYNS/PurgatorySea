#pragma once
#include "Person.h"

class FMarriage
{
    std::vector<std::shared_ptr<FPerson>> Persons; 
    
public:
    void InitPerson(const std::string& string);
    void AskToMarry(const std::string& string, const std::string& jake);
    std::shared_ptr<FPerson> GetPerson(const std::string& string);
};
