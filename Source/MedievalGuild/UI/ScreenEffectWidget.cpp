
#include "ScreenEffectWidget.h"
#include "Animation/WidgetAnimation.h"

void UScreenEffectWidget::NativeConstruct() 
{
	Super::NativeConstruct();

    DeathAnim = GetAnimationByName(TEXT("DeathAnimation"));
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
        PlayAnimation(DeathAnim);
        SetVisibility(ESlateVisibility::Visible);
        FTimerHandle timer;
        GetWorld()->GetTimerManager().SetTimer(timer, [this]() {
            SetVisibility(ESlateVisibility::Collapsed);
        }, DeathAnim->GetEndTime(), false);
    }
}
