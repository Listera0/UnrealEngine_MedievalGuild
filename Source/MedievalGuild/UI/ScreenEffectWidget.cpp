
#include "ScreenEffectWidget.h"
#include "Animation/WidgetAnimation.h"

void UScreenEffectWidget::NativeConstruct() 
{
	Super::NativeConstruct();

    DeathAnim = GetAnimationByName(TEXT("DeathAnimation"));
    MoveAnim = GetAnimationByName(TEXT("MoveAnimation"));
    FadeInAnim = GetAnimationByName(TEXT("FadeInAnimation"));
    FadeOutAnim = GetAnimationByName(TEXT("FadeOutAnimation"));
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
        StopAllAnimations();
        SetVisibility(ESlateVisibility::Visible);
        PlayAnimation(DeathAnim);
        EndAnimation(DeathAnim->GetEndTime());
    }
}
void UScreenEffectWidget::StartMoveStageAnimation()
{
    if (MoveAnim) {
        StopAllAnimations();
        SetVisibility(ESlateVisibility::Visible);
        PlayAnimation(MoveAnim);
        EndAnimation(MoveAnim->GetEndTime());
    }
}

void UScreenEffectWidget::StartFadeInAnimation()
{
    if (FadeInAnim) {
        StopAllAnimations();
        SetVisibility(ESlateVisibility::Visible);
        PlayAnimation(FadeInAnim);
        EndAnimation(FadeInAnim->GetEndTime());
    }
}

void UScreenEffectWidget::StartFadeOutAnimation()
{
    if (FadeOutAnim) {
        StopAllAnimations();
        SetVisibility(ESlateVisibility::Visible);
        PlayAnimation(FadeOutAnim);
        EndAnimation(FadeOutAnim->GetEndTime());
    }
}

void UScreenEffectWidget::EndAnimation(float time)
{
    FTimerHandle timer;
    GetWorld()->GetTimerManager().SetTimer(timer, [this]() {
        if (!IsAnyAnimationPlaying()) SetVisibility(ESlateVisibility::Collapsed);
        else { EndAnimation(0.1f); }
    }, time, false);
}

bool UScreenEffectWidget::CheckPlayingAnimation()
{
    return GetVisibility() == ESlateVisibility::Visible ? true : false;
}
