#include "Validation.h"

FValidation::FValidation()
    : bIsValid(false)
{}

void FValidation::ValidateShips()
{
    for (const auto& Ship : Board->GetShips())
    {
        for (const auto& Position : Ship->GetPositions())
        {
            if (Position.Letter > Board->GetWidth()-1 || Position.Letter < 0
                || Position.Number > Board->GetHeight()-1 || Position.Number < 0)
            {
                bIsValid = false;
                return;  
            }    
            
        }
    }
    
    bIsValid = true; 
}

void FValidation::SetBoard(std::shared_ptr<FBoard> InBoard)
{
    Board = InBoard;
}

bool FValidation::GetIsValid()
{
    return bIsValid; 
}
