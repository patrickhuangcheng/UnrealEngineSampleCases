// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleCodingPractise.h"


// Sets default values
ASampleCodingPractise::ASampleCodingPractise()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TotalDamage = 200;
	DamageTimeInSeconds = 1.f;
}

// Called when the game starts or when spawned
void ASampleCodingPractise::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASampleCodingPractise::PostInitProperties()
{
	Super::PostInitProperties();
	CalculateDamageValues();
}

#if WITH_EDITOR
void ASampleCodingPractise::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateDamageValues();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
void ASampleCodingPractise::CalculateDamageValues()
{
	if (DamageTimeInSeconds != 0)
	{
		DamagePerSecond = TotalDamage / DamageTimeInSeconds;
	}
}

// Called every frame
void ASampleCodingPractise::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

