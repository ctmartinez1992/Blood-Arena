#ifndef RL_ACTOR_HPP
#define RL_ACTOR_HPP

class Actor : public Persistent {
public:
	int	x;
	int	y;

	//NOTE: A sum of all equipped weapons and armor plus it's natural defense.
	float power;
	float gold;

    char code;
    TCODColor color;

    char* name;
    char* nickname;
    char* fullName;		//NOTE: Name + ", " + nickname
	char* corpseName;	//NOTE: Name + " corpse"

    bool blocks;
    bool fovOnly;
    bool inSandbox;

    //NOTE: Components.
    Weapon* leftHandWeapon;

    Armor* headArmor;
    Armor* chestArmor;
    Armor* legArmor;
    Armor* leftShoulderArmor;
    Armor* rightShoulderArmor;
    Armor* leftArmArmor;
    Armor* rightArmArmor;
    Armor* leftFootArmor;
    Armor* rightFootArmor;

    //TODO: Accessorys
    //Accessory* beltAccessory;
    
    Ai* ai;
    Destructible* destructible;
    Pickable* pickable;
    Container* container;
    
	Traits* traits;

    Actor(int x, int y);
	~Actor();

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

    void
	Update();

    void
	Render();

	void
	CalculatePower();

    float
	GetDistance(int cx, int cy);
};

#endif