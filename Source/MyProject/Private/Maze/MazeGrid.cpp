
#include "Maze/MazeGrid.h"



AMazeGrid::AMazeGrid()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMazeGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMazeGrid::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMazeGrid::AddWalls(const int32& RowInd, const int32& ColInd)
{
	if (ColInd > 1 && Maze[RowInd][ColInd-2] == false)
	{
		Walls.Add({RowInd, ColInd-1, RowInd, ColInd-2});
	}
	if (ColInd < this->Width-2 && Maze[RowInd][ColInd+2] == false)
	{
		Walls.Add({RowInd, ColInd+1, RowInd, ColInd+2});
	}
	if (RowInd > 1 && Maze[RowInd-2][ColInd] == false)
	{
		Walls.Add({RowInd-1, ColInd, RowInd-2, ColInd});
	}
	if (RowInd < this->Height-2 && Maze[RowInd+2][ColInd] == false)
	{
		Walls.Add({RowInd+1, ColInd, RowInd+2, ColInd});
	}
}

void AMazeGrid::InitializeMaze()
{
	UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'InitializeMaze' started."));
	Maze.SetNum(Height);
	for  (int RowInd = 0; RowInd < Height; RowInd++)
	{
		Maze[RowInd].SetNum(Width);
		for (int ColInd = 0; ColInd < Width; ColInd++)
		{
			Maze[RowInd][ColInd] = false;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'InitializeMaze' finished. (Num=%d)"), Maze.Num());
}

void AMazeGrid::GenerateMazeGrid(const int32& HeightValue, const int32& WidthValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'GenerateMazeGrid' started."));
	this->Height = HeightValue;
	this->Width = WidthValue;
	this->InitializeMaze();
	
	if (Maze.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'GenerateMazeGrid' error. (Num=%d)"), Maze.Num());
		return;
	}

	const int32 StartRowInd = FMath::RandRange(0,  this->Height-1); // rand
	const int32 StartColInd = FMath::RandRange(0,  this->Width-1);; // rand
	Maze[StartRowInd][StartColInd] = true;
	AddWalls(StartRowInd, StartColInd);
		
	int32 RandomIndex = -1;
	int32 WallRowInd = -1;
	int32 WallColInd = -1;
	int32 RoomRowInd = -1;
	int32 RoomColInd = -1;
	
	while (Walls.Num() > 0)
	{
		RandomIndex = FMath::RandRange(0,  Walls.Num()-1);
		WallRowInd = Walls[RandomIndex][0];
		WallColInd = Walls[RandomIndex][1];
		RoomRowInd = Walls[RandomIndex][2];
		RoomColInd = Walls[RandomIndex][3];
		
		Walls.RemoveAt(RandomIndex);

		if (Maze[RoomRowInd][RoomColInd] == false)
		{
			Maze[WallRowInd][WallColInd] = true;
			Maze[RoomRowInd][RoomColInd] = true;
			AddWalls(RoomRowInd, RoomColInd);
			
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'GenerateMazeGrid' finished."));
}

int32 AMazeGrid::GetMazeWidth() const
{
	return Width;
}

int32 AMazeGrid::GetMazeHeight() const
{
	return Height;
}

bool AMazeGrid::GetMazeCell(const int32& RowInd, const int32& ColInd)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'GetMazeCell' started."));
	if (Maze.Num() != 0 && Maze.IsValidIndex(RowInd) && Maze[RowInd].IsValidIndex(ColInd))
	{
		UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'GetMazeCell' finished."));
		return Maze[RowInd][ColInd];
	}
	UE_LOG(LogTemp, Warning, TEXT("Debug Message: 'GetMazeCell' error. (Num=%d)"), Maze.Num());
	return false;
}

FMazeRoadNeighbours AMazeGrid::GetMazeCellNeighbours(const int32& RowInd, const int32& ColInd)
{
	FMazeRoadNeighbours MazeRoadNeighbours;
	
	if (Maze[RowInd].IsValidIndex(ColInd-1) && Maze[RowInd][ColInd-1] == true)
	{
		MazeRoadNeighbours.bIsRoadOnTheLeft = true;
	}
	if (Maze[RowInd].IsValidIndex(ColInd+1) && Maze[RowInd][ColInd+1] == true)
	{
		MazeRoadNeighbours.bIsRoadOnTheRight = true;
	}
	if (Maze.IsValidIndex(RowInd-1) && Maze[RowInd-1][ColInd] == true)
	{
		MazeRoadNeighbours.bIsRoadBelow = true;
	}
	if (Maze.IsValidIndex(RowInd+1) && Maze[RowInd+1][ColInd] == true)
	{
		MazeRoadNeighbours.bIsRoadAbove = true;
	}
	return MazeRoadNeighbours;
}

