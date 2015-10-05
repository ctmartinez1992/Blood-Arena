#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(int maxHP, float defense) :
    maxHP(maxHP), curHP(maxHP), defense(defense)
{
}

void
Destructible::Die(Actor* owner) {
	owner->code = '%';
	owner->color = TCODColor::darkRed;

	owner->blocks = false;

	e->SendToBackArena(owner);
}

void
Destructible::TakeDamage(Actor* owner, int damage) {
    if(damage > 0) {
        curHP -= damage;

        if (curHP <= 0) {
            Die(owner);
        }
    }
}

int
Destructible::Heal(int amount) {
    curHP += amount;

    if(curHP > maxHP) {
		amount -= curHP - maxHP;
		curHP = maxHP;
    }

    return(amount);
}

OrcDestructible::OrcDestructible(int maxHP, float defense) :
    Destructible(maxHP, defense)
{
}

void
OrcDestructible::Die(Actor* owner) {
    e->gui->Message(TCODColor::lightGrey, "%s is dead.", owner->name);

    Destructible::Die(owner);
}

PlayerDestructible::PlayerDestructible(int maxHP, float defense) :
    Destructible(maxHP, defense) 
{
}

void
PlayerDestructible::Die(Actor* owner) {
    e->gui->Message(TCODColor::red, "You died!");

    Destructible::Die(owner);
}