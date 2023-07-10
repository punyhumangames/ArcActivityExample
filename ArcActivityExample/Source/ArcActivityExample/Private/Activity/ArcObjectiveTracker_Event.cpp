// Fill out your copyright notice in the Description page of Project Settings.


#include "Activity/ArcObjectiveTracker_Event.h"
#include "ArcActivityWorldSubsystem.h"
#include "ArcActivityInstance.h"

void UArcObjectiveTracker_Event::BeginPlay_Implementation()
{
	if (!EventTagToListenFor.IsValid())
	{
		MarkFailure();
		return;
	}

	Activations = 0;

	if (UArcActivityWorldSubsystem* WorldSubsystem = GetSubsystem())
	{
		auto Callback = [this](FGameplayTag Tag, const UScriptStruct* ScriptStruct, const void* Data)
		{
			if (IsValid(this))
			{
				MessageHandler(Tag);
			}
		};
		ListenerHandle = WorldSubsystem->UNSAFE_DANGER_RegisterListenerInternal(EventTagToListenFor, Callback, EventPayloadStruct, EventMatchType);

		GetActivityInstance()->SetStatTagStack(UIMaxValueTag, MaxCount);
		GetActivityInstance()->SetStatTagStack(UICurrentValueTag, 0);
	}
}

void UArcObjectiveTracker_Event::EndPlay_Implementation(bool Canceled)
{
	//We don't want to hear completions anymore from this
	if (ListenerHandle.IsValid())
	{
		ListenerHandle.Unregister();
	}

	GetActivityInstance()->ClearStatTag(UIMaxValueTag);
	GetActivityInstance()->ClearStatTag(UICurrentValueTag);
}

void UArcObjectiveTracker_Event::MessageHandler(FGameplayTag Tag)
{
	Activations = FMath::Min(Activations + 1, MaxCount);

	GetActivityInstance()->SetStatTagStack(UICurrentValueTag, Activations);

	if (Activations >= MaxCount)
	{
		ListenerHandle.Unregister();
		MarkSuccess();
		return;
	}
}
