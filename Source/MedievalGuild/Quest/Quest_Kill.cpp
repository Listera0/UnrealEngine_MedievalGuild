// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Kill.h"

bool UQuest_Kill::CheckQuest(int index)
{
	if (ObjectIndex == index)
	{
		Amount++;
	}

	if (Amount >= RequiredAmount)
	{
		CompleteQuest();
		return true;
	}

	return false;
}
