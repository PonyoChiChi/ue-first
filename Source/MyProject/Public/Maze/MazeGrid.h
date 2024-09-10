
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGrid.generated.h"


USTRUCT(BlueprintType)
struct FMazeNeighbours
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="MazeGrid")
	bool bIsRoadOnTheLeft = false;

	UPROPERTY(BlueprintReadWrite, Category="MazeGrid")
	bool bIsRoadOnTheRight = false;

	UPROPERTY(BlueprintReadWrite, Category="MazeGrid")
	bool bIsRoadAbove = false;

	UPROPERTY(BlueprintReadWrite, Category="MazeGrid")
	bool bIsRoadBelow = false;
	
};


UCLASS()
class MYPROJECT_API AMazeGrid : public AActor
{
	GENERATED_BODY()

	
public:
	AMazeGrid();
	
	
private:
	TArray<TArray<bool>> Maze;
	TArray<TArray<int32>> Walls;

	UPROPERTY(BlueprintGetter=GetMazeWidth, Category="MazeGrid")
	int32 Width = 0;

	UPROPERTY(BlueprintGetter=GetMazeHeight, Category="MazeGrid")
	int32 Height = 0;

	
protected:
	virtual void BeginPlay() override;

	
public:
	virtual void Tick(float DeltaTime) override;


private:
	void AddWalls(const int32& RowInd, const int32& ColInd);
	void InitializeMaze();
	void AddBorderWalls();
	void GenerateMazeGrid();


public:
	UFUNCTION(BlueprintCallable, Category="MazeGrid")
	bool GetMazeCell(const int32& RowInd, const int32& ColInd);

	UFUNCTION(BlueprintCallable, Category="MazeGrid")
	FMazeNeighbours GetMazeCellNeighbours(const int32& RowInd, const int32& ColInd);

	UFUNCTION(BlueprintCallable, Category="MazeGrid")
	void CreateMaze(const int32& HeightValue, const int32& WidthValue);
	
	UFUNCTION(BlueprintGetter, Category="MazeGrid")
	int32 GetMazeWidth() const;

	UFUNCTION(BlueprintGetter, Category="MazeGrid")
	int32 GetMazeHeight() const;
	
};
