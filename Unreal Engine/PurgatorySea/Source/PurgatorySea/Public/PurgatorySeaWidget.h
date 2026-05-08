#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class APurgatorySeaControllerActor;

class PURGATORYSEA_API SPurgatorySeaWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPurgatorySeaWidget)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<APurgatorySeaControllerActor>, ControllerActor)
	SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

private:
	TWeakObjectPtr<APurgatorySeaControllerActor> ControllerActor;
	TSharedPtr<STextBlock> StatusText;

	FReply OnValidateClicked();
};