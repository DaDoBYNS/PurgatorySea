#include "pch.h"
#include "Person.h"

FPerson::FPerson()
    : bIsMarried(false)
    , Name("Empty")
{}

bool FPerson::GetMarried() const
{
    return bIsMarried; 
}

void FPerson::SetName(std::string InName)
{
    Name = InName;    
}

std::string FPerson::GetName()
{
    return Name; 
}

void FPerson::SetMarried(bool bInIsMarried)
{
    bIsMarried = bInIsMarried;
}
