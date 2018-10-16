// Fill out your copyright notice in the Description page of Project Settings.

#include "RollDice.h"
#include "TimerManager.h"

// Sets default values
ARollDice::ARollDice()
{
 	// Defaults
	bIsRoll = false;
}

void ARollDice::StartRoll()
{// Start to Roll method
	bIsRoll = true;
	InitRoll();
	UE_LOG(LogClass, Log, TEXT("\n---===Start to Roll===---"));
	RollDices();
}

void ARollDice::StopRoll()
{// Quit rolling by the player
	UE_LOG(LogClass, Log, TEXT("---===Stop Rolling===---"));
	bIsRoll = false;
}

void ARollDice::InitRoll()
{// reset cached data
	bIsPlayerFirst = true;
	RoundCounter = 0;
	Results.Empty();
	TotalResult = FVector2D::ZeroVector;
	PlayerRolls.Empty();
	ComputerRolls.Empty();
}

void ARollDice::RollDices()
{// timer for calling RollDices() each second
	if (bIsRoll)
	{
		OnRollDices();
		FTimerHandle RollDiceTimerHandle;
		GetWorldTimerManager().SetTimer(RollDiceTimerHandle, this, &ARollDice::RollDices, 1.f, false);
	}
	
}

void ARollDice::OnRollDices()
{
	UE_LOG(LogClass, Log, TEXT("\n---===Round %d::Rolling===---"), RoundCounter+1);
	FVector2D playerRoll =  GetRandomDice();
	FVector2D computerRoll = GetRandomDice();
	if (IsNeedCheat())
	{
		if (ResultText(ShowResult(playerRoll, computerRoll)) == FString(TEXT("Player Wins")))
		{// Swap roll result if player wins, CHEATING
			PlayerRolls.Add(computerRoll);
			ComputerRolls.Add(playerRoll);
		}
		else if (ResultText(ShowResult(playerRoll, computerRoll)) == FString(TEXT("Exception Warning")))
		{// in the case of exception, make the round draw
			PlayerRolls.Add(FVector2D::ZeroVector);
			ComputerRolls.Add(FVector2D::ZeroVector);
		}
		else
		{// in case of expanding as per the cheat result / needs
			PlayerRolls.Add(playerRoll);
			ComputerRolls.Add(computerRoll);
		}
	}
	else
	{
		PlayerRolls.Add(playerRoll);
		ComputerRolls.Add(computerRoll);
	}
	

	if (bIsPlayerFirst)
	{// output the result of roll, simulating as the real roll sequence
		UE_LOG(LogClass, Log, TEXT("Player Roll: DieI: %d  DieII:%d"), (uint8)PlayerRolls[RoundCounter].X, (uint8)PlayerRolls[RoundCounter].Y);
		UE_LOG(LogClass, Log, TEXT("Computer Roll: DieI: %d  DieII:%d"), (uint8)ComputerRolls[RoundCounter].X, (uint8)ComputerRolls[RoundCounter].Y);
	}
	else
	{
		UE_LOG(LogClass, Log, TEXT("Computer Roll: DieI: %d  DieII:%d"), (uint8)ComputerRolls[RoundCounter].X, (uint8)ComputerRolls[RoundCounter].Y);
		UE_LOG(LogClass, Log, TEXT("Player Roll: DieI: %d  DieII:%d"), (uint8)PlayerRolls[RoundCounter].X, (uint8)PlayerRolls[RoundCounter].Y);
	}
	FVector2D Result = ShowResult(PlayerRolls[RoundCounter], ComputerRolls[RoundCounter]);
	PrintResult(Result);
}

bool ARollDice::IsNeedCheat()
{
	return AnalyzeComWinRate() < 0.7 && RoundCounter %3!=0;
}

FVector2D ARollDice::ShowResult(const FVector2D playerRoll, const FVector2D computerRoll)
{// Check Rolls as per rules
	FVector2D result = FVector2D::ZeroVector;
	if (CheckDouble(result, playerRoll, computerRoll))
	{
		return result;
	}
	else if (CheckTotal(result, playerRoll, computerRoll))
	{
		return result;
	}
	else if (CheckHighDie(result, playerRoll, computerRoll))
	{
		return result;
	}
	else if (CheckDraw(result, playerRoll, computerRoll))
	{
		return result;
	}
	else
	{
		result = FVector2D(-1,-1);
		return result;
	}

}

void ARollDice::PrintResult(const FVector2D Result)
{
	UE_LOG(LogClass, Log, TEXT("---===Roll Result:: %s, Com Win Rate:: %f===---\n"), *ResultText(Result), AnalyzeComWinRate(Result));
	Results.Add(Result);
	SwitchTurn();
}

void ARollDice::SwitchTurn()
{
	bIsPlayerFirst = !bIsPlayerFirst;
	RoundCounter++;
}

bool ARollDice::CheckDouble(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll)
{
	bool isFinish = false;
	bool isPlayerDouble = playerRoll.X == playerRoll.Y;
	bool isComputerDouble = computerRoll.X == computerRoll.Y;
	if (isPlayerDouble || isComputerDouble)
	{
		isFinish = true;
		if (isPlayerDouble && isComputerDouble)
		{// Double compare
			if (playerRoll.X == computerRoll.X)
			{// Draw
				OutResult =FVector2D(0, 0);
			}
			else
			{// Compare
				OutResult = playerRoll.X > computerRoll.X ?
					FVector2D(1, 0) : FVector2D(0, 1);
// 				Results.Add(result);
			}
		}
		else
		{// Double wins
			OutResult = FVector2D(isPlayerDouble, isComputerDouble);
		}
	}
	return isFinish;
}

bool ARollDice::CheckTotal(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll)
{
	bool isFinish = false;
	if (playerRoll.X + playerRoll.Y != computerRoll.X + computerRoll.Y)
	{
		isFinish = true;
		OutResult = playerRoll.X + playerRoll.Y > computerRoll.X + computerRoll.Y ?
			FVector2D(1, 0) : FVector2D(0, 1);
///		Results.Add(result);
	}
	return isFinish;
}

bool ARollDice::CheckHighDie(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll)
{
	bool isFinish = false;
	if (playerRoll.X + playerRoll.Y == computerRoll.X + computerRoll.Y &&
		FMath::Max(playerRoll.X, playerRoll.Y) != FMath::Max(computerRoll.X, computerRoll.Y))
	{
		isFinish = true;
		OutResult = FMath::Max(playerRoll.X, playerRoll.Y) > FMath::Max(computerRoll.X, computerRoll.Y) ?
			FVector2D(1, 0) : FVector2D(0, 1);
// 		Results.Add(result);
	}
	return isFinish;
}

bool ARollDice::CheckDraw(FVector2D& OutResult, const FVector2D playerRoll, const FVector2D computerRoll)
{
	bool isFinish = false;
	if (FMath::Max(playerRoll.X, playerRoll.Y) == FMath::Max(computerRoll.X, computerRoll.Y) &&
		FMath::Min(playerRoll.X, playerRoll.Y) == FMath::Min(computerRoll.X, computerRoll.Y))
	{
		isFinish = true;
// 		Results.Add(FVector2D(0, 0));
		OutResult = FVector2D(0, 0);
	}
	return isFinish;
}

FString ARollDice::ResultText(const FVector2D result)
{// interpreting the result
	if (result.X == 0 && result.Y == 0)
	{
		return FString(TEXT("Draw"));
	}
	else
	{
		return result.X > result.Y ? FString(TEXT("Player Wins")) : FString(TEXT("Computer Wins"));
	}

	if (result.X == -1 && result.Y == -1)
	{
		return FString(TEXT("Exception Warning"));
	}
}

float ARollDice::AnalyzeComWinRate(const FVector2D CurrentResult)
{// checks the computer winning rate
	TotalResult += CurrentResult;// Results[RoundCounter];
	float result = TotalResult.Y / (TotalResult.X + TotalResult.Y);
	return result;
}

FVector2D ARollDice::GetRandomDice()
{// roll the dice
	return FVector2D(FMath::RandRange(1, 6), FMath::RandRange(1, 6));
}

