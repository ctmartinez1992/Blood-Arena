#ifndef RL_TRAIT_HPP
#define RL_TRAIT_HPP

/***************************************************/
/*************** Behaviours Messages ***************/
/***************************************************/
global_variable int UPDATES_UNTIL_BEHAVIOUR_FEAR_MERCY = 5;

global_variable char* BEHAVIOUR_FEAR_MERCY_M_INTRO = "kneels down and begs for mercy...";

//27
global_variable char BEHAVIOUR_FEAR_MERCY_M_TEST[][95] = {
	"Mercy 1", "Mercy 2", "Mercy 3", "Mercy 4", "Mercy 5", "Mercy 6", "Mercy 7", "Mercy 8", "Mercy 9",
	"Mercy 10", "Mercy 11", "Mercy 12", "Mercy 13", "Mercy 14", "Mercy 15", "Mercy 16", "Mercy 17",
	"Mercy 18", "Mercy 19", "Mercy 20", "Mercy 21", "Mercy 22", "Mercy 23", "Mercy 24", "Mercy 25",
	"Mercy 26", "Mercy 27"
};

global_variable int PRECOMPUTED_POWER_CHANCES[] = {
	0,
	50,	//Power = 1
	36,	//Power = 2
	22,	//Power = 3
	12,	//Power = 4
	7,	//Power = 5
};

/************************************************/
/*************** Actions Messages ***************/
/************************************************/
global_variable int UPDATES_UNTIL_ACT_INSULT = 3;
global_variable int UPDATES_UNTIL_ACT_TAUNT = 3;

//27
global_variable char TAUNT_M_TEST[][10] = {
	"Taunt 1", "Taunt 2", "Taunt 3", "Taunt 4", "Taunt 5", "Taunt 6", "Taunt 7", "Taunt 8", "Taunt 9",
	"Taunt 10", "Taunt 11", "Taunt 12", "Taunt 13", "Taunt 14", "Taunt 15", "Taunt 16", "Taunt 17",
	"Taunt 18", "Taunt 19", "Taunt 20", "Taunt 21", "Taunt 22", "Taunt 23", "Taunt 24", "Taunt 25",
	"Taunt 26", "Taunt 27"
};

class TraitBehaviour;
class TraitAction;

//TODO: I really should separate TraitAct and TraitBehaviour.
class Trait {
public:
	//NOTE: 1 - Most likely ... 5 - Least likely
	unsigned char power;

	Trait(unsigned char power);

	void
	HandleTraitActionMessage(Actor* owner, TraitAction* trait, int traitLimit, char* messageArray);

	virtual void
	Behave(Actor* owner) = 0;

	virtual void
	Act(Actor* owner) = 0;

protected:
    enum trait_type {
        TRAIT_TYPE_NONE = 0,
        //Behaviours
        TRAIT_TYPE_BEHAVIOUR_FEAR,
        //Actions
        TRAIT_TYPE_ACTION_TALK
    };
};

class Traits {
public:
	TCODList<Trait*> traits;

	Traits();
	~Traits();

	void
	GenerateTraits();

	void
	HandleTraits(Actor* owner);
};

/******************************************/
/*************** Behaviours ***************/
/******************************************/
class TraitBehaviour : public Trait {
public:
	TraitBehaviour(unsigned char power);

	virtual void
	Behave(Actor* owner) = 0;

	void
	Act(Actor* owner) {}
};

class TraitBehaviourFearMercy : public TraitBehaviour {
public:
	trait_type type;

    TraitBehaviourFearMercy(unsigned char power);

	void
	Behave(Actor* owner);
};

class TraitAction : public Trait {
public:
	//NOTE: When this variable reaches a predetermined limit, the trait is acted.
	int canAct;

	TraitAction(unsigned char power);

	void
	Behave(Actor* owner) {}

	virtual void
	Act(Actor* owner) = 0;
};

class TraitActionTalkTaunt : public TraitAction {
public:
	trait_type type;

    TraitActionTalkTaunt(unsigned char power);

	void
	Act(Actor* owner);
};

#endif