// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class catfinder_ue4 : ModuleRules
{
	public catfinder_ue4(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        bUseRTTI = true; // turn on RTTI

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        string libPath = "E:/catfinder/qideps/";

        PublicLibraryPaths.Add(libPath + "libqi-sdk/lib");
        PublicLibraryPaths.Add(libPath + "boost_1_61_0_x64/lib");
        PublicLibraryPaths.Add(libPath + "openssl-1.0.1t-vs2015/lib");

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicAdditionalLibraries.Add("qi.lib");
        } else
        {
            PublicAdditionalLibraries.Add("qi.lib");
        }

        PublicIncludePaths.Add(libPath + "libqi-sdk/include");
        PublicIncludePaths.Add(libPath + "boost_1_61_0_x64");

    }
}
