// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MedievalGuild/EItemType.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEItemType() {}

// Begin Cross Module References
MEDIEVALGUILD_API UEnum* Z_Construct_UEnum_MedievalGuild_EItemType();
UPackage* Z_Construct_UPackage__Script_MedievalGuild();
// End Cross Module References

// Begin Enum EItemType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EItemType;
static UEnum* EItemType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EItemType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EItemType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MedievalGuild_EItemType, (UObject*)Z_Construct_UPackage__Script_MedievalGuild(), TEXT("EItemType"));
	}
	return Z_Registration_Info_UEnum_EItemType.OuterSingleton;
}
template<> MEDIEVALGUILD_API UEnum* StaticEnum<EItemType>()
{
	return EItemType_StaticEnum();
}
struct Z_Construct_UEnum_MedievalGuild_EItemType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Clothes.DisplayName", "Clothes" },
		{ "Clothes.Name", "EItemType::Clothes" },
		{ "Gold.DisplayName", "Gold" },
		{ "Gold.Name", "EItemType::Gold" },
		{ "ModuleRelativePath", "EItemType.h" },
		{ "Money.DisplayName", "Money" },
		{ "Money.Name", "EItemType::Money" },
		{ "Ruby.DisplayName", "Ruby" },
		{ "Ruby.Name", "EItemType::Ruby" },
		{ "Silver.DisplayName", "Silver" },
		{ "Silver.Name", "EItemType::Silver" },
		{ "Weapon.DisplayName", "Weapon" },
		{ "Weapon.Name", "EItemType::Weapon" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EItemType::Money", (int64)EItemType::Money },
		{ "EItemType::Gold", (int64)EItemType::Gold },
		{ "EItemType::Silver", (int64)EItemType::Silver },
		{ "EItemType::Ruby", (int64)EItemType::Ruby },
		{ "EItemType::Clothes", (int64)EItemType::Clothes },
		{ "EItemType::Weapon", (int64)EItemType::Weapon },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MedievalGuild_EItemType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MedievalGuild,
	nullptr,
	"EItemType",
	"EItemType",
	Z_Construct_UEnum_MedievalGuild_EItemType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MedievalGuild_EItemType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MedievalGuild_EItemType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MedievalGuild_EItemType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MedievalGuild_EItemType()
{
	if (!Z_Registration_Info_UEnum_EItemType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EItemType.InnerSingleton, Z_Construct_UEnum_MedievalGuild_EItemType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EItemType.InnerSingleton;
}
// End Enum EItemType

// Begin Registration
struct Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_EItemType_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EItemType_StaticEnum, TEXT("EItemType"), &Z_Registration_Info_UEnum_EItemType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3738037376U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_EItemType_h_794433254(TEXT("/Script/MedievalGuild"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_EItemType_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_EItemType_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
