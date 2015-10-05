#include "main.hpp"

Deity::Deity() :
	id(0),
	name(""),
	species(DEITY_SPECIES_NONE), sex(DEITY_SEX_NONE), worship(DEITY_WORSHIP_NONE),
	fullDescription("")
{	
}

Deity::~Deity() {
	
}

void
Deity::Generate() {
	local_persist int currentId = 0;
	id = ++currentId;

	name = ReadLineFromFileByRandomIndex(DEITY_NAME_PATH);
	RemoveTrailingNewLineFromString(name);

	species = RandomDeitySpecies();
	sex = RandomDeitySex();
	worship = RandomDeityWorship();

	char* sexText = DeitySexToText();
	char* worshipText = DeityWorshipToText();
	char* speciesText = DeitySpeciesToText();

	fullDescription = ToString(
		"%s, The %s of %s, has the form of %s %s.\n",
		name,
		sexText,
		worshipText,
		DecideIndefiniteArticle(speciesText),
		speciesText);
	std::cout << fullDescription;
}

DEITY_SPECIES
Deity::RandomDeitySpecies() {
	return((DEITY_SPECIES)RandomNumberInRange(0, (int)(DEITY_SPECIES_SIZE) - 1));
}

DEITY_SEX
Deity::RandomDeitySex() {
	return((DEITY_SEX)RandomNumberInRange(0, (int)(DEITY_SEX_SIZE) - 1));
}

DEITY_WORSHIP
Deity::RandomDeityWorship() {
	return((DEITY_WORSHIP)RandomNumberInRange(0, (int)(DEITY_WORSHIP_SIZE) - 1));
}

char*
Deity::DeitySpeciesToText() {
	switch(species) {
		case DEITY_SPECIES_NONE:		return("NONE");
		case DEITY_SPECIES_ORC:			return("ORC");
		case DEITY_SPECIES_HUMAN:		return("HUMAN");
		case DEITY_SPECIES_SIZE:		return("NONE");
		default:						return("NONE");
	}
}

char*
Deity::DeitySexToText() {
	switch(sex) {
		case DEITY_SEX_NONE:			return("NONE");
		case DEITY_SEX_MALE:			return("GOD");
		case DEITY_SEX_FEMALE:			return("GODDESS");
		case DEITY_SEX_ASEXUAL:			return("DEITY");
		case DEITY_SEX_SIZE:			return("NONE");
		default:						return("NONE");
	}
}

char*
Deity::DeityWorshipToText() {
	switch(worship) {
		case DEITY_WORSHIP_NONE:		return("NONE");
		case DEITY_WORSHIP_WAR:			return("WAR");
		case DEITY_WORSHIP_LOVE:		return("LOVE");
		case DEITY_WORSHIP_BREAD:		return("BREAD");
		case DEITY_WORSHIP_SIZE:		return("NONE");
		default:						return("NONE");
	}
}

Deities::Deities() {
	
}

Deities::~Deities() {
	
}