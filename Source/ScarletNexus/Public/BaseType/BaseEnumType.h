#pragma once

UENUM()
enum class EBaseConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EBaseValidType : uint8
{
	Valid,
	InValid,
};

UENUM()
enum class EBaseSuccessType : uint8
{
	Success,
	Failed,
};

UENUM(BlueprintType)
enum class EBaseDirectionType : uint8
{
	None = 0b0000,
	Front = 0b1101,
	Back = 0b1110,
	Left = 0b0111,
	Right = 0b1011,
	Max = 0b1111
};

UENUM(BlueprintType)
enum class EBaseAIDirectionType : uint8
{
	Forward   UMETA(DisplayName = "Forward"),
   Backward  UMETA(DisplayName = "Backward"),
   Left      UMETA(DisplayName = "Left"),
   Right     UMETA(DisplayName = "Right"),
   None      UMETA(DisplayName = "None")
	
};

UENUM()
enum class EProjectileDamagePolicy
{
	OnHit,
	OnBeginOverlap	
};