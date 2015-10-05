#include "main.hpp"

internal_function Armor*
CreateTemplateArmor(float baseArmor, float maxDurability, char* name, char* stockName,
					Armor::ARMOR_TYPE type, Armor::ARMOR_MATERIAL material, Armor::ARMOR_CRAFTSMANSHIP craftsmanship)
{
	Armor* result = new Armor();

	result->baseArmor = baseArmor;

	result->durability = maxDurability;
	result->maxDurability = maxDurability;

	result->name = name;
	result->stockName = stockName;

	result->type = type;
	result->material = material;
	result->craftsmanship = craftsmanship;

	return(result);
}

//Head Armor
Armor*
CreateArmorHeadRandom() {
	int armorType = RandomNumberInRange(1, 3);

	switch(armorType) {
		case 1: 	return(CreateArmorHeadCapCloth()); break;
		case 2: 	return(CreateArmorHeadCapLeather()); break;
		case 3: 	return(CreateArmorHeadHelmetIron()); break;
		default: 	return(CreateArmorHeadCapCloth()); break;
	}
}

Armor*
CreateArmorHeadCapCloth() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_HEAD_CAP, ARMOR_DURABILITY_HEAD_CLOTH, "Cloth Cap", "Cloth Cap",
		Armor::ARMOR_TYPE_HEAD_CAP, Armor::ARMOR_MATERIAL_CLOTH, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorHeadCapLeather() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_HEAD_CAP, ARMOR_DURABILITY_HEAD_LEATHER, "Leather Cap", "Leather Cap",
		Armor::ARMOR_TYPE_HEAD_CAP, Armor::ARMOR_MATERIAL_LEATHER, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorHeadHelmetIron() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_HEAD_HELMET, ARMOR_DURABILITY_HEAD_IRON, "Iron Helmet", "Iron Helmet",
		Armor::ARMOR_TYPE_HEAD_HELMET, Armor::ARMOR_MATERIAL_IRON, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

//Chest Armor
Armor*
CreateArmorChestRandom() {
	int armorType = RandomNumberInRange(1, 3);

	switch(armorType) {
		case 1: 	return(CreateArmorChestVestCloth()); break;
		case 2: 	return(CreateArmorChestVestLeather()); break;
		case 3: 	return(CreateArmorChestBreastplateIron()); break;
		default: 	return(CreateArmorChestVestCloth()); break;
	}
}

Armor*
CreateArmorChestVestCloth() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_CHEST_VEST, ARMOR_DURABILITY_CHEST_CLOTH, "Cloth Vest", "Cloth Vest",
		Armor::ARMOR_TYPE_CHEST_VEST, Armor::ARMOR_MATERIAL_CLOTH, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorChestVestLeather() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_CHEST_VEST, ARMOR_DURABILITY_CHEST_LEATHER, "Leather Vest", "Leather Vest",
		Armor::ARMOR_TYPE_CHEST_VEST, Armor::ARMOR_MATERIAL_LEATHER, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorChestBreastplateIron() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_CHEST_BREASTPLATE, ARMOR_DURABILITY_CHEST_IRON, "Iron Breastplate", "Iron Breastplate",
		Armor::ARMOR_TYPE_CHEST_BREASTPLATE, Armor::ARMOR_MATERIAL_IRON, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

//Leg Armor
Armor*
CreateArmorLegRandom() {
	int armorType = RandomNumberInRange(1, 3);

	switch(armorType) {
		case 1: 	return(CreateArmorLegPantsCloth()); break;
		case 2: 	return(CreateArmorLegPantsLeather()); break;
		case 3: 	return(CreateArmorLegGreavesIron()); break;
		default: 	return(CreateArmorLegPantsCloth()); break;
	}
}

Armor*
CreateArmorLegPantsCloth() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_LEG_PANTS, ARMOR_DURABILITY_LEG_CLOTH, "Cloth Pants", "Cloth Pants",
		Armor::ARMOR_TYPE_LEG_PANTS, Armor::ARMOR_MATERIAL_CLOTH, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorLegPantsLeather() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_LEG_PANTS, ARMOR_DURABILITY_LEG_LEATHER, "Leather Pants", "Leather Pants",
		Armor::ARMOR_TYPE_LEG_PANTS, Armor::ARMOR_MATERIAL_LEATHER, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorLegGreavesIron() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_LEG_GREAVES, ARMOR_DURABILITY_LEG_IRON, "Iron Greaves", "Iron Greaves",
		Armor::ARMOR_TYPE_LEG_GREAVES, Armor::ARMOR_MATERIAL_IRON, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

//Shoulder Armor
Armor*
CreateArmorShoulderRandom() {
	int armorType = RandomNumberInRange(1, 3);

	switch(armorType) {
		case 1: 	return(CreateArmorShoulderPauldronCloth()); break;
		case 2: 	return(CreateArmorShoulderPauldronLeather()); break;
		case 3: 	return(CreateArmorShoulderPauldronIron()); break;
		default: 	return(CreateArmorShoulderPauldronCloth()); break;
	}
}

Armor*
CreateArmorShoulderPauldronCloth() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_SHOULDER_PAULDRON, ARMOR_DURABILITY_SHOULDER_CLOTH, "Cloth Pauldron", "Cloth Pauldron",
		Armor::ARMOR_TYPE_SHOULDER_PAULDRON, Armor::ARMOR_MATERIAL_CLOTH, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorShoulderPauldronLeather() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_SHOULDER_PAULDRON, ARMOR_DURABILITY_SHOULDER_LEATHER, "Leather Pauldron", "Leather Pauldron",
		Armor::ARMOR_TYPE_SHOULDER_PAULDRON, Armor::ARMOR_MATERIAL_LEATHER, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorShoulderPauldronIron() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_SHOULDER_PAULDRON, ARMOR_DURABILITY_SHOULDER_IRON, "Iron Pauldron", "Iron Pauldron",
		Armor::ARMOR_TYPE_SHOULDER_PAULDRON, Armor::ARMOR_MATERIAL_IRON, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

//Arm Armor
Armor*
CreateArmorArmRandom() {
	int armorType = RandomNumberInRange(1, 3);

	switch(armorType) {
		case 1: 	return(CreateArmorArmBracerCloth()); break;
		case 2: 	return(CreateArmorArmBracerLeather()); break;
		case 3: 	return(CreateArmorArmGauntletIron()); break;
		default: 	return(CreateArmorArmBracerCloth()); break;
	}
}

Armor*
CreateArmorArmBracerCloth() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_ARM_BRACER, ARMOR_DURABILITY_ARM_CLOTH, "Cloth Bracer", "Cloth Bracer",
		Armor::ARMOR_TYPE_ARM_BRACER, Armor::ARMOR_MATERIAL_CLOTH, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorArmBracerLeather() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_ARM_BRACER, ARMOR_DURABILITY_ARM_LEATHER, "Leather Bracer", "Leather Bracer",
		Armor::ARMOR_TYPE_ARM_BRACER, Armor::ARMOR_MATERIAL_LEATHER, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorArmGauntletIron() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_ARM_GAUNTLET, ARMOR_DURABILITY_ARM_IRON, "Iron Gauntlet", "Iron Gauntlet",
		Armor::ARMOR_TYPE_ARM_GAUNTLET, Armor::ARMOR_MATERIAL_IRON, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

//Foot Armor
Armor*
CreateArmorFootRandom() {
	int armorType = RandomNumberInRange(1, 3);

	switch(armorType) {
		case 1: 	return(CreateArmorFootShoeCloth()); break;
		case 2: 	return(CreateArmorFootShoeLeather()); break;
		case 3: 	return(CreateArmorFootBootIron()); break;
		default: 	return(CreateArmorFootShoeCloth()); break;
	}
}

Armor*
CreateArmorFootShoeCloth() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_FOOT_SHOE, ARMOR_DURABILITY_FOOT_CLOTH, "Cloth Shoe", "Cloth Shoe",
		Armor::ARMOR_TYPE_FOOT_SHOE, Armor::ARMOR_MATERIAL_CLOTH, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorFootShoeLeather() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_FOOT_SHOE, ARMOR_DURABILITY_FOOT_LEATHER, "Leather Shoe", "Leather Shoe",
		Armor::ARMOR_TYPE_FOOT_SHOE, Armor::ARMOR_MATERIAL_LEATHER, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}

Armor*
CreateArmorFootBootIron() {
	Armor* armor = CreateTemplateArmor(
		ARMOR_BASE_FOOT_BOOT, ARMOR_DURABILITY_FOOT_IRON, "Iron Boot", "Iron Boot",
		Armor::ARMOR_TYPE_FOOT_BOOT, Armor::ARMOR_MATERIAL_IRON, Armor::ARMOR_CRAFTSMANSHIP_NORMAL);

	return(armor);
}