#include "pch.h"
#include "Marriage.h"

void FMarriage::InitPerson(const std::string& string)
{
    std::shared_ptr<FPerson> Person = std::make_shared<FPerson>(); 
    Person->SetName(string);
    Persons.emplace_back(Person); 
}

void FMarriage::AskToMarry(const std::string& AskedPerson, const std::string& ProposePerson)
{
    for (auto Person : Persons)
    {
        if (Person->GetName() == ProposePerson)
        {
            if (ProposePerson != "Daniel")
            {
                Person->SetMarried(false); 
                return; 
            }
            
            if (ProposePerson == "Daniel")
            {
                for (auto MarriedPerson : Persons)
                {
                    if (MarriedPerson->GetName() == AskedPerson)
                    {
                        MarriedPerson->SetMarried(true);
                        return; 
                    }
                }
            }
        }
    }
}

std::shared_ptr<FPerson> FMarriage::GetPerson(const std::string& InName)
{
    for (auto Person : Persons)
    {
        if (Person->GetName() == InName)
        {
            return Person; 
        }
    }
    
    return nullptr;  
}
