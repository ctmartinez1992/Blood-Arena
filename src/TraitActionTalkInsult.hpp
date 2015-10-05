#ifndef RL_TRAIT_ACTION_TALK_INSULT_HPP
#define RL_TRAIT_ACTION_TALK_INSULT_HPP

class TraitActionTalkInsult : public TraitAction {
public:
	trait_type type;

    TraitActionTalkInsult(unsigned char power);

	void
	Act(Actor* owner);
};

#endif