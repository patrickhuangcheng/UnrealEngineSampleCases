// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TP_VehicleMotorGameMode.h"
#include "TP_VehicleMotorPawn.h"
#include "TP_VehicleMotorHud.h"
#include "UObject/ConstructorHelpers.h"


ATP_VehicleMotorGameMode::ATP_VehicleMotorGameMode()
{
	static ConstructorHelpers::FClassFinder<ATP_VehicleMotorPawn> PawnClass(TEXT("/Game/SampleCases/TwoWheeledVehicle/VehicleMotor/BP_TP_MotorPawn"));
	if (PawnClass.Class)
	{
		DefaultPawnClass = PawnClass.Class;
	}
	else
	{
		DefaultPawnClass = ATP_VehicleMotorPawn::StaticClass();
	}
	HUDClass = ATP_VehicleMotorHud::StaticClass();
}
