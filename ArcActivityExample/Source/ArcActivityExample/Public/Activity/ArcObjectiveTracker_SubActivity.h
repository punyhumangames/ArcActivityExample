// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataModel/ArcActivityTask_ObjectiveTracker.h"
#include "ArcActivityWorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "ArcObjectiveTracker_SubActivity.generated.h"

UENUM(BlueprintType)
enum class EArcSubActivitySucceessMode : uint8
{
	//Any form of completion counts as success for this tracker
	AnyCompletionSucceeds,
	//The completion mode of the sub activity dictates the result of this tracker
	CompletionModeMatters,
};

UENUM(BlueprintType)
enum class EArcSubActivityPlayerTransferMode : uint8
{
	//All players in this activity will automatically join the sub activity
	InheritPlayers,
	//Players must explicitly join the sub activity
	ExplicitJoin,
};

UENUM(BlueprintType)
enum class EArcSubActivityActivityCancelMode : uint8
{
	//Cancel the activity if this tracker ends play while the activity is active.
	CancelActivity,
	//Do not cancel the activity if this tracker ends play
	DoNotCancelAbility,
};


/**
 * 
 */
UCLASS()
class ARCACTIVITYEXAMPLE_API UArcObjectiveTracker_SubActivity : public UArcActivityTask_ObjectiveTracker
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Activity")
	UArcActivity* Activity;

	UPROPERTY()
	UArcActivityInstance* SubActivityInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
		FGameplayTagContainer ActivityTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	EArcSubActivitySucceessMode SuccessMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	EArcSubActivityPlayerTransferMode PlayerTransferMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	EArcSubActivityActivityCancelMode ActivityCancellationMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	FGameplayTag UICurrentValueTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activity")
	FGameplayTag UIMaxValueTag;
	

	virtual void BeginPlay_Implementation() override;
	virtual void EndPlay_Implementation(bool Canceled) override;
private:
	FArcActivityMessageListenerHandle ListenerHandle;

	void OnActivityStateChanged(FGameplayTag Channel, const FArcActivityActivityStateChanged& StateChangedPayload);
};
