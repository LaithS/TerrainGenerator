#pragma once

#include "ProceduralTerrain.h"
#include "GeneratedTerrain.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TERRAINGENERATOR_API AGeneratedTerrain : public AProceduralTerrain
{
	GENERATED_BODY()
public:
	AGeneratedTerrain(const FObjectInitializer& PCIP);
};