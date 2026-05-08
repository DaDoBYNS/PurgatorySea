#include "PurgatorySeaWidget.h"

#include "PurgatorySeaControllerActor.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void SPurgatorySeaWidget::Construct(const FArguments& InArgs)
{
    ControllerActor = InArgs._ControllerActor;

    ChildSlot
    [
       SNew(SOverlay)

       + SOverlay::Slot()
       .HAlign(HAlign_Right)
       .VAlign(VAlign_Bottom)
       .Padding(20.f)
       [
          SNew(SBorder)
          .Padding(15.f)
          .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
          .BorderBackgroundColor(FLinearColor(0.05f, 0.05f, 0.05f, 0.85f))
          [
             SNew(SVerticalBox)

             + SVerticalBox::Slot()
             .AutoHeight()
             .Padding(0.f, 0.f, 0.f, 10.f)
             [
                SAssignNew(StatusText, STextBlock)
                .Text(FText::FromString(TEXT("Piazza le navi e convalida.")))
                .ColorAndOpacity(FLinearColor::White)
                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 18))
             ]

             + SVerticalBox::Slot()
             .AutoHeight()
             [
                SNew(SBox)
                .WidthOverride(220.f)
                .HeightOverride(55.f)
                [
                   SNew(SButton)
                   .HAlign(HAlign_Center)
                   .VAlign(VAlign_Center)
                   .OnClicked(this, &SPurgatorySeaWidget::OnValidateClicked)
                   [
                      SNew(STextBlock)
                      .Text(FText::FromString(TEXT("CONVALIDA NAVI")))
                      .ColorAndOpacity(FLinearColor::White)
                      .Font(FCoreStyle::GetDefaultFontStyle("Bold", 18))
                   ]
                ]
             ]
          ]
       ]
    ];
}

FReply SPurgatorySeaWidget::OnValidateClicked()
{
    if (!ControllerActor.IsValid())
    {
       if (StatusText.IsValid())
       {
          StatusText->SetText(FText::FromString(TEXT("Errore: controller non trovato.")));
       }

       return FReply::Handled();
    }

    ControllerActor->RequestReady();

    if (StatusText.IsValid())
    {
       StatusText->SetText(FText::FromString(TEXT("Validazione eseguita. Controlla le navi.")));
    }

    return FReply::Handled();
}