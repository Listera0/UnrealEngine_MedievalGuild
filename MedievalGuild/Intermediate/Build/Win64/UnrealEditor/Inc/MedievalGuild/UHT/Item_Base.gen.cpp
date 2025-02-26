// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MedievalGuild/Item_Base.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeItem_Base() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_AItem_Base();
MEDIEVALGUILD_API UClass* Z_Construct_UClass_AItem_Base_NoRegister();
MEDIEVALGUILD_API UEnum* Z_Construct_UEnum_MedievalGuild_EItemType();
UPackage* Z_Construct_UPackage__Script_MedievalGuild();
// End Cross Module References

// Begin Class AItem_Base
void AItem_Base::StaticRegisterNativesAItem_Base()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AItem_Base);
UClass* Z_Construct_UClass_AItem_Base_NoRegister()
{
	return AItem_Base::StaticClass();
}
struct Z_Construct_UClass_AItem_Base_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Item_Base.h" },
		{ "ModuleRelativePath", "Item_Base.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mesh_MetaData[] = {
		{ "Category", "Item" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8 \xec\x84\xb8\xed\x8c\x85\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item_Base.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xbb\xb4\xed\x8f\xac\xeb\x84\x8c\xed\x8a\xb8 \xec\x84\xb8\xed\x8c\x85" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_eItemType_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Item_Base.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_price_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Item_Base.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Item_Base.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_description_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Item_Base.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_index_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Item_Base.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mesh;
	static const UECodeGen_Private::FBytePropertyParams NewProp_eItemType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_eItemType;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_price;
	static const UECodeGen_Private::FNamePropertyParams NewProp_name;
	static const UECodeGen_Private::FNamePropertyParams NewProp_description;
	static const UECodeGen_Private::FIntPropertyParams NewProp_index;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AItem_Base>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_mesh = { "mesh", nullptr, (EPropertyFlags)0x002008000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItem_Base, mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mesh_MetaData), NewProp_mesh_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_eItemType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_eItemType = { "eItemType", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItem_Base, eItemType), Z_Construct_UEnum_MedievalGuild_EItemType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_eItemType_MetaData), NewProp_eItemType_MetaData) }; // 3738037376
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_price = { "price", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItem_Base, price), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_price_MetaData), NewProp_price_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItem_Base, name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_name_MetaData), NewProp_name_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_description = { "description", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItem_Base, description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_description_MetaData), NewProp_description_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AItem_Base_Statics::NewProp_index = { "index", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AItem_Base, index), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_index_MetaData), NewProp_index_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AItem_Base_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_eItemType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_eItemType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_price,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AItem_Base_Statics::NewProp_index,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AItem_Base_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AItem_Base_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MedievalGuild,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AItem_Base_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AItem_Base_Statics::ClassParams = {
	&AItem_Base::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AItem_Base_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AItem_Base_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AItem_Base_Statics::Class_MetaDataParams), Z_Construct_UClass_AItem_Base_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AItem_Base()
{
	if (!Z_Registration_Info_UClass_AItem_Base.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AItem_Base.OuterSingleton, Z_Construct_UClass_AItem_Base_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AItem_Base.OuterSingleton;
}
template<> MEDIEVALGUILD_API UClass* StaticClass<AItem_Base>()
{
	return AItem_Base::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AItem_Base);
AItem_Base::~AItem_Base() {}
// End Class AItem_Base

// Begin Registration
struct Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AItem_Base, AItem_Base::StaticClass, TEXT("AItem_Base"), &Z_Registration_Info_UClass_AItem_Base, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AItem_Base), 2656631780U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_865544543(TEXT("/Script/MedievalGuild"),
	Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_MedievalGuild_Source_MedievalGuild_Item_Base_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
