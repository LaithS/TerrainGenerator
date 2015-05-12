// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DynamicMeshBuilder.h"
#include "ProceduralTerrainChunk.generated.h"

class AProceduralTerrain;
class UTerrainGrid;

UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class TERRAINGENERATOR_API UProceduralTerrainChunk : public UMeshComponent, public IInterface_CollisionDataProvider
{
	GENERATED_BODY()
public:
	UProceduralTerrainChunk(const FObjectInitializer &ObjectInitializer);

	FIntVector ChunkLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Procedural Terrain")
	FTransform TerrainTransform;

	UPROPERTY(BlueprintReadWrite, Category = "Procedural Terrain")
	AProceduralTerrain *Terrain;

	//UPROPERTY(BlueprintReadWrite, Category = "Procedural Terrain")
	//UTerrainGrid *TerrainGrid;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Terrain")
	bool IsUpdating;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Terrain")
	bool HasChanges;

	/** Set the geometry to use on this triangle mesh */

	/** Description of collision */
	UPROPERTY(BlueprintReadOnly, Category = "Collision")
	class UBodySetup* ModelBodySetup;

	UPROPERTY(BlueprintReadOnly, Category = "Collision")
	bool IsCollisionEnabled;

	UPROPERTY(BlueprintReadOnly, Category = "Rendering")
	bool IsRenderable;


	// Begin Interface_CollisionDataProvider Interface
	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	virtual bool WantsNegXTriMesh() override{ return false; }
	// End Interface_CollisionDataProvider Interface
	// Begin UPrimitiveComponent interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual class UBodySetup* GetBodySetup() override;
	// End UPrimitiveComponent interface.
	// Begin UMeshComponent interface.
	virtual int32 GetNumMaterials() const override;
	// End UMeshComponent interface.

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void UpdateBodySetup();

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void UpdateCollision();

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void RemoveCollision();


	void MarkRenderable(bool bRenderable = true);

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void RegenerateVoxelData();

	UFUNCTION(BlueprintCallable, Category = "Procedural Terrain")
	void UpdateVertexData();

	TArray<FVector> Positions;
	TArray<FDynamicMeshVertex> Vertices;
	TArray<int32> Indices;

	virtual void BeginDestroy() override;
private:

	// Begin USceneComponent interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform & LocalToWorld) const override;
	// Begin USceneComponent interface.
	/** */
	friend class FProceduralTerrainChunkSceneProxy;
};