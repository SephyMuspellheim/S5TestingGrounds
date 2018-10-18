// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "S5TestingGrounds.h"


// Sets default values
UActorPool::UActorPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

AActor * UActorPool::Checkout()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
	}
	return Pool.Pop();
}

void UActorPool::Return(AActor * ActorToReturn)
{
	Add(ActorToReturn);
}

void UActorPool::Add(AActor * ActorToAdd)
{
	Pool.Push(ActorToAdd);
}
