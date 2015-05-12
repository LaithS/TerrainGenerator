#pragma once

#include "ProceduralTerrainChunk.h"
#include "GenericPlatformProcess.h"

class UTerrainGrid;

struct FTerrainWorkerTask
{
	FIntVector ChunkIdentifier;

	// Output Data
	TArray<FVector> Positions;
	TArray<FDynamicMeshVertex> Vertices;
	TArray<int32> Indices;

	// Input Data
	
	// Grid Params
	UTerrainGrid *TerrainGrid;
	FIntVector ChunkEndSize;
	FIntVector ChunkStartSize;

	// Marching Cubes Info
	float SurfaceCrossValue;

	// Chunk Info
	FVector ChunkScale;
	FVector ChunkLocation;
	FTransform TerrainTransform;

	FTerrainWorkerTask()
	{
	};
};

// Worker Thread for Terrain Marching
class FProceduralTerrainWorker : public FRunnable
{	
	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
	bool bIsRunning;
	FThreadSafeCounter StopTaskCounter;

public:

	// Queue for chunks that needs to be processed
	TQueue <FTerrainWorkerTask> QueuedTasks;

	// Queue for chunks that are processed and are ready to be sent to the render thread
	TQueue <FTerrainWorkerTask> FinishgedTasks;

	// Returns the number of this kind of threads 
	static int32 ThreadCount;

	// Returns the state of the thread
	bool IsRunning() const
	{
		return bIsRunning;
	};
	
	// Constructor Destructor
	FProceduralTerrainWorker();
	virtual ~FProceduralTerrainWorker();
 
	// 
	bool Start();
	void Shutdown();
	void EnsureCompletion();

	virtual bool Init() override;
	virtual uint32 Run();
	virtual void Stop() override;
	virtual void Exit() override;

private:
	bool WorkOnTask(FTerrainWorkerTask *WorkerTask);
	int PolygonizeToTriangles(UTerrainGrid *TerrainGrid, float p_fSurfaceCrossValue, FIntVector ChunkStartSize, FIntVector ChunkEndSize, TArray<FDynamicMeshVertex> *Vertices, TArray<int32> *Indices, TArray<FVector> *Positions, FVector &ChunkLocaiton, FVector &ChunkScale, FTransform &TerrainTransform);

 
 
};