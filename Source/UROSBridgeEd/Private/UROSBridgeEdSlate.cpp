// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen

#include "UROSBridgeEdSlate.h"
#include "UROSBridgeEdMode.h"
#include "UROSBridgeEdTool.h"
#include "UROSBridgeEdToolCustomization.h"
#include "Engine/Selection.h"

#include "PropertyEditorModule.h"
#include "SlateOptMacros.h"

#include "IDetailsView.h"
#include "IIntroTutorials.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FUROSBridgeEdTool"


void FUROSBridgeEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	FUROSBridgeEdMode* ROSBridgeEdMode = GetEditorMode();

	ROSBridgeEdWidgets = SNew(SROSBridgeEd, SharedThis(this));

	FModeToolkit::Init(InitToolkitHost);
}

FName FUROSBridgeEdModeToolkit::GetToolkitFName() const
{
	return FName("ROSBridgeEd");
}

FText FUROSBridgeEdModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("Toolkitname", "New Editor");
}

FUROSBridgeEdMode* FUROSBridgeEdModeToolkit::GetEditorMode() const
{
	return (FUROSBridgeEdMode*)GLevelEditorModeTools().GetActiveMode(
		FUROSBridgeEdMode::EM_UROSBridgeEdModeId);
}

TSharedPtr<SWidget> FUROSBridgeEdModeToolkit::GetInlineContent() const
{
	return ROSBridgeEdWidgets;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SROSBridgeEd::Construct(const FArguments& InArgs,
                                      TSharedRef<FUROSBridgeEdModeToolkit> InParentToolkit)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(
		"PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout("ROSBridgeEdTool",
	                                               FOnGetDetailCustomizationInstance::CreateStatic(
		                                               &FUROSBridgeEdToolCustomization::MakeInstance));
	PropertyEditorModule.NotifyCustomizationModuleChanged();

	FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);

	DetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsPanel->SetIsPropertyVisibleDelegate(
		FIsPropertyVisible::CreateSP(this, &SROSBridgeEd::GetIsPropertyVisible));

	FUROSBridgeEdMode* ROSBridgeEdMode = GetEditorMode();

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(0)
		[
			SNew(SVerticalBox)
			.IsEnabled(this, &SROSBridgeEd::GetROSBridgeEdIsEnabled)
			+ SVerticalBox::Slot()
			.Padding(0)
			[
				DetailsPanel.ToSharedRef()
			]
		]
	];

	RefreshDetailPanel();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FUROSBridgeEdMode* SROSBridgeEd::GetEditorMode() const
{
	return (FUROSBridgeEdMode*)GLevelEditorModeTools().GetActiveMode(
		FUROSBridgeEdMode::EM_UROSBridgeEdModeId);
}

FText SROSBridgeEd::GetErrorText() const
{
	FUROSBridgeEdMode* ROSBridgeEdMode = GetEditorMode();

	return FText::GetEmpty();
}

bool SROSBridgeEd::GetROSBridgeEdIsEnabled() const
{
	FUROSBridgeEdMode* ROSBridgeEdMode = GetEditorMode();
	if (ROSBridgeEdMode)
	{
		return true;
	}
	return false;
}

bool SROSBridgeEd::GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const
{
	return true;
}

void SROSBridgeEd::RefreshDetailPanel()
{
	FUROSBridgeEdMode* ROSBridgeEdMode = GetEditorMode();
	if (ROSBridgeEdMode)
	{
		// Refresh details panel
		DetailsPanel->SetObject(ROSBridgeEdMode->UISettings, true);
	}
}
#undef LOCTEXT_NAMESPACE
