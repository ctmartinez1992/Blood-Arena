#ifndef RL_CONTAINER_HPP
#define RL_CONTAINER_HPP

class Container : public Persistent {
public:
	TCODList<Actor*> inventory;

	//NOTE: If 0, then it's infinite.
    int size;

    Container(int size);
	~Container();

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

    bool
    Add(Actor* actor);

	void
	Remove(Actor* actor);
};

#endif