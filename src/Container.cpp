#include "main.hpp"

Container::Container(int size) :
	size(size)
{
}

Container::~Container() {
    inventory.clearAndDelete();
}

bool
Container::Add(Actor* actor) {
    if(size > 0 && inventory.size() >= size) {
        return(false);
    }

    inventory.push(actor);

    return(true);
}

void
Container::Remove(Actor* actor) {
    inventory.remove(actor);
}