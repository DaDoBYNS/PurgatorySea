#include "Board.h"


FBoard::FBoard()
{
    Width = 10;
    Height = 10;
}

void FBoard::InitPlayerBoard()
{
    PlayerShips.clear();
}

void FBoard::SetHeightAndWidth(int NewHeight, int NewWidth)
{
    Width = NewWidth;
    Height = NewHeight;

    PlayerShips.clear();
}

bool FBoard::PlaceShip(FPosition Position)
{
    int X = static_cast<int>(Position.Letter);
    int Y = static_cast<int>(Position.Number);

    if (X < 0 || X >= Width || Y < 0 || Y >= Height)
    {
        return false;
    }

    for (const auto& Ship : PlayerShips)
    {
        if (Ship == Position)
        {
            return false;
        }
    }

    PlayerShips.push_back(Position);
    return true;
}

std::vector<FPosition> FBoard::GetPlayerBoard()
{
    return PlayerShips;
}
