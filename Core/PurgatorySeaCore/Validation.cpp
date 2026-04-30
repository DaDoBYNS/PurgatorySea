#include "Validation.h"

FValidation::FValidation()
    : bIsValid(false)
{}

void FValidation::ValidateShips()
{
    bool bTempIsValid = true; 
    
    for (const auto& Ship : Board->GetShips())
    {
        for (const auto& Position : Ship->GetPositions())
        {
            if (Position.Letter > Board->GetWidth()-1 || Position.Letter < 0
                || Position.Number > Board->GetHeight()-1 || Position.Number < 0)
            {
                bTempIsValid = false;
            }
            
            for (const auto& CheckShip : Board->GetShips())
            {
                if (Ship == CheckShip)
                {
                    continue; 
                }
                
                for (const auto& CheckPosition : CheckShip->GetPositions())
                {
                    if (CheckPosition.Letter == Position.Letter && CheckPosition.Number == Position.Number)
                    {
                        bTempIsValid = false; 
                    }
                }
                
            }
            
        }
    }
    
    bIsValid = bTempIsValid; 
}

void FValidation::SetBoard(std::shared_ptr<FBoard> InBoard)
{
    Board = InBoard;
}

bool FValidation::GetIsValid()
{
    return bIsValid; 
}
