// Fill out your copyright notice in the Description page of Project Settings.


#include "Activity/ArcObjectiveTracker_SubActivity.h"
#include "ArcActivityInstance.h"
#include "ArcActivityWorldSubsystem.h"
#include "DataModel/ArcActivity.h"
#include "ArcActivityTypes.h"

void UArcObjectiveTracker_SubActivity::BeginPlay_Implementation()
{
	if (!IsValid(Activity))
	{
		MarkFailure();
		return;
	}

	if (UArcActivityWorldSubsystem* WorldSubsystem = GetSubsystem())
	{
		SubActivityInstance = WorldSubsystem->StartActivity(Activity, ActivityTags);
		if (PlayerTransferMode == EArcSubActivityPlayerTransferMode::InheritPlayers)
		{
			for (auto Player : GetActivityInstance()->GetPlayersInActivity())
			{
				SubActivityInstance->AddPlayerToActivity(Player);
			}
		}

		ListenerHandle = WorldSubsystem->RegisterListener(FArcActivityStateChangedEventTag, this, &ThisClass::OnActivityStateChanged);
		

		GetActivityInstance()->SetTaggedData(UIMaxValueTag, 1);
		GetActivityInstance()->SetTaggedData(UICurrentValueTag, 0);
	}


}

void UArcObjectiveTracker_SubActivity::EndPlay_Implementation(bool Canceled)
{
	//We don't want to hear completions anymore from this
	ListenerHandle.Unregister();

	if (IsValid(SubActivityInstance))
	{
		if (ActivityCancellationMode == EArcSubActivityActivityCancelMode::CancelActivity)
		{
			SubActivityInstance->EndActivity(true);
		}
	}

	GetActivityInstance()->ClearTaggedData(UIMaxValueTag);
	GetActivityInstance()->ClearTaggedData(UICurrentValueTag);
}

void UArcObjectiveTracker_SubActivity::OnActivityStateChanged(FGameplayTag Channel, const FArcActivityActivityStateChanged& StateChangedPayload)
{
	if (StateChangedPayload.ActivityInstance != SubActivityInstance)
	{
		return;
	}

	const bool bFailure = StateChangedPayload.ActivityState == EArcActivitySuccessState::Failure;
	const bool bSuccess = StateChangedPayload.ActivityState == EArcActivitySuccessState::Success;
	const bool bCancelled = StateChangedPayload.ActivityState == EArcActivitySuccessState::Cancelled;
	const bool bActivityEnded = bFailure || bSuccess || bCancelled;

	if (bActivityEnded)
	{
		GetActivityInstance()->SetTaggedData(UICurrentValueTag, 1);

		if (bSuccess || (bActivityEnded && SuccessMode == EArcSubActivitySucceessMode::AnyCompletionSucceeds))
		{
			MarkSuccess();
		}
		else if (bFailure || bCancelled)
		{
			MarkFailure();
		}
	}
}
