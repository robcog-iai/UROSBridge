// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "UROSBridgeEdMode.h"
#include "Toolkits/IToolkitHost.h"
#include "AssetThumbnail.h"
#include "Toolkits/BaseToolkit.h"
#include "Editor.h"

class IDetailsView;
class SROSBridgeEd;
class SErrorText;
struct FPropertyAndParent;

class FUROSBridgeEdModeToolkit : public FModeToolkit
{
public:
	/** FModeToolkit interface */
	void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FUROSBridgeEdMode* GetEditorMode() const override;
	TSharedPtr<class SWidget> GetInlineContent() const override;


private:
	/** Geometry tools widget */
	TSharedPtr<SROSBridgeEd> ROSBridgeEdWidgets;
};

/**
* Slate widgets for the New Editor Mode
*/
class SROSBridgeEd : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SROSBridgeEd)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedRef<FUROSBridgeEdModeToolkit> InParentToolkit);

	void RefreshDetailPanel();

protected:

	class FUROSBridgeEdMode* GetEditorMode() const;

	FText GetErrorText() const;

	bool GetROSBridgeEdIsEnabled() const;

	bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;

	TSharedPtr<SErrorText> Error;

	TSharedPtr<IDetailsView> DetailsPanel;
};
