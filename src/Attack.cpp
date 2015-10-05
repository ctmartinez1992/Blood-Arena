#include "main.hpp"

void
Attack(Actor* attacker, Weapon* attackerWeapon, Actor* target, ATTACK_TARGET_PART targetPart, ATTACK_TYPE type) {
	if(target->destructible && !target->destructible->IsDead()) {
		int damage = CalculateTargetArmorDamage(attacker, attackerWeapon, target, targetPart, type);

		Armor* targetArmor = GetActorEquipmentGivenTargetPart(target, targetPart);

		int attackerWeaponNewDurability = CalculateAttackerWeaponNewDurability(attackerWeapon);
		int targetArmorDamage = CalculateTargetPartNewDurability(targetArmor, damage);

		int targetActorDamage = CalculateTargetActorDamage(target, targetArmor, damage);

		PrintAttackInLogText(attacker, attackerWeapon, target, targetArmor, targetPart, type,
							 targetArmorDamage, targetActorDamage);

		target->destructible->TakeDamage(target, targetActorDamage);
	}
	else {
		e->gui->Message(TCODColor::lightGrey, "%s tried to attack %s, but he's dead.",
							attacker->name, target->name);
	}
}

int
CalculateTargetArmorDamage(Actor* attacker, Weapon* attackerWeapon, Actor* target,
ATTACK_TARGET_PART targetPart, ATTACK_TYPE type)
{
	float attackerDamage = GetAttackValue(type, attackerWeapon) *
		attackerWeapon->CalculateWeaponFullDamage();

	float targetDefense = target->destructible->defense;
	Armor* targetArmor = GetActorEquipmentGivenTargetPart(attacker, targetPart);

	if (targetArmor) {
		targetDefense += targetArmor->CalculateArmorPieceFullDefense();
	}

	return(FastRoundf(attackerDamage - targetDefense));
}

//NOTE: The round values just maps the armor reduction percentage to 0..1 if below 50% of remaining durability.
//NOTE: 1..2 if above 50%.
int
CalculateTargetActorDamage(Actor* target, Armor* targetArmor, int damage) {
	float durDiv = targetArmor->durability / targetArmor->maxDurability;

	if (durDiv >= 0.5f && durDiv < 1) {
		float armorReductionPercentage = 1 - durDiv;
		float roundValues = armorReductionPercentage * 2;

		return(FastRoundf(damage * armorReductionPercentage));
	} else if (durDiv < 0.5f && durDiv > 0){
		float armorReductionPercentage = 2 - durDiv;
		float roundValues = armorReductionPercentage - durDiv;

		return(FastRoundf(damage * armorReductionPercentage));
	} else if (targetArmor->durability >= targetArmor->maxDurability) {
		return(0);
	} else {
		return(damage * 2);
	}
}

int
CalculateAttackerWeaponNewDurability(Weapon* attackerWeapon) {
	int lostDurability = 1;

	attackerWeapon->durability -= lostDurability;
	return(lostDurability);
}

int
CalculateTargetPartNewDurability(Armor* armor, int damage) {
	int lostDurability = 0;

	if (damage > 0) {
		lostDurability = FastRoundf(damage * 0.5f);
	} else {
		//TODO: Just a tick?
		lostDurability = 1;
	}

	armor->durability -= lostDurability;

	return(lostDurability);
}

void
PrintAttackInLogText(Actor* attacker, Weapon* attackerWeapon, Actor* target, Armor* targetArmor,
					 ATTACK_TARGET_PART targetPart, ATTACK_TYPE type,
					 int targetArmorDamage, int targetActorDamage)
{
	char* attackerName = attacker->name;
	char* attackerWeaponName = attackerWeapon->name;
	char* targetName = target->name;
	char* targetArmorName = targetArmor->name;

	char* targetPartName = GetTargetPartName(targetPart);
	char* attackTypeName = GetAttackTypeName(type, targetActorDamage, target->destructible->maxHP);

	char* damageDoneToArmorText = ToString("%d", targetArmorDamage);
	char* damageDoneToActorText = ToString("%d", targetActorDamage);

	if(targetActorDamage > 0) {
		e->gui->Message(attacker->code == e->player->code ? TCODColor::red : TCODColor::lightGrey,
							"%s %s %s's %s with his %s for %s armor damage and %s flesh damage.",
							attackerName, attackTypeName,
							targetName, targetArmorName,
							attackerWeaponName,
							damageDoneToArmorText, damageDoneToActorText);
	}
	else {
		e->gui->Message(TCODColor::lightGrey,
							"%s %s %s's %s with his %s, but it only dents the armor for %s damage.",
							attackerName, attackTypeName,
							targetName, targetArmorName,
							attackerWeaponName,
							damageDoneToArmorText);
	}

	free(attackTypeName);

	free(damageDoneToArmorText);
	free(damageDoneToActorText);
}

ATTACK_TARGET_PART
GetRandomTargetPart() {
	int chance = RandomNumberInRange(1, 10);

	switch(chance) {
		case 1:			return(ATTACK_TARGET_PART_HEAD);
		case 2:			return(ATTACK_TARGET_PART_CHEST);
		case 3:			return(ATTACK_TARGET_PART_LEG);
		case 5:			return(ATTACK_TARGET_PART_SHOULDER_LEFT);
		case 6:			return(ATTACK_TARGET_PART_SHOULDER_RIGHT);
		case 7:			return(ATTACK_TARGET_PART_ARM_LEFT);
		case 8:			return(ATTACK_TARGET_PART_ARM_RIGHT);
		case 9:			return(ATTACK_TARGET_PART_FOOT_LEFT);
		case 10:		return(ATTACK_TARGET_PART_FOOT_RIGHT);

		default:		return(ATTACK_TARGET_PART_CHEST);
	}
}

Armor*
GetActorEquipmentGivenTargetPart(Actor* owner, ATTACK_TARGET_PART targetPart) {
	switch(targetPart) {
		case ATTACK_TARGET_PART_HEAD:					return(owner->headArmor);
		case ATTACK_TARGET_PART_CHEST:					return(owner->chestArmor);
		case ATTACK_TARGET_PART_LEG:					return(owner->legArmor);
		case ATTACK_TARGET_PART_SHOULDER_LEFT:			return(owner->leftShoulderArmor);
		case ATTACK_TARGET_PART_SHOULDER_RIGHT:			return(owner->rightShoulderArmor);
		case ATTACK_TARGET_PART_ARM_LEFT:				return(owner->leftArmArmor);
		case ATTACK_TARGET_PART_ARM_RIGHT:				return(owner->rightArmArmor);
		case ATTACK_TARGET_PART_FOOT_LEFT:				return(owner->leftFootArmor);
		case ATTACK_TARGET_PART_FOOT_RIGHT:				return(owner->rightFootArmor);

		default:										return(nullptr);
	}
}
	
float
GetAttackValue(ATTACK_TYPE type, Weapon* weapon) {
	switch(type) {
		case ATTACK_TYPE_SLASH:			return(weapon->baseDamage);
		case ATTACK_TYPE_BASH:			return(weapon->defense);

		default:						return(0);
	}
}

char*
GetTargetPartName(ATTACK_TARGET_PART targetPart) {
	switch(targetPart) {
		case ATTACK_TARGET_PART_HEAD:					return("Head");
		case ATTACK_TARGET_PART_CHEST:					return("Chest");
		case ATTACK_TARGET_PART_LEG:					return("Leg");
		case ATTACK_TARGET_PART_SHOULDER_LEFT:			return("Left Shoulder");
		case ATTACK_TARGET_PART_SHOULDER_RIGHT:			return("Right Shoulder");
		case ATTACK_TARGET_PART_ARM_LEFT:				return("Left Arm");
		case ATTACK_TARGET_PART_ARM_RIGHT:				return("Right Arm");
		case ATTACK_TARGET_PART_FOOT_LEFT:				return("Left Foot");
		case ATTACK_TARGET_PART_FOOT_RIGHT:				return("Right Foot");

		default:										return("?");
	}
}

char*
GetAttackTypeName(ATTACK_TYPE type, int damage, int targetMaxHP) {
	float damagePercentage = damage / (targetMaxHP * 1.0f);

	if(damagePercentage <= 0) {
		switch(type) {
			case ATTACK_TYPE_SLASH:		return(DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "no"));
			case ATTACK_TYPE_BASH:		return("Bashs");

			default:					return("?");
		}
	}
	else if(damagePercentage > 0 && damagePercentage < 0.05) {
		switch(type) {
			case ATTACK_TYPE_SLASH:		return(DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "low"));
			case ATTACK_TYPE_BASH:		return("Bashs");

			default:					return("?");
		}
	}
	else if(damagePercentage >= 0.05 && damagePercentage < 0.125) {
		switch(type) {
			case ATTACK_TYPE_SLASH:		return(DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "mid"));
			case ATTACK_TYPE_BASH:		return("Bashs");

			default:					return("?");
		}
	}
	else if(damagePercentage >= 0.125 && damagePercentage < 0.25) {
		switch(type) {
			case ATTACK_TYPE_SLASH:		return(DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "high"));
			case ATTACK_TYPE_BASH:		return("Bashs");

			default:					return("?");
		}
	}
	else if(damagePercentage >= 0.25) {
		switch(type) {
			case ATTACK_TYPE_SLASH:
			{
				char* randomAdverb = DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "ultra");
				char* randomVerb;

				if(PercentageChance(50)) {
					randomVerb = DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "mid");
				}
				else {
					randomVerb = DODGetRandomContent(e->c->DOD_ATTACK_SLASH_SWORD, "!!damage", "high");
				}

				char* result = ToString("%s %s", randomAdverb, randomVerb);

				free(randomAdverb);
				free(randomVerb);

				return(result);
			}
			case ATTACK_TYPE_BASH:		return("Bashs");

			default:					return("?");
		}
	}
	else {
		return("?");
	}
}
