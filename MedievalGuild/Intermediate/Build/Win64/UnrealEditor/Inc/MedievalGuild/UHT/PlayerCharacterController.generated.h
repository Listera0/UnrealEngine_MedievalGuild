// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PlayerCharacterController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MEDIEVALGUILD_PlayerCharacterController_generated_h
#error "PlayerCharacterController.generated.h already included, missing '#pragma once' in PlayerCharacterController.h"
#endif
#define MEDIEVALGUILD_PlayerCharacterController_generated_h

#define FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlayerCharacterController(); \
	friend struct Z_Construct_UClass_APlayerCharacterController_Statics; \
public: \
	DECLARE_CLASS(APlayerCharacterController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MedievalGuild"), NO_API) \
	DECLARE_SERIALIZER(APlayerCharacterController)


#define FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	APlayerCharacterController(APlayerCharacterController&&); \
	APlayerCharacterController(const APlayerCharacterController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerCharacterController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerCharacterController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APlayerCharacterController) \
	NO_API virtual ~APlayerCharacterController();


#define FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h_14_PROLOG
#define FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h_17_INCLASS_NO_PURE_DECLS \
	FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MEDIEVALGUILD_API UClass* StaticClass<class APlayerCharacterController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_MedievalGuild_Source_MedievalGuild_PlayerCharacterController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
