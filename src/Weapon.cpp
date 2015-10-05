#include "main.hpp"

Weapon::Weapon() :
	baseDamage(0), defense(0), durability(0), maxDurability(0),
	name(0), stockName(0),
	type(WEAPON_TYPE_UNKNOWN), style(WEAPON_STYLE_UNKNOWN), material(WEAPON_MATERIAL_UNKNOWN),
	craftsmanship(WEAPON_CRAFTSMANSHIP_UNKNOWN)
{
}

Weapon::Weapon(float baseDamage, float defense, float maxDurability,
			   char* stockName,
			   WEAPON_TYPE type, WEAPON_STYLE style, WEAPON_MATERIAL material,
			   WEAPON_CRAFTSMANSHIP craftsmanship) :
	baseDamage(baseDamage), defense(defense), durability(maxDurability), maxDurability(maxDurability),
	name(stockName), stockName(stockName),
	type(type), style(style), material(material), craftsmanship(craftsmanship)
{
}

float
Weapon::CalculateWeaponFullDamage() {
	return(GetMaterialModifierValue(type, material) * GetCraftsmanshipValue(craftsmanship));
}
	
float
Weapon::GetMaterialModifierValue(WEAPON_TYPE type, WEAPON_MATERIAL material) {
	switch(type) {
		case WEAPON_TYPE_SWORD_1H:
			switch(material) {
				case WEAPON_MATERIAL_WOOD:			return(WEAPON_MATERIAL_MODIFIER_SWORD_1H_WOOD);
				case WEAPON_MATERIAL_STONE:			return(WEAPON_MATERIAL_MODIFIER_SWORD_1H_STONE);
				case WEAPON_MATERIAL_IRON:			return(WEAPON_MATERIAL_MODIFIER_SWORD_1H_IRON);
				default:							return(0);
			}
		case WEAPON_TYPE_SHIELD:
			switch(material) {
				case WEAPON_MATERIAL_WOOD:			return(WEAPON_MATERIAL_MODIFIER_SHIELD_WOOD);
				case WEAPON_MATERIAL_STONE:			return(WEAPON_MATERIAL_MODIFIER_SHIELD_STONE);
				case WEAPON_MATERIAL_IRON:			return(WEAPON_MATERIAL_MODIFIER_SHIELD_IRON);
				default:							return(0);
			}

		default:									return(0);
	}
}
	
float
Weapon::GetCraftsmanshipValue(WEAPON_CRAFTSMANSHIP craftsmanship) {
	switch(craftsmanship) {
		case WEAPON_CRAFTSMANSHIP_HORRIBLE:			return(WEAPON_CRAFTSMANSHIP_MODIFIER_HORRIBLE);
		case WEAPON_CRAFTSMANSHIP_WEAK:				return(WEAPON_CRAFTSMANSHIP_MODIFIER_WEAK);
		case WEAPON_CRAFTSMANSHIP_POOR:				return(WEAPON_CRAFTSMANSHIP_MODIFIER_POOR);
		case WEAPON_CRAFTSMANSHIP_NORMAL:			return(WEAPON_CRAFTSMANSHIP_MODIFIER_NORMAL);
		case WEAPON_CRAFTSMANSHIP_GOOD:				return(WEAPON_CRAFTSMANSHIP_MODIFIER_GOOD);
		case WEAPON_CRAFTSMANSHIP_FINE:				return(WEAPON_CRAFTSMANSHIP_MODIFIER_FINE);
		case WEAPON_CRAFTSMANSHIP_SUPERIOR:			return(WEAPON_CRAFTSMANSHIP_MODIFIER_SUPERIOR);
		case WEAPON_CRAFTSMANSHIP_EXCEPTIONAL:		return(WEAPON_CRAFTSMANSHIP_MODIFIER_EXCEPTIONAL);
		case WEAPON_CRAFTSMANSHIP_MASTERFUL:		return(WEAPON_CRAFTSMANSHIP_MODIFIER_MASTERFUL);
		case WEAPON_CRAFTSMANSHIP_LEGENDARY:		return(WEAPON_CRAFTSMANSHIP_MODIFIER_LEGENDARY);

		default:									return(0);
	}
}