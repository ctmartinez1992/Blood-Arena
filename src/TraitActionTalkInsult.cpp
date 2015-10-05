#include "main.hpp"

TraitActionTalkInsult::TraitActionTalkInsult(unsigned char power) :
	TraitAction(power),
	type(TRAIT_TYPE_ACTION_TALK)
{
}

void
TraitActionTalkInsult::Act(Actor* owner) {
	if(PercentageChance(PRECOMPUTED_POWER_CHANCES[power])) {
		char* result;
		char* resultStructure;

		if (PercentageChance(50)) {
			resultStructure = DODGetRandomContent(e->c->DOD_TRAIT_ACTION_INSULT, "!!desc", "1");
			char* insult1 = DODGetRandomContent(e->c->DOD_TRAIT_ACTION_INSULT_1, "!!desc", "all");

			result = ToString(resultStructure, insult1);

			free(insult1);
		} else {
			resultStructure = DODGetRandomContent(e->c->DOD_TRAIT_ACTION_INSULT, "!!desc", "2");
			char* insult1 = DODGetRandomContent(e->c->DOD_TRAIT_ACTION_INSULT_2, "!!desc", "1");
			char* insult2 = DODGetRandomContent(e->c->DOD_TRAIT_ACTION_INSULT_2, "!!desc", "2");

			result = ToString(resultStructure, insult1, insult2);

			free(insult1);
			free(insult2);
		}

		Trait::HandleTraitActionMessage(owner, this, UPDATES_UNTIL_ACT_INSULT, result);

		free(resultStructure);
	}
}