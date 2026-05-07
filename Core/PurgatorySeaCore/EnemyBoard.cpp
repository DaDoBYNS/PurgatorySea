#include "EnemyBoard.h"

FEnemyBoard::FEnemyBoard()
{
}

void FEnemyBoard::InitEnemyBoard()
{
    EnemyShipPosition.clear();
    HitPositions.clear();
}

EHitStatus FEnemyBoard::SetHitPosition(FPosition HitPosition)
{
    if (CheckShot(HitPosition))
    {
        return EHitStatus::AlredyShot;
    }

    for (auto ShipPosition : EnemyShipPosition)
    {
        if (ShipPosition == HitPosition)
        {
            HitPositions.push_back({ShipPosition, EHitStatus::Hit});
            return EHitStatus::Hit;
        }
    }

    HitPositions.push_back({HitPosition, EHitStatus::Miss});
    return EHitStatus::Miss;
}

bool FEnemyBoard::CheckShot(FPosition HitPosition)
{
    for (auto ShotPosition : HitPositions)
    {
        if ( HitPosition == ShotPosition.Position)
        {
            return true;
        }
    }
    return false;
}

std::vector<FPosition> FEnemyBoard::GetEnemyShipPositions() const
{
    return EnemyShipPosition;
}

std::vector<SEnemyBoard> FEnemyBoard::GetHitPositions() const
{
    return HitPositions;
}

bool FEnemyBoard::AddShipPosition(FPosition ShipPosition)
{
    for ( auto OldPosition : EnemyShipPosition)
    {
        if (OldPosition == ShipPosition)
        {
            return false;
        }
    }

    EnemyShipPosition.push_back(ShipPosition);
    return true;
}
