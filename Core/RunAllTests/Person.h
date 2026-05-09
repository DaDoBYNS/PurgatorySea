#pragma once

class FPerson
{
    std::string Name; 
    bool bIsMarried; 
public:
    FPerson(); 
    bool GetMarried() const;
    void SetName(std::string InName);
    std::string GetName();
    void SetMarried(bool bInIsMarried);
};
