// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Engine/LevelScriptActor.h"
#include "FunctionalTestLevelScript.generated.h"

UCLASS(notplaceable, meta=(KismetHideOverrides = "ReceiveAnyDamage,ReceivePointDamage,ReceiveRadialDamage,ReceiveActorBeginOverlap,ReceiveActorEndOverlap,ReceiveHit,ReceiveDestroyed,ReceiveActorBeginCursorOver,ReceiveActorEndCursorOver,ReceiveActorOnClicked,ReceiveActorOnReleased,ReceiveActorOnInputTouchBegin,ReceiveActorOnInputTouchEnd,ReceiveActorOnInputTouchEnter,ReceiveActorOnInputTouchLeave"), HideCategories=(Collision,Rendering,"Utilities|Transformation"))
class FUNCTIONALTESTING_API AFunctionalTestLevelScript : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()
	
};