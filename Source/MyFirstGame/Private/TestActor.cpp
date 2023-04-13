// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include <string>

#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
//视图配置设置
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloatingCube"));
	VisualMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0, 0, 0)); //设置初始位置
	}
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector new_location = GetActorLocation();//默认新位置
	FRotator new_rotation = GetActorRotation();//默认新角度
	const float running_time = GetGameTimeSinceCreation();
	const float delta_height = (FMath::Sin(running_time + DeltaTime) - FMath::Sin(running_time));//跳幅高度
	new_location.Z += delta_height * 20.0f;
	const float delta_rotation=DeltaTime * 20.0f;//旋转幅度
	new_rotation.Yaw += delta_rotation;
	SetActorLocationAndRotation(new_location, new_rotation);//修改位置和旋转
}
