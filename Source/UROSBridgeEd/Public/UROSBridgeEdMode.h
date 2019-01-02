// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "UROSBridgeEdTool.h"
#include "EdMode.h"

class UROSBridgeEdTool;

class FUROSBridgeEdMode : public FEdMode
{
public:
	UROSBridgeEdTool* UISettings;

	const static FEditorModeID EM_UROSBridgeEdModeId;

	/* Constructor */
	FUROSBridgeEdMode();

	/* Destructor */
	virtual ~FUROSBridgeEdMode();

	/** FGCObject interface */
	void AddReferencedObjects(FReferenceCollector& Collector) override;

	// FEdMode interface
	void Enter() override;
	void Exit() override;
	//virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	//virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void ActorSelectionChangeNotify() override;
	bool UsesToolkits() const override;
	// End of FEdMode interface
};
