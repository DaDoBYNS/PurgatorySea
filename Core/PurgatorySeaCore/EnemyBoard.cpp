#include "EnemyBoard.h"

FEnemyBoard::FEnemyBoard()
{
}

void FEnemyBoard::InitEnemyBoard()
{
    HitPositions.clear();
}

EHitStatus FEnemyBoard::SetHitPosition(FPosition HitPosition, EHitStatus HitStatus)
{
    if (CheckShot(HitPosition))
    {
        return EHitStatus::AlredyShot;
    }

    HitPositions.push_back({HitPosition, HitStatus});
    return HitStatus;
}

bool FEnemyBoard::CheckShot(FPosition HitPosition) const
{
    for (const auto& ShotPosition : HitPositions)
    {
        if (HitPosition == ShotPosition.Position)
        {
            return true;
        }
    }

    return false;
}

int FEnemyBoard::GetSunkShipsCount() const
{
    int SunkShipsCount = 0;

    for (const auto& HitPosition : HitPositions)
    {
        if (HitPosition.Type == EHitStatus::Sink)
        {
            SunkShipsCount++;
        }
    }

    return SunkShipsCount;
}

std::vector<SEnemyBoard> FEnemyBoard::GetHitPositions() const
{
    return HitPositions;
}