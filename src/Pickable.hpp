#ifndef RL_PICKABLE_HPP
#define RL_PICKABLE_HPP

class Pickable : public Persistent {
public:
	internal_function Pickable*
	Create(TCODZip& zip);

	virtual bool
	Use(Actor* owner, Actor* wearer);

    bool
    Pick(Actor* owner, Actor* wearer);

	void
	Drop(Actor* owner, Actor* wearer);

protected:
    enum pickable_type {
        PICKABLE_TYPE_HEALER,
		PICKABLE_TYPE_LIGHTNING_BOLT,
		PICKABLE_TYPE_CONFUSER,
		PICKABLE_TYPE_FIREBALL
    };
};

class Healer : public Pickable {
public:
    int amount;

	Healer(int amount);

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	bool
	Use(Actor* owner, Actor* wearer);
};

class LightningBolt : public Pickable {
public:
	int range;
	int damage;

	LightningBolt(int range, int damage);

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	bool
	Use(Actor* owner, Actor* wearer);
};

class Fireball : public LightningBolt {
public:
    Fireball(int range, int damage);

	bool
	Use(Actor* owner, Actor* wearer);

	void
	Save(TCODZip& zip);
};

#endif