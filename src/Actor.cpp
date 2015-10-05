#include <math.h>
#include "main.hpp"

Actor::Actor(int x, int y) :
    x(x), y(y),
    power(0), gold(0),
	code(0), color(TCODColor::white),
	name(0), nickname(0), fullName(0), corpseName(0),
    blocks(true), fovOnly(true),
	leftHandWeapon(nullptr),
	headArmor(nullptr), chestArmor(nullptr), legArmor(nullptr),
	leftShoulderArmor(nullptr), rightShoulderArmor(nullptr),
	leftArmArmor(nullptr), rightArmArmor(nullptr),
	leftFootArmor(nullptr), rightFootArmor(nullptr),
	destructible(nullptr), ai(nullptr),
	pickable(nullptr), container(nullptr),
	traits(nullptr)
{
}

Actor::~Actor() {
	CleanPointer(leftHandWeapon);

	CleanPointer(headArmor);
	CleanPointer(chestArmor);
	CleanPointer(legArmor);
	CleanPointer(leftShoulderArmor);
	CleanPointer(rightShoulderArmor);
	CleanPointer(leftArmArmor);
	CleanPointer(rightArmArmor);
	CleanPointer(leftFootArmor);
	CleanPointer(rightFootArmor);

	CleanPointer(destructible);
	CleanPointer(ai);
	CleanPointer(pickable);
	CleanPointer(container);
	CleanPointer(traits);

	CleanPointer(name);
	CleanPointer(nickname);
	CleanPointer(fullName);
	CleanPointer(corpseName);
}

void
Actor::Render() {
    TCODConsole::root->setChar(x, y, code);
    TCODConsole::root->setCharForeground(x, y, color);
}

void
Actor::Update() {
	if(ai) {
		ai->Update(this);
	}
}

void
Actor::CalculatePower() {
	power = destructible->defense;

	power += (leftHandWeapon->baseDamage + leftHandWeapon->defense) *
			 leftHandWeapon->GetMaterialModifierValue(leftHandWeapon->type, leftHandWeapon->material);

	power += headArmor->CalculateArmorPieceFullDefense();
	power += chestArmor->CalculateArmorPieceFullDefense();
	power += legArmor->CalculateArmorPieceFullDefense();
	power += leftShoulderArmor->CalculateArmorPieceFullDefense();
	power += rightShoulderArmor->CalculateArmorPieceFullDefense();
	power += leftArmArmor->CalculateArmorPieceFullDefense();
	power += rightArmArmor->CalculateArmorPieceFullDefense();
	power += leftFootArmor->CalculateArmorPieceFullDefense();
	power += rightFootArmor->CalculateArmorPieceFullDefense();
}

float
Actor::GetDistance(int cx, int cy) {
    int dx = x - cx;
    int dy = y - cy;

    return(FastSqrtf((float)(dx * dx + dy * dy)));
}