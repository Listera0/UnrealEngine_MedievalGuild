#include "Quest_Item.h"

bool UQuest_Item::CheckQuest(int ItemID)
{
	if (!QuestItem) return false;

	if (QuestItem->GetDefaultObject<AItem_Base>()->GetIndex() == ItemID)
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
