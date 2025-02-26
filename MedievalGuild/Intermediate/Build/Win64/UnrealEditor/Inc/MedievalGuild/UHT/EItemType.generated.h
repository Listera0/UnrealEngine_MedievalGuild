// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "EItemType.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MEDIEVALGUILD_EItemType_generated_h
#error "EItemType.generated.h already included, missing '#pragma once' in EItemType.h"
#endif
#define MEDIEVALGUILD_EItemType_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MedievalGuild_Source_MedievalGuild_EItemType_h


#define FOREACH_ENUM_EITEMTYPE(op) \
	op(EItemType::Money) \
	op(EItemType::Gold) \
	op(EItemType::Silver) \
	op(EItemType::Ruby) \
	op(EItemType::Clothes) \
	op(EItemType::Weapon) 

enum class EItemType : uint8;
template<> struct TIsUEnumClass<EItemType> { enum { Value = true }; };
template<> MEDIEVALGUILD_API UEnum* StaticEnum<EItemType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
