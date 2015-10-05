#include "main.hpp"

bool
Pickable::Pick(Actor* owner, Actor* wearer) {
    if(wearer->container && wearer->container->Add(owner)) {
        e->RestActorFromWorld(owner);

        return(true);
    }

    return(false);
}

void
Pickable::Drop(Actor* owner, Actor* wearer) {
    if(wearer->container) {
        wearer->container->Remove(owner);
        e->AddActorToArena(owner);

        owner->x = wearer->x;
        owner->y = wearer->y;

        e->gui->Message(TCODColor::lightGrey, "%s dropped %s.", wearer->name, owner->name);
    }
}

bool
Pickable::Use(Actor* owner, Actor* wearer) {
	if(wearer->container) {
        wearer->container->Remove(owner);

        return(true);
    }

    return(false);
}

Healer::Healer(int amount) :
	amount(amount)
{
}

bool
Healer::Use(Actor* owner, Actor* wearer) {
    if(wearer->destructible) {
        int amountHealed = wearer->destructible->Heal(amount);

        if(amountHealed > 0) {
            return(Pickable::Use(owner, wearer));
        }
    }

    return(false);
}

LightningBolt::LightningBolt(int range, int damage) :
	range(range),
	damage(damage)
{
}

bool
LightningBolt::Use(Actor* owner, Actor* wearer) {
    Actor* closest = e->GetClosestDestructibleActor(wearer->x, wearer->y, range);

    if(!closest) {
        e->gui->Message(TCODColor::lightGrey, "No enemy is close enough to strike.");

        return(false);
    }

    e->gui->Message(TCODColor::lightBlue, "A lighting bolt strikes the %s with a loud thunder!\n"
                        "It deals %g damage.", closest->name, damage);

    closest->destructible->TakeDamage(closest, damage);

    return(Pickable::Use(owner, wearer));
}

Fireball::Fireball(int range, int damage) :
	LightningBolt(range, damage)
{
}

bool
Fireball::Use(Actor* owner, Actor* wearer) {
	int x;
	int y;

    e->gui->Message(TCODColor::cyan, "Left-click a target tile for the fireball.\nRight-click to cancel.");
    
    if(!e->PickATile(&x, &y)) {
        return(false);
    }

    e->gui->Message(TCODColor::orange, "The fireball explodes, burning everything within %g tiles!", range);

    for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
        Actor* actor = *it;

        if(actor->destructible && !actor->destructible->IsDead() && actor->GetDistance(x,y) <= range) {
            e->gui->Message(TCODColor::orange, "The %s gets burned for %g damage.", actor->name, damage);

            actor->destructible->TakeDamage(actor, damage);
        }
    }

    return Pickable::Use(owner, wearer);
}