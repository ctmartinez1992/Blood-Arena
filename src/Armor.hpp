#ifndef RL_ARMOR_HPP
#define RL_ARMOR_HPP

//TODO: Add hand stuff, gloves and mittens.
//TODO: Research for more armor
/******************** Armor base armor values ********************/
//////////////////////////////HEAD
global_variable float ARMOR_BASE_HEAD_CAP = 			30;
global_variable float ARMOR_BASE_HEAD_HELMET = 			70;
//////////////////////////////CHEST
global_variable float ARMOR_BASE_CHEST_VEST = 			60;
global_variable float ARMOR_BASE_CHEST_BREASTPLATE = 	130;
//////////////////////////////LEG
global_variable float ARMOR_BASE_LEG_PANTS = 			50;
global_variable float ARMOR_BASE_LEG_GREAVES = 			80;
//////////////////////////////SHOULDER
global_variable float ARMOR_BASE_SHOULDER_PAULDRON = 	50;
//////////////////////////////ARM
global_variable float ARMOR_BASE_ARM_BRACER = 			30;
global_variable float ARMOR_BASE_ARM_GAUNTLET = 		50;
//////////////////////////////FOOT
global_variable float ARMOR_BASE_FOOT_SHOE = 			20;
global_variable float ARMOR_BASE_FOOT_BOOT = 			40;
/*************************************************************************/

/******************** Armor material values ********************/
//////////////////////////////HEAD - CAP
global_variable float ARMOR_MATERIAL_MODIFIER_HEAD_CAP_CLOTH = 					0.75f;
global_variable float ARMOR_MATERIAL_MODIFIER_HEAD_CAP_LEATHER = 				1.25f;
global_variable float ARMOR_MATERIAL_MODIFIER_HEAD_CAP_IRON = 					1.75f;
//////////////////////////////HEAD - HELMET
global_variable float ARMOR_MATERIAL_MODIFIER_HEAD_HELMET_CLOTH = 				0.8f;
global_variable float ARMOR_MATERIAL_MODIFIER_HEAD_HELMET_LEATHER = 			1.4f;
global_variable float ARMOR_MATERIAL_MODIFIER_HEAD_HELMET_IRON = 				1.9f;
//////////////////////////////CHEST - VEST
global_variable float ARMOR_MATERIAL_MODIFIER_CHEST_VEST_CLOTH = 				0.75f;
global_variable float ARMOR_MATERIAL_MODIFIER_CHEST_VEST_LEATHER = 				1.15f;
global_variable float ARMOR_MATERIAL_MODIFIER_CHEST_VEST_IRON = 				1.55f;
//////////////////////////////CHEST - BREASTPLATE
global_variable float ARMOR_MATERIAL_MODIFIER_CHEST_BREASTPLATE_CLOTH = 		0.9f;
global_variable float ARMOR_MATERIAL_MODIFIER_CHEST_BREASTPLATE_LEATHER = 		1.7f;
global_variable float ARMOR_MATERIAL_MODIFIER_CHEST_BREASTPLATE_IRON = 			2.2f;
//////////////////////////////LEG - PANTS
global_variable float ARMOR_MATERIAL_MODIFIER_LEG_PANTS_CLOTH = 				0.7f;
global_variable float ARMOR_MATERIAL_MODIFIER_LEG_PANTS_LEATHER = 				1.1f;
global_variable float ARMOR_MATERIAL_MODIFIER_LEG_PANTS_IRON = 					1.5f;
//////////////////////////////LEG - GREAVES
global_variable float ARMOR_MATERIAL_MODIFIER_LEG_GREAVES_CLOTH = 				0.8f;
global_variable float ARMOR_MATERIAL_MODIFIER_LEG_GREAVES_LEATHER = 			1.6f;
global_variable float ARMOR_MATERIAL_MODIFIER_LEG_GREAVES_IRON = 				2.1f;
//////////////////////////////SHOULDER - PAULDRON
global_variable float ARMOR_MATERIAL_MODIFIER_SHOULDER_PAULDRON_CLOTH = 		0.6f;
global_variable float ARMOR_MATERIAL_MODIFIER_SHOULDER_PAULDRON_LEATHER = 		1.1f;
global_variable float ARMOR_MATERIAL_MODIFIER_SHOULDER_PAULDRON_IRON = 			1.65f;
//////////////////////////////ARM - BRACER
global_variable float ARMOR_MATERIAL_MODIFIER_ARM_BRACER_CLOTH =	 			0.5f;
global_variable float ARMOR_MATERIAL_MODIFIER_ARM_BRACER_LEATHER = 				0.95f;
global_variable float ARMOR_MATERIAL_MODIFIER_ARM_BRACER_IRON = 				1.3f;
//////////////////////////////ARM - GAUNTLET
global_variable float ARMOR_MATERIAL_MODIFIER_ARM_GAUNTLET_CLOTH = 				0.55f;
global_variable float ARMOR_MATERIAL_MODIFIER_ARM_GAUNTLET_LEATHER = 			1;
global_variable float ARMOR_MATERIAL_MODIFIER_ARM_GAUNTLET_IRON = 				1.35f;
//////////////////////////////FOOT - SHOE
global_variable float ARMOR_MATERIAL_MODIFIER_FOOT_SHOE_CLOTH = 				0.4f;
global_variable float ARMOR_MATERIAL_MODIFIER_FOOT_SHOE_LEATHER = 				0.8f;
global_variable float ARMOR_MATERIAL_MODIFIER_FOOT_SHOE_IRON = 					1.3f;
//////////////////////////////FOOT - BOOT
global_variable float ARMOR_MATERIAL_MODIFIER_FOOT_BOOT_CLOTH = 				0.5f;
global_variable float ARMOR_MATERIAL_MODIFIER_FOOT_BOOT_LEATHER = 				0.9f;
global_variable float ARMOR_MATERIAL_MODIFIER_FOOT_BOOT_IRON = 					1.4f;
/******************************************************************/

/******************** Armor durability values ********************/
//////////////////////////////HEAD
global_variable float ARMOR_DURABILITY_HEAD_CLOTH = 		500;
global_variable float ARMOR_DURABILITY_HEAD_LEATHER = 		1500;
global_variable float ARMOR_DURABILITY_HEAD_IRON = 			2500;
//////////////////////////////CHEST
global_variable float ARMOR_DURABILITY_CHEST_CLOTH = 		750;
global_variable float ARMOR_DURABILITY_CHEST_LEATHER = 		2000;
global_variable float ARMOR_DURABILITY_CHEST_IRON = 		3750;
//////////////////////////////LEG
global_variable float ARMOR_DURABILITY_LEG_CLOTH = 			750;
global_variable float ARMOR_DURABILITY_LEG_LEATHER = 		1750;
global_variable float ARMOR_DURABILITY_LEG_IRON = 			3500;
//////////////////////////////SHOULDER
global_variable float ARMOR_DURABILITY_SHOULDER_CLOTH = 	500;
global_variable float ARMOR_DURABILITY_SHOULDER_LEATHER = 	1500;
global_variable float ARMOR_DURABILITY_SHOULDER_IRON = 		2500;
//////////////////////////////ARM
global_variable float ARMOR_DURABILITY_ARM_CLOTH = 			500;
global_variable float ARMOR_DURABILITY_ARM_LEATHER = 		1250;
global_variable float ARMOR_DURABILITY_ARM_IRON = 			2250;
//////////////////////////////FOOT
global_variable float ARMOR_DURABILITY_FOOT_CLOTH = 		500;
global_variable float ARMOR_DURABILITY_FOOT_LEATHER = 		1000;
global_variable float ARMOR_DURABILITY_FOOT_IRON = 			2750;
/*************************************************************************/

/******************** Armor craftsmanship values ********************/
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_HORRIBLE = 		0.65f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_WEAK = 			0.8f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_POOR = 			0.9f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_NORMAL = 		1;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_GOOD = 			1.2f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_FINE = 			1.3f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_SUPERIOR = 		1.4f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_EXCEPTIONAL = 	1.6f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_MASTERFUL = 		1.8f;
global_variable float ARMOR_CRAFTSMANSHIP_MODIFIER_LEGENDARY = 		2;
/*************************************************************************/

//TODO: What about rings, amulets and stuff like that.
class Armor {
public:
	enum ARMOR_TYPE {
		ARMOR_TYPE_UNKNOWN,
		// Head
		ARMOR_TYPE_HEAD_CAP,
		ARMOR_TYPE_HEAD_HELMET,
		// Chest
		ARMOR_TYPE_CHEST_VEST,
		ARMOR_TYPE_CHEST_BREASTPLATE,
		// Legs
		ARMOR_TYPE_LEG_PANTS,
		ARMOR_TYPE_LEG_GREAVES,
		// Shoulder
		ARMOR_TYPE_SHOULDER_PAULDRON,
		// Arm
		ARMOR_TYPE_ARM_BRACER,
		ARMOR_TYPE_ARM_GAUNTLET,
		// Boot
		ARMOR_TYPE_FOOT_SHOE,
		ARMOR_TYPE_FOOT_BOOT,
		ARMOR_TYPE_SIZE
	};

	enum ARMOR_MATERIAL {
		ARMOR_MATERIAL_UNKNOWN,
		ARMOR_MATERIAL_CLOTH,
		ARMOR_MATERIAL_LEATHER,
		ARMOR_MATERIAL_IRON,
		ARMOR_MATERIAL_SIZE
	};

	enum ARMOR_CRAFTSMANSHIP {
		ARMOR_CRAFTSMANSHIP_UNKNOWN,
		ARMOR_CRAFTSMANSHIP_HORRIBLE,
		ARMOR_CRAFTSMANSHIP_WEAK,
		ARMOR_CRAFTSMANSHIP_POOR,
		ARMOR_CRAFTSMANSHIP_NORMAL,
		ARMOR_CRAFTSMANSHIP_GOOD,
		ARMOR_CRAFTSMANSHIP_FINE,
		ARMOR_CRAFTSMANSHIP_SUPERIOR,
		ARMOR_CRAFTSMANSHIP_EXCEPTIONAL,
		ARMOR_CRAFTSMANSHIP_MASTERFUL,
		ARMOR_CRAFTSMANSHIP_LEGENDARY
	};

	float baseArmor;

	float durability;
	float maxDurability;

	char* name;
	char* stockName;

	ARMOR_TYPE type;
	ARMOR_MATERIAL material;
	ARMOR_CRAFTSMANSHIP craftsmanship;

	Armor();
	Armor(float baseArmor, float maxDurability, char* stockName,
		  ARMOR_TYPE type, ARMOR_MATERIAL material, ARMOR_CRAFTSMANSHIP craftsmanship);

	float
	CalculateArmorPieceFullDefense();

	float
	GetMaterialModifierValue(ARMOR_TYPE type, ARMOR_MATERIAL material);

	float
	GetCraftsmanshipValue(ARMOR_CRAFTSMANSHIP craftsmanship);
};

#endif