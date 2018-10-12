// Fill out your copyright notice in the Description page of Project Settings.
// Ref: https://docs.unrealengine.com/en-US/Programming/Introduction
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SampleCodingPractise.generated.h"

UCLASS()
class SAMPLES_API ASampleCodingPractise : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASampleCodingPractise();

//////////////////////////////////////////////////////////////////////////
// Variable Exposure I - from C++ to Blueprint 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VariableExposure | Damage")
    int32 TotalDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VariableExposure | Damage")
    float DamageTimeInSeconds;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "VariableExposure | Damage")
    float DamagePerSecond;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called after the constructor
	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void CalculateDamageValues();

//////////////////////////////////////////////////////////////////////////
//Iterators:

	//Iterator for getting all objects
	UFUNCTION(BlueprintCallable, Category = "Iterator")
	void GetAllObjectsItor();

	//Example of using GetAllObjectsName() in Blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Iterator")
	void GetAllObjectsName_BPNative();
	//The implementation of the above in c++
	void GetAllObjectsName_BPNative_Implementation();

	//Iterator with template for getting all objects
	template< class T >
	void GetAllObjectsName()
	{
		for (TObjectIterator<T> It; It; ++It)
		{
			T* CurrentObject = *It;
			UE_LOG(LogTemp, Log, TEXT("GetAllObjectsName:: Found %s named: %s"), *T::StaticClass()->GetFName().ToString(), *CurrentObject->GetName());
		}
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
