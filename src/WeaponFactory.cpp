#include "main.hpp"

internal_function Weapon*
CreateTemplateWeapon(float baseDamage, float defense, float maxDurability,
					 char* name, char* stockName,
					 Weapon::WEAPON_TYPE type, Weapon::WEAPON_STYLE style, Weapon::WEAPON_MATERIAL material,
					 Weapon::WEAPON_CRAFTSMANSHIP craftsmanship) {
	Weapon* result = new Weapon();

	result->baseDamage = baseDamage;
	result->defense = defense;

	result->durability = maxDurability;
	result->maxDurability = maxDurability;

	result->name = name;
	result->stockName = stockName;

	result->type = type;
	result->style = style;
	result->material = material;
	result->craftsmanship = craftsmanship;

	return(result);
}

Weapon*
CreateWeaponRandom() {
	int typeWeapon = RandomNumberInRange(1, 6);

	switch(typeWeapon) {
		case 1: 	return(CreateWeaponSword1HWood()); break;
		case 2: 	return(CreateWeaponSword1HStone()); break;
		case 3: 	return(CreateWeaponSword1HIron()); break;
		case 4: 	return(CreateWeaponShieldWood()); break;
		case 5: 	return(CreateWeaponShieldStone()); break;
		case 6: 	return(CreateWeaponShieldIron()); break;
		default:	return(CreateWeaponSword1HIron()); break;
	}
}

//1H Swords
Weapon*
CreateWeaponSword1HWood() {
	Weapon* weapon = CreateTemplateWeapon(
		WEAPON_BASE_SWORD_1H_DAMAGE, WEAPON_BASE_SWORD_1H_DEFENSE, WEAPON_DURABILITY_SWORD_1H_WOOD,
		"Wood Sword (1H)", "Wood Sword (1H)",
		Weapon::WEAPON_TYPE_SWORD_1H, Weapon::WEAPON_STYLE_MELEE_BLADE, Weapon::WEAPON_MATERIAL_WOOD,
		Weapon::WEAPON_CRAFTSMANSHIP_NORMAL);

	return(weapon);
}

Weapon*
CreateWeaponSword1HStone() {
	Weapon* weapon = CreateTemplateWeapon(
		WEAPON_BASE_SWORD_1H_DAMAGE, WEAPON_BASE_SWORD_1H_DEFENSE, WEAPON_DURABILITY_SWORD_1H_STONE,
		"Stone Sword (1H)", "Stone Sword (1H)",
		Weapon::WEAPON_TYPE_SWORD_1H, Weapon::WEAPON_STYLE_MELEE_BLADE, Weapon::WEAPON_MATERIAL_STONE,
		Weapon::WEAPON_CRAFTSMANSHIP_NORMAL);

	return(weapon);
}

Weapon*
CreateWeaponSword1HIron() {
	Weapon* weapon = CreateTemplateWeapon(
		WEAPON_BASE_SWORD_1H_DAMAGE, WEAPON_BASE_SWORD_1H_DEFENSE, WEAPON_DURABILITY_SWORD_1H_IRON,
		"Iron Sword (1H)", "Iron Sword (1H)",
		Weapon::WEAPON_TYPE_SWORD_1H, Weapon::WEAPON_STYLE_MELEE_BLADE, Weapon::WEAPON_MATERIAL_IRON,
		Weapon::WEAPON_CRAFTSMANSHIP_NORMAL);

	return(weapon);
}

//TODO: To be removed or use as cheat.
Weapon*
CreateWeaponSword1HLegendary() {
	Weapon* weapon = CreateTemplateWeapon(
		1000, 1000, 20000,
		"Legendary Sword (1H)", "Legendary Sword (1H)",
		Weapon::WEAPON_TYPE_SWORD_1H, Weapon::WEAPON_STYLE_MELEE_BLADE, Weapon::WEAPON_MATERIAL_IRON,
		Weapon::WEAPON_CRAFTSMANSHIP_LEGENDARY);

	return(weapon);
}

//Shields
Weapon*
CreateWeaponShieldWood() {
	Weapon* weapon = CreateTemplateWeapon(
		WEAPON_BASE_SHIELD_DAMAGE, WEAPON_BASE_SHIELD_DEFENSE, WEAPON_DURABILITY_SHIELD_WOOD,
		"Wood Shield", "Wood Shield",
		Weapon::WEAPON_TYPE_SHIELD, Weapon::WEAPON_STYLE_MELEE_PROTECTION, Weapon::WEAPON_MATERIAL_WOOD,
		Weapon::WEAPON_CRAFTSMANSHIP_NORMAL);

	return(weapon);
}

Weapon*
CreateWeaponShieldStone() {
	Weapon* weapon = CreateTemplateWeapon(
		WEAPON_BASE_SHIELD_DAMAGE, WEAPON_BASE_SHIELD_DEFENSE, WEAPON_DURABILITY_SHIELD_STONE,
		"Stone Shield", "Stone Shield",
		Weapon::WEAPON_TYPE_SHIELD, Weapon::WEAPON_STYLE_MELEE_PROTECTION, Weapon::WEAPON_MATERIAL_STONE,
		Weapon::WEAPON_CRAFTSMANSHIP_NORMAL);

	return(weapon);
}

Weapon*
CreateWeaponShieldIron() {
	Weapon* weapon = CreateTemplateWeapon(
		WEAPON_BASE_SHIELD_DAMAGE, WEAPON_BASE_SHIELD_DEFENSE, WEAPON_DURABILITY_SHIELD_IRON,
		"Iron Shield", "Iron Shield",
		Weapon::WEAPON_TYPE_SHIELD, Weapon::WEAPON_STYLE_MELEE_PROTECTION, Weapon::WEAPON_MATERIAL_IRON,
		Weapon::WEAPON_CRAFTSMANSHIP_NORMAL);

	return(weapon);
}