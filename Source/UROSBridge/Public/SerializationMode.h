#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ESerializationMode : uint8 {
	MODE_JSON,
	MODE_BSON
};