#ifndef RL_ATTACK_HPP
#define RL_ATTACK_HPP

//TODO: We can go really deep by having this enum and then having another called something target_part_detailed
//and having eyes be targetable and receive the head armor, same thing for teeth, fingers, etc.
enum ATTACK_TARGET_PART {
	ATTACK_TARGET_PART_UNKNOWN,
	ATTACK_TARGET_PART_HEAD,
	ATTACK_TARGET_PART_CHEST,
	ATTACK_TARGET_PART_LEG,
	ATTACK_TARGET_PART_SHOULDER_LEFT,
	ATTACK_TARGET_PART_SHOULDER_RIGHT,
	ATTACK_TARGET_PART_ARM_LEFT,
	ATTACK_TARGET_PART_ARM_RIGHT,
	ATTACK_TARGET_PART_FOOT_LEFT,
	ATTACK_TARGET_PART_FOOT_RIGHT
};

enum ATTACK_TYPE {
	ATTACK_TYPE_UNKNOWN,
	ATTACK_TYPE_SLASH,
	ATTACK_TYPE_BASH
};

//TODO: Implement parrying.
//TODO: Shield blocking.
void
Attack(Actor* attacker, Weapon* attackerWeapon, Actor* target, ATTACK_TARGET_PART targetPart, ATTACK_TYPE type);

int
CalculateTargetArmorDamage(Actor* attacker, Weapon* attackerWeapon, Actor* target,
ATTACK_TARGET_PART targetPart, ATTACK_TYPE type);

int
CalculateTargetActorDamage(Actor* target, Armor* targetArmor, int damage);

//NOTE: Returns the amount of durability lost.
int
CalculateAttackerWeaponNewDurability(Weapon* attackerWeapon);

//NOTE: Returns the amount of durability lost.
int
CalculateTargetPartNewDurability(Armor* armor, int damage);

void
PrintAttackInLogText(Actor* attacker, Weapon* attackerWeapon, Actor* target, Armor* targetArmor,
					 ATTACK_TARGET_PART targetPart, ATTACK_TYPE type,
					 int targetArmorDamage, int targetActorDamage);


ATTACK_TARGET_PART
GetRandomTargetPart();

Armor*
GetActorEquipmentGivenTargetPart(Actor* owner, ATTACK_TARGET_PART targetPart);
	
float
GetAttackValue(ATTACK_TYPE type, Weapon* weapon);

char*
GetTargetPartName(ATTACK_TARGET_PART targetPart);

char*
GetAttackTypeName(ATTACK_TYPE type, int damage, int targetMaxHP);

#endif