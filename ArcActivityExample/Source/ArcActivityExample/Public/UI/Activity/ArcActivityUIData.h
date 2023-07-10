// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcActivityUIObject.h"
#include "GameplayTagContainer.h"
#include "ArcActivityUIData.generated.h"


UENUM(BlueprintType)
enum class EArcActivityObjectiveDisplayMode : uint8
{
	MinMax,
	Percentage,
	Checkbox,
};

USTRUCT(BlueprintType)
struct FArcActivityObjectiveDisplay
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
	EArcActivityObjectiveDisplayMode DisplayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FGameplayTag ValueTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FGameplayTag MaxTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	FText ObjectiveText;
};

/**
 * 
 */
UCLASS(BlueprintType)
class ARCACTIVITYEXAMPLE_API UArcActivityUIData : public UArcActivityUIObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="UI")
	TObjectPtr<UUserWidget> Widget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TArray<FArcActivityObjectiveDisplay> ObjectiveDisplays;


};
