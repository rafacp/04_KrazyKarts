// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovingComponent.generated.h"


/**
* Structure for the Go Kart Move data
*/
USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Throttle;

	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;

	UPROPERTY()
	float Time;

	bool IsValid()const 
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	};
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

	FVector GetVelocity() { return Velocity; };
	void SetVelocity(FVector Val) { Velocity = Val; };
	void SetThrottle(float Val) { Throttle = Val; };
	void SetSteeringThrow(float Val) { SteeringThrow = Val; };

	FGoKartMove GetLastMove() { return LastMove; };

private:
	FGoKartMove CreateMove(float DeltaTime);

	FVector GetAirResistance();
	FVector GetRollingResistance();

	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime, float SteeringThrow);
	
	//Mass of the car (in Kg)
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	//The force applied to the car when the throttle is fully down (in N)
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	//Min Turning Radius at full lock (in m)
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10;

	//Higher means more drag (Kg/m)
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	//Higher means more rolling resistance
	UPROPERTY(EditAnywhere)
	float RollingResistenceCoefficient = 0.015f;
	
	FVector Velocity;
	
	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;
};
