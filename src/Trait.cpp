#include "main.hpp"

Trait::Trait(unsigned char power) :
	power(power)
{
}

void
Trait::HandleTraitActionMessage(Actor* owner, TraitAction* trait, int traitLimit, char* messageArray) {
	if(owner->ai->canDoActions) {
		if(trait->canAct >= traitLimit && !owner->ai->alreadyTalked) {
			e->gui->Message(TCODColor::white, "%s: %s", owner->name, messageArray);

			owner->ai->alreadyTalked = true;
			trait->canAct = 0;
		}

		trait->canAct++;
	}

	free(messageArray);
}

Traits::Traits() {
	GenerateTraits();
}

Traits::~Traits() {
	traits.clearAndDelete();
}

void
Traits::GenerateTraits() {
	traits.push(new TraitBehaviourFearMercy(1));
	traits.push(new TraitActionTalkInsult(1));
	traits.push(new TraitActionTalkTaunt(5));
}

void
Traits::HandleTraits(Actor* owner) {
	if(!traits.isEmpty()) {
		if(!owner->destructible->IsDead()) {
			for(Trait** it = traits.begin(); it != traits.end(); ++it) {
				(*it)->Behave(owner);
				(*it)->Act(owner);
			}
		}
	}
}

/******************************************/
/*************** Behaviours ***************/
/******************************************/
TraitBehaviour::TraitBehaviour(unsigned char power) :
	Trait(power)
{
}

TraitBehaviourFearMercy::TraitBehaviourFearMercy(unsigned char power) :
	TraitBehaviour(power),
	type(TRAIT_TYPE_BEHAVIOUR_FEAR)
{
}

void
TraitBehaviourFearMercy::Behave(Actor* owner) {
	if(!owner->ai->beggingForMercy && owner->destructible->curHP <= 5) {
		Ai* newAi = new OrcAiBegForMercy(owner->ai);
		owner->ai = newAi;

		e->gui->Message(TCODColor::white, "%s %s", owner->name, BEHAVIOUR_FEAR_MERCY_M_INTRO);
		//owner->ai->alreadyTalked = true;
	}
}

/*****************************************/
/**************** Actions ****************/
/*****************************************/
TraitAction::TraitAction(unsigned char power) :
	Trait(power),
	canAct(0)
{
}

TraitActionTalkTaunt::TraitActionTalkTaunt(unsigned char power) :
	TraitAction(power),
	type(TRAIT_TYPE_ACTION_TALK)
{
}

void
TraitActionTalkTaunt::Act(Actor* owner) {
	if(PercentageChance(PRECOMPUTED_POWER_CHANCES[power])) {
		int randomMessageIndex = RandomNumberInRange(0, ArrayCount(TAUNT_M_TEST) - 1);
		//HandleTraitActionMessage(owner, this, UPDATES_UNTIL_ACT_INSULT,
		//	TAUNT_M_TEST[randomMessageIndex]);
	}
}