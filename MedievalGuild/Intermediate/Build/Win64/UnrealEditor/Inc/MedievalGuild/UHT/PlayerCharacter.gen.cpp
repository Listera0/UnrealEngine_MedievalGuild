// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MedievalGuild/PlayerCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayerCharacter() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_APlayerCharacter();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_APlayerCharacter_NoRegister();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_USectionControlNotify_NoRegister();
MEDIEVALGUILD_API UEnum* Z_Construct_UEnum_MedievalGuild_MoveState();
UPackage* Z_Construct_UPackage__Script_MedievalGuild();
// End Cross Module References

// Begin Enum MoveState
static FEnumRegistrationInfo Z_Registration_Info_UEnum_MoveState;
static UEnum* MoveState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_MoveState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_MoveState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MedievalGuild_MoveState, (UObject*)Z_Construct_UPackage__Script_MedievalGuild(), TEXT("MoveState"));
	}
	return Z_Registration_Info_UEnum_MoveState.OuterSingleton;
}
template<> MEDIEVALGUILD_API UEnum* StaticEnum<MoveState>()
{
	return MoveState_StaticEnum();
}
struct Z_Construct_UEnum_MedievalGuild_MoveState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Idle.DisplayName", "Idle" },
		{ "Idle.Name", "MoveState::Idle" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
		{ "Run.DisplayName", "Run" },
		{ "Run.Name", "MoveState::Run" },
		{ "Stealth.DisplayName", "Stealth" },
		{ "Stealth.Name", "MoveState::Stealth" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "MoveState::Idle", (int64)MoveState::Idle },
		{ "MoveState::Run", (int64)MoveState::Run },
		{ "MoveState::Stealth", (int64)MoveState::Stealth },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MedievalGuild_MoveState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MedievalGuild,
	nullptr,
	"MoveState",
	"MoveState",
	Z_Construct_UEnum_MedievalGuild_MoveState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MedievalGuild_MoveState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MedievalGuild_MoveState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MedievalGuild_MoveState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MedievalGuild_MoveState()
{
	if (!Z_Registration_Info_UEnum_MoveState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_MoveState.InnerSingleton, Z_Construct_UEnum_MedievalGuild_MoveState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_MoveState.InnerSingleton;
}
// End Enum MoveState

// Begin Class APlayerCharacter Function OnSectionJumpEnd
struct Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics
{
	struct PlayerCharacter_eventOnSectionJumpEnd_Parms
	{
		const USectionControlNotify* SectionControl;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SectionControl;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::NewProp_SectionControl = { "SectionControl", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlayerCharacter_eventOnSectionJumpEnd_Parms, SectionControl), Z_Construct_UClass_USectionControlNotify_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::NewProp_SectionControl,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APlayerCharacter, nullptr, "OnSectionJumpEnd", nullptr, nullptr, Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::PlayerCharacter_eventOnSectionJumpEnd_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::PlayerCharacter_eventOnSectionJumpEnd_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlayerCharacter::execOnSectionJumpEnd)
{
	P_GET_OBJECT(USectionControlNotify,Z_Param_SectionControl);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSectionJumpEnd(Z_Param_SectionControl);
	P_NATIVE_END;
}
// End Class APlayerCharacter Function OnSectionJumpEnd

// Begin Class APlayerCharacter Function OnSectionJumpReady
struct Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics
{
	struct PlayerCharacter_eventOnSectionJumpReady_Parms
	{
		const USectionControlNotify* SectionControl;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SectionControl;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::NewProp_SectionControl = { "SectionControl", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PlayerCharacter_eventOnSectionJumpReady_Parms, SectionControl), Z_Construct_UClass_USectionControlNotify_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::NewProp_SectionControl,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APlayerCharacter, nullptr, "OnSectionJumpReady", nullptr, nullptr, Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::PropPointers), sizeof(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::PlayerCharacter_eventOnSectionJumpReady_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::Function_MetaDataParams), Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::PlayerCharacter_eventOnSectionJumpReady_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APlayerCharacter::execOnSectionJumpReady)
{
	P_GET_OBJECT(USectionControlNotify,Z_Param_SectionControl);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSectionJumpReady(Z_Param_SectionControl);
	P_NATIVE_END;
}
// End Class APlayerCharacter Function OnSectionJumpReady

// Begin Class APlayerCharacter
void APlayerCharacter::StaticRegisterNativesAPlayerCharacter()
{
	UClass* Class = APlayerCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnSectionJumpEnd", &APlayerCharacter::execOnSectionJumpEnd },
		{ "OnSectionJumpReady", &APlayerCharacter::execOnSectionJumpReady },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APlayerCharacter);
UClass* Z_Construct_UClass_APlayerCharacter_NoRegister()
{
	return APlayerCharacter::StaticClass();
}
struct Z_Construct_UClass_APlayerCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "PlayerCharacter.h" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[] = {
		{ "Category", "PlayerCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerCamera_MetaData[] = {
		{ "Category", "PlayerCharacter" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerMoveState_MetaData[] = {
		{ "Category", "CharaterOption" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NormalMoveSpeed_MetaData[] = {
		{ "Category", "CharaterOption" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RunningMoveSpeed_MetaData[] = {
		{ "Category", "CharaterOption" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StealthMoveSpeed_MetaData[] = {
		{ "Category", "CharaterOption" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackMontage_MetaData[] = {
		{ "Category", "PlayerMovement" },
		{ "ModuleRelativePath", "PlayerCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerCamera;
	static const UECodeGen_Private::FBytePropertyParams NewProp_PlayerMoveState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PlayerMoveState;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NormalMoveSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RunningMoveSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StealthMoveSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackMontage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APlayerCharacter_OnSectionJumpEnd, "OnSectionJumpEnd" }, // 589182405
		{ &Z_Construct_UFunction_APlayerCharacter_OnSectionJumpReady, "OnSectionJumpReady" }, // 1292171478
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayerCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x0020080000090009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArm_MetaData), NewProp_SpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayerCamera = { "PlayerCamera", nullptr, (EPropertyFlags)0x0020080000090009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, PlayerCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerCamera_MetaData), NewProp_PlayerCamera_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayerMoveState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayerMoveState = { "PlayerMoveState", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, PlayerMoveState), Z_Construct_UEnum_MedievalGuild_MoveState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerMoveState_MetaData), NewProp_PlayerMoveState_MetaData) }; // 525420252
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NormalMoveSpeed = { "NormalMoveSpeed", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, NormalMoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NormalMoveSpeed_MetaData), NewProp_NormalMoveSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunningMoveSpeed = { "RunningMoveSpeed", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, RunningMoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RunningMoveSpeed_MetaData), NewProp_RunningMoveSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_StealthMoveSpeed = { "StealthMoveSpeed", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, StealthMoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StealthMoveSpeed_MetaData), NewProp_StealthMoveSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayerCharacter_Statics::NewProp_AttackMontage = { "AttackMontage", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayerCharacter, AttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackMontage_MetaData), NewProp_AttackMontage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_SpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayerCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayerMoveState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_PlayerMoveState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_NormalMoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_RunningMoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_StealthMoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayerCharacter_Statics::NewProp_AttackMontage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APlayerCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_MedievalGuild,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayerCharacter_Statics::ClassParams = {
	&APlayerCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APlayerCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_APlayerCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlayerCharacter()
{
	if (!Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton, Z_Construct_UClass_APlayerCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlayerCharacter.OuterSingleton;
}
template<> MEDIEVALGUILD_API UClass* StaticClass<APlayerCharacter>()
{
	return APlayerCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlayerCharacter);
APlayerCharacter::~APlayerCharacter() {}
// End Class APlayerCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_PlayerCharacter_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ MoveState_StaticEnum, TEXT("MoveState"), &Z_Registration_Info_UEnum_MoveState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 525420252U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlayerCharacter, APlayerCharacter::StaticClass, TEXT("APlayerCharacter"), &Z_Registration_Info_UClass_APlayerCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayerCharacter), 1659773385U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_PlayerCharacter_h_3285406739(TEXT("/Script/MedievalGuild"),
	Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_PlayerCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_PlayerCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_PlayerCharacter_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_PlayerCharacter_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
