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
enum class EBaseDebuffType : uint8
{
	BURN,
	OIL,
	SHOCK,
	WET,
	CONFUSE,
	NONE,
};