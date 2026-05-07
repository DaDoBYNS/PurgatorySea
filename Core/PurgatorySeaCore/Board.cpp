#include "Board.h"

FBoard::FBoard()
{
    Width = 10;
    Height = 10;
}

void FBoard::InitPlayerBoard()
{
    Ships.clear();
    ReceivedShots.clear();
}

std::shared_ptr<FShip> FBoard::CreateShip(FPosition InPosition, int InDimension, const char* InName)
{
    Ships.emplace_back(std::make_shared<FShip>(InPosition, InDimension));
    Ships.back()->SetName(InName);

    return Ships.back();
}

EHitStatus FBoard::ReceiveShot(FPosition ShotPosition)
{
    if (HasReceivedShot(ShotPosition))
    {
        return EHitStatus::AlredyShot;
    }

    ReceivedShots.emplace_back(ShotPosition);

    for (auto& Ship : Ships)
    {
        if (Ship->ContainsPosition(ShotPosition))
        {
            Ship->RegisterHit(ShotPosition);

            if (Ship->GetIsSunk())
            {
                return EHitStatus::Sink;
            }

            return EHitStatus::Hit;
        }
    }

    return EHitStatus::Miss;
}

bool FBoard::HasReceivedShot(FPosition ShotPosition) const
{
    for (const auto& ReceivedShot : ReceivedShots)
    {
        if (ReceivedShot == ShotPosition)
        {
            return true;
        }
    }

    return false;
}

void FBoard::SetHeightAndWidth(int NewHeight, int NewWidth)
{
    Width = NewWidth;
    Height = NewHeight;

    Ships.clear();
    ReceivedShots.clear();
}

bool FBoard::AreAllShipsSunk() const
{
    if (Ships.empty())
    {
        return false;
    }

    for (const auto& Ship : Ships)
    {
        if (!Ship->GetIsSunk())
        {
            return false;
        }
    }

    return true;
}

std::vector<std::shared_ptr<FShip>> FBoard::GetShips()
{
    return Ships;
}

std::vector<FPosition> FBoard::GetReceivedShots() const
{
    return ReceivedShots;
}

int FBoard::GetHeight() const
{
    return Height;
}

int FBoard::GetWidth() const
{
    return Width;
}