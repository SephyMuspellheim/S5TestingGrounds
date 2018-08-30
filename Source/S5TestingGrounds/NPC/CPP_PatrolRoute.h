// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_PatrolRoute.generated.h"

/**
* A route card to help AI choose their next wayout
**/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S5TESTINGGROUNDS_API UCPP_PatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	

	TArray<AActor*>GetPatrolPoints() const;

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*> PatrolPoints;

};
