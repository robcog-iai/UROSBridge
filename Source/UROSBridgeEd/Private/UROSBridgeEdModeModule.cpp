// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen

#include "UROSBridgeEdModeModule.h"
#include "UROSBridgeEdMode.h"
#include "UROSBridgeEdTool.h"

#include "PropertyEditorModule.h"

#include "Styling/SlateStyleRegistry.h"
#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "FUROSBridgeEdModeModule"
#define IMAGE_PLUGIN_BRUSH( RelativePath, ...) FSlateImageBrush (FUROSBridgeEdModule::InContent( RelativePath, ".png"), __VA_ARGS__)

FString FUROSBridgeEdModule::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = FPaths::ProjectPluginsDir() / TEXT("UROSWorldControl/Content/Slate");
	return (ContentDir / RelativePath) + Extension;
}

TSharedPtr<FSlateStyleSet> FUROSBridgeEdModule::StyleSet = nullptr;
TSharedPtr<class ISlateStyle> FUROSBridgeEdModule::Get() { return StyleSet; }

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FUROSBridgeEdModule::Initialize()
{
	// Const icon sizes
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("ROSBridgeEdMode/Content/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	StyleSet->Set("LevelEditor.ROSBridgeEdMode", new IMAGE_PLUGIN_BRUSH("Icons/Icon128", Icon40x40));
	StyleSet->Set("LevelEditor.ROSBridgeEdMode.Small", new IMAGE_PLUGIN_BRUSH("Icons/Icon128", Icon20x20));
	StyleSet->Set("LevelEditor.ROSBridgeEdMode.Selected", new IMAGE_PLUGIN_BRUSH("Icons/Icon128", Icon40x40));
	StyleSet->Set("LevelEditor.ROSBridgeEdMode.Selected.Small", new IMAGE_PLUGIN_BRUSH("Icons/Icon128", Icon20x20));


	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_PLUGIN_BRUSH

FName FUROSBridgeEdModule::GetStyleSetName()
{
	static FName StyleName(TEXT("ROSBridgeEdMode"));
	return StyleName;
}

void FUROSBridgeEdModule::StartupModule()
{
	//Initialize styleset
	Initialize();

	//register mode
	FEditorModeRegistry::Get().RegisterMode<FUROSBridgeEdMode>(
		FUROSBridgeEdMode::EM_UROSBridgeEdModeId,
		LOCTEXT("ROSBridgeEdModeEdModeName", "ROSBridgeEdModeEdMode"),
		FSlateIcon(GetStyleSetName(), "LevelEditor.ROSBridgeEdMode", "LevelEditor.ROSBridgeEdMode.Small"),
		true
	);
}

void FUROSBridgeEdModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FUROSBridgeEdMode::EM_UROSBridgeEdModeId);
}

#undef LOCTEXT_NAMESPACE

#if ENGINE_MINOR_VERSION < 22
	IMPLEMENT_MODULE(FUROSBridgeEdModule, UROSBridgeEdMode)
#else
	IMPLEMENT_MODULE(FUROSBridgeEdModule, UROSBridgeEd)
#endif
