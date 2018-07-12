// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UCPP_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//UE_LOG(LogTemp, Warning, TEXT("AI in C++!"));

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	
	//TODO provide more rich return system, allowing for failsafe if task fails.
	//Return task succeeded
	return EBTNodeResult::Succeeded;
}
