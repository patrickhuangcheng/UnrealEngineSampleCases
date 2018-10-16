// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollDice.generated.h"

UCLASS()
class SAMPLES_API ARollDice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARollDice();

	UFUNCTION(BlueprintCallable, Category ="AlgorithmControl")
	void StartRoll();

	UFUNCTION(BlueprintCallable, Category ="AlgorithmControl")
	void StopRoll();

protected:
	bool bIsPlayerFirst;
	int RoundCounter;
	/*for recording if computer player is win
	X: Player Score, Y: Computer Score*/
	TArray<FVector2D> Results;
	FVector2D TotalResult;
	TArray<FVector2D> PlayerRolls;
	TArray<FVector2D> ComputerRolls;

	void InitRoll();

	void RollDices();

	void OnRollDices();

	bool IsNeedCheat();

	FVector2D ShowResult(const FVector2D playerRoll, const FVector2D computerRoll);

	void PrintResult(const FVector2D Result);

	void SwitchTurn();

	bool CheckDouble(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll);

	bool CheckTotal(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll);

	bool CheckHighDie(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll);

	bool CheckDraw(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll);

	/*Get Result Text: Player Wins, ComputerWins, Draw*/
	FString ResultText(const FVector2D result);

	/*Get Computer Win Rate*/
	float AnalyzeComWinRate(const FVector2D CurrentResult = FVector2D::ZeroVector);
private:
	bool bIsRoll;
	FVector2D GetRandomDice();
};
