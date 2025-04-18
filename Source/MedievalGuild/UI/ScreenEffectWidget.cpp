
#include "ScreenEffectWidget.h"
#include "Animation/WidgetAnimation.h"

void UScreenEffectWidget::NativeConstruct() 
{
	Super::NativeConstruct();

    DeathAnim = GetAnimationByName(TEXT("DeathAnimation"));
    MoveAnim = GetAnimationByName(TEXT("MoveAnimation"));
}

UWidgetAnimation* UScreenEffectWidget::GetAnimationByName(FName AnimName)
{
    for (TFieldIterator<FObjectProperty> Prop(GetClass()); Prop; ++Prop)
    {
        FObjectProperty* ObjectProp = *Prop;
        if (ObjectProp->PropertyClass == UWidgetAnimation::StaticClass())
        {
            if (ObjectProp->GetName() == AnimName.ToString())
            {
                return Cast<UWidgetAnimation>(ObjectProp->GetObjectPropertyValue_InContainer(this));
            }
        }
    }
    return nullptr;
}

void UScreenEffectWidget::StartDeathAnimation()
{
    if (DeathAnim) {
        SetVisibility(ESlateVisibility::Visible);
        PlayAnimation(DeathAnim);
        EndAnimation(DeathAnim->GetEndTime());
    }
}
void UScreenEffectWidget::StartMoveStageAnimation()
{
    if (MoveAnim) {
        SetVisibility(ESlateVisibility::Visible);
        PlayAnimation(MoveAnim);
        EndAnimation(MoveAnim->GetEndTime());
    }
}

void UScreenEffectWidget::EndAnimation(float time)
{
    FTimerHandle timer;
    GetWorld()->GetTimerManager().SetTimer(timer, [this]() {
        SetVisibility(ESlateVisibility::Collapsed);
    }, time, false);
}

bool UScreenEffectWidget::CheckPlayingAnimation()
{
    return GetVisibility() == ESlateVisibility::Visible ? true : false;
}
