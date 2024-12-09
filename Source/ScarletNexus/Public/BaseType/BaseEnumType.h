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

UENUM()
enum class EBaseDirectionType : uint8
{
	Front,
	Back,
	Left,
	Right,
	InValid
};