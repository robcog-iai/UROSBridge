// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#include "UROSBridgeEdMode.h"
#include "UROSBridgeEdSlate.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FUROSBridgeEdMode::EM_UROSBridgeEdModeId = TEXT("EM_UROSBridgeEdMode");

FUROSBridgeEdMode::FUROSBridgeEdMode()
{
	UISettings = NewObject<UROSBridgeEdTool>(GetTransientPackage(), TEXT("UROSBridgeEdTool"), RF_Transactional);
	UISettings->SetParent(this);
}

FUROSBridgeEdMode::~FUROSBridgeEdMode()
{
}

void FUROSBridgeEdMode::AddReferencedObjects(FReferenceCollector& Collector)
{
	// Call parent implementation
	FEdMode::AddReferencedObjects(Collector);

	Collector.AddReferencedObject(UISettings);
}

void FUROSBridgeEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FUROSBridgeEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FUROSBridgeEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FUROSBridgeEdMode::UsesToolkits() const
{
	return true;
}
