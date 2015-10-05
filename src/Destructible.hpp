#ifndef RL_DESTRUCTIBLE_HPP
#define RL_DESTRUCTIBLE_HPP

class Destructible : public Persistent {
public:
    int maxHP;
    int curHP;

    float defense;

	Destructible(int maxHP, float defense);

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	internal_function Destructible*
	Create(TCODZip& zip);

	virtual void
	Die(Actor* owner);

    void
    TakeDamage(Actor* owner, int damage);

    int
    Heal(int amount);

	inline bool
	IsDead() {
		return(curHP <= 0);
	}

protected:
    enum destructible_type {
        DESTRUCTIBLE_TYPE_ORC,
		DESTRUCTIBLE_TYPE_PLAYER
    };
};

class OrcDestructible : public Destructible {
public:
    OrcDestructible(int maxHP, float defense);

	void
	Save(TCODZip& zip);

	void
	Die(Actor* owner);
};

class PlayerDestructible : public Destructible {
public:
	PlayerDestructible(int maxHP, float defense);

	void
	Save(TCODZip& zip);

    void
    Die(Actor* owner);
};

#endif