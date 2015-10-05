#ifndef RL_AI_HPP
#define RL_AI_HPP

class Ai : public Persistent {
public:
	bool canDoActions;
	bool alreadyTalked;
	bool beggingForMercy;

	Ai(bool canDoActions, bool alreadyTalked);

	internal_function Ai*
	Create(TCODZip& zip);

    virtual void
    Update(Actor* owner) = 0;

protected:
    enum ai_type {
        AI_TYPE_ORC,
		AI_TYPE_ORC_BEG_FOR_MERCY,
		AI_TYPE_PLAYER
	};
};

class OrcAi : public Ai {
public:
	OrcAi(bool canDoActions = true, bool alreadyTalked = false);

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	void
	Update(Actor* owner);

protected:
    void
    MoveOrAttack(Actor* owner, int targetx, int targety);
};

class OrcAiBegForMercy : public OrcAi {
protected:
    Ai* oldAi;

    int canBehave;

public:
    OrcAiBegForMercy(Ai* oldAi);

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	void
	Update(Actor* owner);
};

class PlayerAi : public Ai {
protected:
	bool inSandbox;

public:
    PlayerAi();

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	void
	Update(Actor* owner);

protected:
    bool
    MoveOrAttack(Actor* owner, int targetX, int targetY);

    void
    HandleActionKey(Actor* owner, char ascii);

    Actor*
    ChooseFromInventory(Actor* owner);

    void
    DisplayStats(Actor* owner);
};

#endif