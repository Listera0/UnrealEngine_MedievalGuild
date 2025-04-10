// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEffectDataAsset.h"

UItemEffectDataAsset::UItemEffectDataAsset()
{
	ItemIndex = 0;
	ItemTarget.Add(EEffectTarget::None);
	TargetValue.Add(0.0f);
}
