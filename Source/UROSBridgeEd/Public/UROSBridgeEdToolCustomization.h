#pragma once

#include "IDetailCustomization.h"
#include "Reply.h"

class FUROSBridgeEdToolCustomization : public IDetailCustomization
{
public:
	//IDetailCustomization interface
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	//End of IdetailCustomization itnerface

	static TSharedRef<IDetailCustomization> MakeInstance();

	static FReply ExecuteCommand(IDetailLayoutBuilder* DetailBuilder, UFunction* MethodToExecute);
};
