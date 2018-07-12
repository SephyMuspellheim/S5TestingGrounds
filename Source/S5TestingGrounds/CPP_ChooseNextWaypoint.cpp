// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" //TODO remove coupling

EBTNodeResult::Type UCPP_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	//get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Return task failed
	if (ensure(PatrolPoints.Num() <= 0))
	{
		return EBTNodeResult::Failed;
	}
	
	//set the next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();	
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle the Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//TODO protect against empty patrol routes

	//Return task succeeded
	return EBTNodeResult::Succeeded;
}
