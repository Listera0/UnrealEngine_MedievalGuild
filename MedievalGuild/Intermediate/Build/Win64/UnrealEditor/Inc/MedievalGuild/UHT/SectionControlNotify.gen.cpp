// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MedievalGuild/SectionControlNotify.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSectionControlNotify() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UAnimNotifyState();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_USectionControlNotify();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_USectionControlNotify_NoRegister();
UPackage* Z_Construct_UPackage__Script_MedievalGuild();
// End Cross Module References

// Begin Class USectionControlNotify
void USectionControlNotify::StaticRegisterNativesUSectionControlNotify()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USectionControlNotify);
UClass* Z_Construct_UClass_USectionControlNotify_NoRegister()
{
	return USectionControlNotify::StaticClass();
}
struct Z_Construct_UClass_USectionControlNotify_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "SectionControlNotify.h" },
		{ "ModuleRelativePath", "SectionControlNotify.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NextSectionName_MetaData[] = {
		{ "Category", "SectionControl" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xaa\xa9\xed\x91\x9c \xec\x84\xb9\xec\x85\x98 \xec\x9d\xb4\xeb\xa6\x84\n" },
#endif
		{ "ModuleRelativePath", "SectionControlNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xaa\xa9\xed\x91\x9c \xec\x84\xb9\xec\x85\x98 \xec\x9d\xb4\xeb\xa6\x84" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_NextSectionName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USectionControlNotify>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_USectionControlNotify_Statics::NewProp_NextSectionName = { "NextSectionName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USectionControlNotify, NextSectionName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NextSectionName_MetaData), NewProp_NextSectionName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USectionControlNotify_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USectionControlNotify_Statics::NewProp_NextSectionName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USectionControlNotify_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USectionControlNotify_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotifyState,
	(UObject* (*)())Z_Construct_UPackage__Script_MedievalGuild,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USectionControlNotify_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USectionControlNotify_Statics::ClassParams = {
	&USectionControlNotify::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_USectionControlNotify_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_USectionControlNotify_Statics::PropPointers),
	0,
	0x001130A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USectionControlNotify_Statics::Class_MetaDataParams), Z_Construct_UClass_USectionControlNotify_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USectionControlNotify()
{
	if (!Z_Registration_Info_UClass_USectionControlNotify.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USectionControlNotify.OuterSingleton, Z_Construct_UClass_USectionControlNotify_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USectionControlNotify.OuterSingleton;
}
template<> MEDIEVALGUILD_API UClass* StaticClass<USectionControlNotify>()
{
	return USectionControlNotify::StaticClass();
}
USectionControlNotify::USectionControlNotify(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USectionControlNotify);
USectionControlNotify::~USectionControlNotify() {}
// End Class USectionControlNotify

// Begin Registration
struct Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_SectionControlNotify_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USectionControlNotify, USectionControlNotify::StaticClass, TEXT("USectionControlNotify"), &Z_Registration_Info_UClass_USectionControlNotify, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USectionControlNotify), 4136563383U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_SectionControlNotify_h_1741016537(TEXT("/Script/MedievalGuild"),
	Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_SectionControlNotify_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_SectionControlNotify_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
