#ifndef RL_DEITIES_HPP
#define RL_DEITIES_HPP

global_variable char* DEITY_NAME_PATH = "res/random/deity_orc_name_list.txt";

enum DEITY_SPECIES {
	DEITY_SPECIES_NONE = -1,
	DEITY_SPECIES_ORC,
	DEITY_SPECIES_HUMAN,
	DEITY_SPECIES_SIZE
};

enum DEITY_SEX {
	DEITY_SEX_NONE = -1,
	DEITY_SEX_MALE,
	DEITY_SEX_FEMALE,
	DEITY_SEX_ASEXUAL,
	DEITY_SEX_SIZE
};

enum DEITY_WORSHIP {
	DEITY_WORSHIP_NONE = -1,
	DEITY_WORSHIP_WAR,
	DEITY_WORSHIP_LOVE,
	DEITY_WORSHIP_BREAD,
	DEITY_WORSHIP_SIZE,
};

class Deity {
public:
	int id;
	char* name;

	DEITY_SPECIES species;
	DEITY_SEX sex;
	DEITY_WORSHIP worship;

	char* fullDescription;

	Deity();
	~Deity();

	void
	Generate();

	DEITY_SPECIES
	RandomDeitySpecies();

	DEITY_SEX
	RandomDeitySex();

	DEITY_WORSHIP
	RandomDeityWorship();

	char*
	DeitySpeciesToText();

	char*
	DeitySexToText();

	char*
	DeityWorshipToText();
};

class Deities {
public:
	Deities();
	~Deities();
};

#endif