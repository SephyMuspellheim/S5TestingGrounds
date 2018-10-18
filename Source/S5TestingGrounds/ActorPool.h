// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class S5TESTINGGROUNDS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UActorPool();

	AActor* Checkout();
	void Return(AActor* ActorToReturn);

	void Add(AActor* ACtorToAdd);

private:
	TArray<AActor*> Pool;

};
