#include "main.hpp"

internal_function char*
GenerateCorpseName(char* name) {
	char* result = ToString("%s Corpse", name);

	return(result);
}

internal_function char*
GenerateNickname() {
	char* tmpNick = nicknames[(RandomNumberInRange(0, 82))];
	int nickSize = CharPointerLength(tmpNick);

	char* result = (char*)calloc(nickSize, sizeof(char));

	MemoryCopy(result, tmpNick, nickSize);

	return(result);
}

internal_function char*
GenerateFullName(char* name, char* nickname) {
	char* fullName = ToString("%s, %s", name, nickname);

	return(fullName);
}

internal_function char*
GenerateOrcName() {
	char* name = (char*)calloc(11, sizeof(char));

	ConcatenateCharPointers(name, namePrefix[(RandomNumberInRange(0, 79))]);
	ConcatenateCharPointers(name, nameSuffix[(RandomNumberInRange(0, 79))]);

	name[0] = CharToUpperCase(name[0]);

	return(name);
}

//NOTE: I'm assuming that the passed name and nickname are allocated outside of this function.
internal_function Actor*
CreateTemplateActor(int x, int y,
					char code, TCODColor color,
					char* name, char* nickname,
					Weapon* leftHandWeapon = nullptr,
					Armor* headArmor = nullptr, Armor* chestArmor = nullptr, Armor* legArmor = nullptr,
					Armor* leftShoulderArmor = nullptr, Armor* rightShoulderArmor = nullptr,
					Armor* leftArmArmor = nullptr, Armor* rightArmArmor = nullptr,
					Armor* leftFootArmor = nullptr, Armor* rightFootArmor = nullptr,
					Ai* ai = nullptr, Destructible* destructible = nullptr,
					Pickable* pickable = nullptr, Container* container = nullptr,
					bool blocks = true, bool fovOnly = true,
					bool calculatePower = false)
{
	Actor* result = new Actor(x, y);

	result->code = code;
	result->color = color;

	result->name = name;
	result->nickname = nickname;
	result->fullName = GenerateFullName(result->name, result->nickname);
	result->corpseName = GenerateCorpseName(result->name);

	result->leftHandWeapon = leftHandWeapon;
	result->headArmor = headArmor;
	result->chestArmor = chestArmor;
	result->legArmor = legArmor;
	result->leftFootArmor = leftFootArmor;
	result->rightFootArmor = rightFootArmor;
	result->leftShoulderArmor = leftShoulderArmor;
	result->rightShoulderArmor = rightShoulderArmor;
	result->leftArmArmor = leftArmArmor;
	result->rightArmArmor = rightArmArmor;

	result->ai = ai;
	result->destructible = destructible;
	result->pickable = pickable;
	result->container = container;

	//TODO: For now.
	result->traits = new Traits();

	result->blocks = blocks;
	result->fovOnly = fovOnly;

	if(calculatePower) {
		result->CalculatePower();
	}

	return(result);
}

Actor*
CreateActorPlayer() {
	char* name = (char*)calloc(7, sizeof(char));
	MemoryCopy(name, "Carlos", 7);
	char* nickname = (char*)calloc(11, sizeof(char));
	MemoryCopy(nickname, "The Legend", 11);

	Actor* actor = CreateTemplateActor(
		0, 0,
		'@', TCODColor::white,
		name, nickname,
		CreateWeaponSword1HIron(),
		CreateArmorHeadHelmetIron(), CreateArmorChestBreastplateIron(), CreateArmorLegGreavesIron(),
		CreateArmorShoulderPauldronIron(), CreateArmorShoulderPauldronIron(),
		CreateArmorArmGauntletIron(), CreateArmorArmGauntletIron(),
		CreateArmorFootBootIron(), CreateArmorFootBootIron(),
		new PlayerAi(),
		new OrcDestructible(175, 5),
		nullptr,
		new Container(26),
		true, true, true);

	delete actor->traits;
	actor->traits = nullptr;

	return(actor);
}

Actor*
CreateActorFullRandomOrc() {
	Actor* actor = CreateTemplateActor(
		0, 0,
		ORC_THUG_CODE, ORC_THUG_COLOR,
		GenerateOrcName(), GenerateNickname(),
		CreateWeaponRandom(),
		CreateArmorHeadRandom(), CreateArmorChestRandom(), CreateArmorLegRandom(),
		CreateArmorShoulderRandom(), CreateArmorShoulderRandom(),
		CreateArmorArmRandom(), CreateArmorArmRandom(),
		CreateArmorFootRandom(), CreateArmorFootRandom(),
		new OrcAi(),
		new OrcDestructible(RandomNumberInRange(60, 120), RandomNumberInRange(2, 6) * 1.0f),
		nullptr,
		nullptr,
		true, true, true);

	return(actor);
}

Actor*
CreateActorOrcThug(int x, int y) {
	Actor* actor = CreateTemplateActor(
		x, y,
		ORC_THUG_CODE, ORC_THUG_COLOR,
		GenerateOrcName(), GenerateNickname(),
		CreateWeaponSword1HWood(),
		CreateArmorHeadCapCloth(), CreateArmorChestVestCloth(), CreateArmorLegPantsCloth(),
		CreateArmorShoulderPauldronCloth(), CreateArmorShoulderPauldronCloth(),
		CreateArmorArmBracerCloth(), CreateArmorArmBracerCloth(),
		CreateArmorFootShoeCloth(), CreateArmorFootShoeCloth(),
		new OrcAi(),
		new OrcDestructible(60, 2),
		nullptr,
		nullptr,
		true, true, true);

	return(actor);
}

Actor*
CreateActorOrcFighter(int x, int y) {
	Actor* actor = CreateTemplateActor(
		x, y,
		ORC_FIGHTER_CODE, ORC_FIGHTER_COLOR,
		GenerateOrcName(), GenerateNickname(),
		CreateWeaponSword1HStone(),
		CreateArmorHeadCapLeather(), CreateArmorChestVestLeather(), CreateArmorLegPantsLeather(),
		CreateArmorShoulderPauldronLeather(), CreateArmorShoulderPauldronLeather(),
		CreateArmorArmBracerLeather(), CreateArmorArmBracerLeather(),
		CreateArmorFootShoeLeather(), CreateArmorFootShoeLeather(),
		new OrcAi(),
		new OrcDestructible(110, 4),
		nullptr,
		nullptr,
		true, true, true);

	return(actor);
}

Actor*
CreateActorOrcVeteran(int x, int y) {
	Actor* actor = CreateTemplateActor(
		x, y,
		ORC_VETERAN_CODE, ORC_VETERAN_COLOR,
		GenerateOrcName(), GenerateNickname(),
		CreateWeaponSword1HIron(),
		CreateArmorHeadHelmetIron(), CreateArmorChestBreastplateIron(), CreateArmorLegGreavesIron(),
		CreateArmorShoulderPauldronIron(), CreateArmorShoulderPauldronIron(),
		CreateArmorArmGauntletIron(), CreateArmorArmGauntletIron(),
		CreateArmorFootBootIron(), CreateArmorFootBootIron(),
		new OrcAi(),
		new OrcDestructible(160, 6),
		nullptr,
		nullptr,
		true, true, true);

	return(actor);
}

Actor*
CreateActorItemPotionHealth(int x, int y) {
	Actor* actor = CreateTemplateActor(
		x, y,
		ITEM_POTION_HEALTH_CODE, ITEM_POTION_HEALTH_COLOR,
		"Health Potion", 0,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr,
		new Healer(4),
		nullptr,
		false, true, false);

	return(actor);
}

Actor*
CreateActorItemScrollLightningBolt(int x, int y) {
	Actor* actor = CreateTemplateActor(
		x, y,
		ITEM_SCROLL_LIGHTNING_BOLT_CODE, ITEM_SCROLL_LIGHTNING_BOLT_COLOR,
		"Scroll of Lightning Bolt", 0,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr,
		new LightningBolt(5, 20),
		nullptr,
		false, true, false);

	return(actor);
}

Actor*
CreateActorItemScrollFireball(int x, int y) {
	Actor* actor = CreateTemplateActor(
		x, y,
		ITEM_SCROLL_FIREBALL_CODE, ITEM_SCROLL_FIREBALL_COLOR,
		"Scroll of Fireball", 0,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr,
		new Fireball(3, 12),
		nullptr,
		false, true, false);

	return(actor);
}