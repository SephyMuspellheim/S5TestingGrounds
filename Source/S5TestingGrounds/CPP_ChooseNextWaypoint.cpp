// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "CPP_PatrolRoute.h"

EBTNodeResult::Type UCPP_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//get the patrol points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UCPP_PatrolRoute>();
	if (!ensure(PatrolRoute)) {	return EBTNodeResult::Failed; }
	
	//Warn about empty patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard has no patrol points allocated")); 
		return EBTNodeResult::Failed;
	}

	
	//set the next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();	
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle the Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//Return task succeeded
	return EBTNodeResult::Succeeded;
}
