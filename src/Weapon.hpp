#ifndef RL_WEAPON_HPP
#define RL_WEAPON_HPP

/******************** Weapon base values ********************/
//////////////////////////////SWORD 1H
global_variable float WEAPON_BASE_SWORD_1H_DAMAGE = 	150;
global_variable float WEAPON_BASE_SWORD_1H_DEFENSE = 	20;
//////////////////////////////SHIELD
global_variable float WEAPON_BASE_SHIELD_DAMAGE = 	20;
global_variable float WEAPON_BASE_SHIELD_DEFENSE = 	120;
/******************************************************************/

/******************** Weapon material values ********************/
//////////////////////////////SWORD 1H
global_variable float WEAPON_MATERIAL_MODIFIER_SWORD_1H_WOOD = 	1;
global_variable float WEAPON_MATERIAL_MODIFIER_SWORD_1H_STONE = 1.5f;
global_variable float WEAPON_MATERIAL_MODIFIER_SWORD_1H_IRON = 	2.5f;
//////////////////////////////SHIELD
global_variable float WEAPON_MATERIAL_MODIFIER_SHIELD_WOOD = 	0.75f;
global_variable float WEAPON_MATERIAL_MODIFIER_SHIELD_STONE = 	1.25f;
global_variable float WEAPON_MATERIAL_MODIFIER_SHIELD_IRON = 	1.75f;
/******************************************************************/

/******************** Weapon durability values ********************/
//////////////////////////////SWORD 1H
global_variable float WEAPON_DURABILITY_SWORD_1H_WOOD = 	1000;
global_variable float WEAPON_DURABILITY_SWORD_1H_STONE = 	1500;
global_variable float WEAPON_DURABILITY_SWORD_1H_IRON = 	2500;
//////////////////////////////SHIELD
global_variable float WEAPON_DURABILITY_SHIELD_WOOD = 		1000;
global_variable float WEAPON_DURABILITY_SHIELD_STONE = 		6000;
global_variable float WEAPON_DURABILITY_SHIELD_IRON = 		4000;
/*************************************************************************/

/******************** Weapon craftsmanship values ********************/
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_HORRIBLE = 		0.5f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_WEAK = 			0.7f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_POOR = 			0.85f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_NORMAL = 		1;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_GOOD = 			1.15f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_FINE = 			1.25f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_SUPERIOR = 		1.35f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_EXCEPTIONAL = 	1.5f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_MASTERFUL = 	1.75f;
global_variable float WEAPON_CRAFTSMANSHIP_MODIFIER_LEGENDARY = 	2;
/*************************************************************************/

class Weapon {
public:
	enum WEAPON_TYPE {
		WEAPON_TYPE_UNKNOWN,
		WEAPON_TYPE_SWORD_1H,
		WEAPON_TYPE_SWORD_2H,
		WEAPON_TYPE_SHIELD
	};

	enum WEAPON_STYLE {
		WEAPON_STYLE_UNKNOWN,
		WEAPON_STYLE_MELEE_BLADE,
		WEAPON_STYLE_MELEE_BLUNT,
		WEAPON_STYLE_MELEE_PROTECTION
	};

	enum WEAPON_MATERIAL {
		WEAPON_MATERIAL_UNKNOWN,
		WEAPON_MATERIAL_WOOD,
		WEAPON_MATERIAL_STONE,
		WEAPON_MATERIAL_IRON
	};

	enum WEAPON_CRAFTSMANSHIP {
		WEAPON_CRAFTSMANSHIP_UNKNOWN,
		WEAPON_CRAFTSMANSHIP_HORRIBLE,
		WEAPON_CRAFTSMANSHIP_WEAK,
		WEAPON_CRAFTSMANSHIP_POOR,
		WEAPON_CRAFTSMANSHIP_NORMAL,
		WEAPON_CRAFTSMANSHIP_GOOD,
		WEAPON_CRAFTSMANSHIP_FINE,
		WEAPON_CRAFTSMANSHIP_SUPERIOR,
		WEAPON_CRAFTSMANSHIP_EXCEPTIONAL,
		WEAPON_CRAFTSMANSHIP_MASTERFUL,
		WEAPON_CRAFTSMANSHIP_LEGENDARY
	};

	float baseDamage;
	float defense;

	float durability;
	float maxDurability;

	char* name;
	char* stockName;

	WEAPON_TYPE type;
	WEAPON_STYLE style;
	WEAPON_MATERIAL material;
	WEAPON_CRAFTSMANSHIP craftsmanship;

	Weapon();
	Weapon(float baseDamage, float defense, float maxDurability,
		   char* stockName,
		   WEAPON_TYPE type, WEAPON_STYLE style, WEAPON_MATERIAL material,
		   WEAPON_CRAFTSMANSHIP craftsmanship);

	float
	CalculateWeaponFullDamage();

	float
	GetMaterialModifierValue(WEAPON_TYPE type, WEAPON_MATERIAL material);

	float
	GetCraftsmanshipValue(WEAPON_CRAFTSMANSHIP craftsmanship);
};

#endif