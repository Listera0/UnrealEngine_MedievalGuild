#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractInterface.generated.h"

// 인터페이스 정의
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
    GENERATED_BODY()
};

// 인터페이스 클래스 구현
class MEDIEVALGUILD_API IInteractInterface
{
    GENERATED_BODY()

public:
    virtual void SetInteractDistance(float distance) = 0;
    virtual float GetInteractDistance() = 0;
};
