// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class PurgatorySea : ModuleRules
{
	public string ProjectRoot => Path.GetFullPath(Path.Combine(ModuleDirectory, "../../"));
	
	public PurgatorySea(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HTTP",
			"Sockets",
			"Networking",
			"HttpServer",
			"Json",
			"JsonUtilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});
		
		PublicIncludePaths.Add(ProjectRoot + "../../Core/PurgatorySeaCore/");
		
		PublicAdditionalLibraries.Add(ProjectRoot + "../../Core/x64/Release/PurgatorySeaCore.lib");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
