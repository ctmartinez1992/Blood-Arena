#ifndef RL_PERSISTENT_HPP
#define RL_PERSISTENT_HPP

class Persistent {
public:
	virtual void
	Save(TCODZip& zip) = 0;

    virtual void
    Load(TCODZip& zip) = 0;
};

#endif