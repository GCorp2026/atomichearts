// Copyright (c) 2026 Atomic Hearts Team. All Rights Reserved.

#include "Inputs/InputConfig.h"
#include "InputAction.h"

const UInputAction* UAtomichartsInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
    for (const FAtomichartsInputAction& Action : NativeInputActions)
    {
        if (Action.InputTag == InputTag)
        {
            return Action.InputAction;
        }
    }
    return nullptr;
}
