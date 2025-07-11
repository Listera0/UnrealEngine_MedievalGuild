// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class MedievalGuild : ModuleRules
{
	public MedievalGuild(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore" ,"Json", "AIModule", "NavigationSystem",               // Add Json module
                "JsonUtilities", "ClothingSystemRuntimeInterface", "ChaosCloth"});

		PublicIncludePaths.Add(Path.Combine(EngineDirectory, "Plugins/ChaosClothAsset/Source/ChaosClothAssetEngine/Public"));

		PrivateDependencyModuleNames.AddRange(new string[] { "ChaosClothAsset" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
