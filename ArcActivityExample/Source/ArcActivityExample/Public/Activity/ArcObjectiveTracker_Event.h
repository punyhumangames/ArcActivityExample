// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataModel/ArcActivityTask_ObjectiveTracker.h"
#include "GameplayTagContainer.h"
#include "ArcActivityWorldSubsystem.h"
#include "ArcObjectiveTracker_Event.generated.h"

/**
 * 
 */
UCLASS()
class ARCACTIVITYEXAMPLE_API UArcObjectiveTracker_Event : public UArcActivityTask_ObjectiveTracker
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Activity")
	FGameplayTag EventTagToListenFor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	UScriptStruct* EventPayloadStruct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	EArcActivityMessageMatch EventMatchType;

	//Number of times to listen for this event before success
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	int32 MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	FGameplayTag UICurrentValueTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	FGameplayTag UIMaxValueTag;

	int32 Activations;

	virtual void BeginPlay_Implementation() override;
	virtual void EndPlay_Implementation(bool Canceled) override;	

private:
	FArcActivityMessageListenerHandle ListenerHandle;
	void MessageHandler(FGameplayTag Tag);
};
