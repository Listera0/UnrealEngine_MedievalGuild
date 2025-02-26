// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Item_Base.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MEDIEVALGUILD_Item_Base_generated_h
#error "Item_Base.generated.h already included, missing '#pragma once' in Item_Base.h"
#endif
#define MEDIEVALGUILD_Item_Base_generated_h

#define FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAItem_Base(); \
	friend struct Z_Construct_UClass_AItem_Base_Statics; \
public: \
	DECLARE_CLASS(AItem_Base, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MedievalGuild"), NO_API) \
	DECLARE_SERIALIZER(AItem_Base)


#define FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AItem_Base(AItem_Base&&); \
	AItem_Base(const AItem_Base&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItem_Base); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItem_Base); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AItem_Base) \
	NO_API virtual ~AItem_Base();


#define FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_11_PROLOG
#define FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_14_INCLASS_NO_PURE_DECLS \
	FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MEDIEVALGUILD_API UClass* StaticClass<class AItem_Base>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MedievalGuild_Source_MedievalGuild_Item_Base_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
