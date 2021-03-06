#include "main.hpp"

Armor::Armor() :
	baseArmor(0), durability(0), maxDurability(0), name(0), stockName(0),
	type(ARMOR_TYPE_UNKNOWN), material(ARMOR_MATERIAL_UNKNOWN),
	craftsmanship(ARMOR_CRAFTSMANSHIP_UNKNOWN)
{
}

Armor::Armor(float baseArmor, float maxDurability, char* stockName,
			 ARMOR_TYPE type, ARMOR_MATERIAL material, ARMOR_CRAFTSMANSHIP craftsmanship) :
	baseArmor(baseArmor), durability(maxDurability), maxDurability(maxDurability),
	name(stockName), stockName(stockName),
	type(type), material(material), craftsmanship(craftsmanship)
{
}

float
Armor::CalculateArmorPieceFullDefense() {
	return(baseArmor * GetMaterialModifierValue(type, material));
}
	
float
Armor::GetMaterialModifierValue(ARMOR_TYPE type, ARMOR_MATERIAL material) {
	switch(type) {
		case ARMOR_TYPE_HEAD_CAP:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_HEAD_CAP_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_HEAD_CAP_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_HEAD_CAP_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_HEAD_HELMET:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_HEAD_HELMET_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_HEAD_HELMET_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_HEAD_HELMET_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_CHEST_VEST:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_CHEST_VEST_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_CHEST_VEST_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_CHEST_VEST_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_CHEST_BREASTPLATE:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_CHEST_BREASTPLATE_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_CHEST_BREASTPLATE_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_CHEST_BREASTPLATE_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_LEG_PANTS:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_LEG_PANTS_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_LEG_PANTS_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_LEG_PANTS_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_LEG_GREAVES:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_LEG_GREAVES_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_LEG_GREAVES_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_LEG_GREAVES_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_SHOULDER_PAULDRON:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_SHOULDER_PAULDRON_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_SHOULDER_PAULDRON_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_SHOULDER_PAULDRON_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_ARM_BRACER:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_ARM_BRACER_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_ARM_BRACER_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_ARM_BRACER_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_ARM_GAUNTLET:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_ARM_GAUNTLET_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_ARM_GAUNTLET_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_ARM_GAUNTLET_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_FOOT_SHOE:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_FOOT_SHOE_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_FOOT_SHOE_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_FOOT_SHOE_IRON);
				default:							return(0);
			}
		case ARMOR_TYPE_FOOT_BOOT:
			switch(material) {
				case ARMOR_MATERIAL_CLOTH:			return(ARMOR_MATERIAL_MODIFIER_FOOT_BOOT_CLOTH);
				case ARMOR_MATERIAL_LEATHER:		return(ARMOR_MATERIAL_MODIFIER_FOOT_BOOT_LEATHER);
				case ARMOR_MATERIAL_IRON:			return(ARMOR_MATERIAL_MODIFIER_FOOT_BOOT_IRON);
				default:							return(0);
			}

		default:									return(0);
	}
}
	
float
Armor::GetCraftsmanshipValue(ARMOR_CRAFTSMANSHIP craftsmanship) {
	switch(craftsmanship) {
		case ARMOR_CRAFTSMANSHIP_HORRIBLE:			return(ARMOR_CRAFTSMANSHIP_MODIFIER_HORRIBLE);
		case ARMOR_CRAFTSMANSHIP_WEAK:				return(ARMOR_CRAFTSMANSHIP_MODIFIER_WEAK);
		case ARMOR_CRAFTSMANSHIP_POOR:				return(ARMOR_CRAFTSMANSHIP_MODIFIER_POOR);
		case ARMOR_CRAFTSMANSHIP_NORMAL:			return(ARMOR_CRAFTSMANSHIP_MODIFIER_NORMAL);
		case ARMOR_CRAFTSMANSHIP_GOOD:				return(ARMOR_CRAFTSMANSHIP_MODIFIER_GOOD);
		case ARMOR_CRAFTSMANSHIP_FINE:				return(ARMOR_CRAFTSMANSHIP_MODIFIER_FINE);
		case ARMOR_CRAFTSMANSHIP_SUPERIOR:			return(ARMOR_CRAFTSMANSHIP_MODIFIER_SUPERIOR);
		case ARMOR_CRAFTSMANSHIP_EXCEPTIONAL:		return(ARMOR_CRAFTSMANSHIP_MODIFIER_EXCEPTIONAL);
		case ARMOR_CRAFTSMANSHIP_MASTERFUL:			return(ARMOR_CRAFTSMANSHIP_MODIFIER_MASTERFUL);
		case ARMOR_CRAFTSMANSHIP_LEGENDARY:			return(ARMOR_CRAFTSMANSHIP_MODIFIER_LEGENDARY);

		default:									return(0);
	}
}