// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class catfinder_ue4 : ModuleRules
{
	public catfinder_ue4(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        bUseRTTI = true; // turn on RTTI
        UEBuildConfiguration.bForceEnableExceptions = true;

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        
        string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
        ThirdPartyPath = Path.Combine(ThirdPartyPath, (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86");

        PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "libqi", "lib"));
        PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "boost_1_61_0_x64", "lib"));
        PublicLibraryPaths.Add(Path.Combine(ThirdPartyPath, "openssl-1.0.1t-vs2015", "lib"));

        if (Target.Configuration != UnrealTargetConfiguration.DebugGame)
        {
            PublicAdditionalLibraries.Add("qi.lib");
        } else {
            PublicAdditionalLibraries.Add("qi.lib");
        }

        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "libqi", "include"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "boost_1_61_0_x64", "include"));
    }
}
