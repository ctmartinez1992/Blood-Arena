#include "main.hpp"

internal_function char*
RandomAdjective() {
	return(DODGetRandomContent(e->c->DOD_GENERATOR_TOURNAMENT_ADJECTIVE, "!!desc", "all"));
}

internal_function char*
RandomNoun() {
	return(DODGetRandomContent(e->c->DOD_GENERATOR_TOURNAMENT_NOUN, "!!desc", "all"));
}

internal_function char*
RandomTypePlace() {
	return(DODGetRandomContent(e->c->DOD_GENERATOR_TOURNAMENT_TYPE_PLACE, "!!desc", "all"));
}

internal_function char*
RandomOfSomething() {
	return(DODGetRandomContent(e->c->DOD_GENERATOR_TOURNAMENT_OF_SOMETHING, "!!desc", "all"));
}

internal_function char*
RandomAndSomething() {
	return(DODGetRandomContent(e->c->DOD_GENERATOR_TOURNAMENT_AND_SOMETHING, "!!desc", "all"));
}

internal_function bool
FilterAdjectiveAndNoun(char* adjective, char* compareAdjective, char* noun, char* compareNoun) {
	if(CompareCharPointers(adjective, compareAdjective) && CompareCharPointers(noun, compareNoun)) {
		adjective = ToString(" %s", RandomAdjective());
		RemoveTrailingNewLineFromString(adjective);

		noun = ToString(" %s", RandomNoun());
		RemoveTrailingNewLineFromString(noun);

		return(true);
	}

	return(false);
}

internal_function void
FilterPossibleMatchs(char* adjective, char* noun) {
	bool shouldRepeat = false;

	do {
		shouldRepeat = FilterAdjectiveAndNoun(adjective, "Agonizing", noun, "Agony");
	} while(shouldRepeat);
}

tournament_name*
GenerateRandomTournamentName() {
	char* adjective;
	char* noun;
	char* typePlace;
	char* ofSomething;
	char* andSomething;

	char* ofThe;
	char* ofAdjective;
	char* andThe;
	char* andAdjective;

	bool hasAdjective = false;
	bool hasNoun = false;
	bool hasTypePlace = false;
	bool hasSomething = false;

	if(PercentageChance(20)) {
		char* tmpAdjective = RandomAdjective();
		adjective = ToString(" %s", tmpAdjective);
		free(tmpAdjective);
		hasAdjective = true;

		char* tmpNoun = RandomNoun();
		noun = ToString(" %s", tmpNoun);
		free(tmpNoun);
		hasNoun = true;

		FilterPossibleMatchs(adjective, noun);
	}
	else if(PercentageChance(70)) {
		if(PercentageChance(65)) {
			char* tmpAdjective = RandomAdjective();
			adjective = ToString(" %s", tmpAdjective);
			free(tmpAdjective);
			hasAdjective = true;

			noun = 0;
		}
		else {
			char* tmpNoun = RandomNoun();
			noun = ToString(" %s", tmpNoun);
			free(tmpNoun);
			hasNoun = true;

			adjective = 0;
		}
	}
	else {
		adjective = 0;
		noun = 0;
	}

	if(!hasNoun) {
		char* tmpTypePlace = RandomTypePlace();
		typePlace = ToString(" %s", tmpTypePlace);
		free(tmpTypePlace);
		hasTypePlace = true;
	}
	else if(hasAdjective && hasNoun) {
		typePlace = 0;
	}
	else {
		if(PercentageChance(65)) {
			char* tmpTypePlace = RandomTypePlace();
			typePlace = ToString(" %s", tmpTypePlace);
			free(tmpTypePlace);
			hasTypePlace = true;
		}
		else {
			typePlace = 0;
		}
	}

	if(PercentageChance(30)) {
		ofThe = ToString(" the");
	}
	else {
		ofThe = 0;
	}

	if(PercentageChance(20)) {
		char* tmpOfAdjective = RandomAdjective();
		ofAdjective = ToString(" %s", tmpOfAdjective);
		free(tmpOfAdjective);
	}
	else {
		ofAdjective = 0;
	}

	if(!hasAdjective && !hasNoun) {
		char* tmpOfSomething = RandomOfSomething();
		ofSomething = ToString(" of%s%s %s",
							   (ofThe) ? ofThe : "",
							   (ofAdjective) ? ofAdjective : "",
							   (tmpOfSomething) ? tmpOfSomething : "");
		free(tmpOfSomething);
		hasSomething = true;
	}
	else if((hasAdjective || hasNoun) && PercentageChance(50)) {
		char* tmpOfSomething = RandomOfSomething();
		ofSomething = ToString(" of%s%s %s",
							   (ofThe) ? ofThe : "",
							   (ofAdjective) ? ofAdjective : "",
							   (tmpOfSomething) ? tmpOfSomething : "");
		free(tmpOfSomething);
		hasSomething = true;
	}
	else if(!hasTypePlace && (hasAdjective || hasNoun)) {
		char* tmpOfSomething = RandomOfSomething();
		ofSomething = ToString(" of%s%s %s",
							   (ofThe) ? ofThe : "",
							   (ofAdjective) ? ofAdjective : "",
							   (tmpOfSomething) ? tmpOfSomething : "");
		free(tmpOfSomething);
		hasSomething = true;
	}
	else {
		ofSomething = 0;
	}

	if(PercentageChance(20)) {
		andThe = ToString(" the");
	}
	else {
		andThe = 0;
	}

	if(PercentageChance(10)) {
		char* tmpAndAdjective = RandomAdjective();
		andAdjective = ToString(" %s", tmpAndAdjective);
		free(tmpAndAdjective);
	}
	else {
		andAdjective = 0;
	}

	if(hasSomething && PercentageChance(25)) {
		char* tmpAndSomething = 0;

		do {
			tmpAndSomething = RandomAndSomething();
			andSomething = ToString(" and%s%s %s",
									(andThe) ? andThe : "",
									(andAdjective) ? andAdjective : "",
									(tmpAndSomething) ? tmpAndSomething : "");
		} while(CompareCharPointers(ofSomething, andSomething));

		if(tmpAndSomething) {
			free(tmpAndSomething);
		}
	}
	else {
		andSomething = 0;
	}

	char* fullName = ToString(
		"The%s%s%s%s%s\n",
		(adjective) ? adjective : "",
		(noun) ? noun : "",
		(typePlace) ? typePlace : "",
		(ofSomething) ? ofSomething : "",
		(andSomething) ? andSomething : "");

	tournament_name* result = (tournament_name*)malloc(sizeof(tournament_name));
	result->fullName = fullName;
	result->adjective = adjective;
	result->noun = noun;
	result->typePlace = typePlace;
	result->ofSomething = ofSomething;
	result->andSomething = andSomething;

	free(ofThe);
	free(ofAdjective);
	free(andThe);
	free(andAdjective);

	return(result);
}

void
FreeTournamentName(tournament_name* name) {
	if(name) {
		if(name->fullName) {
			free(name->fullName);
			name->fullName = nullptr;
		}
		if(name->adjective) {
			free(name->adjective);
			name->adjective = nullptr;
		}
		if(name->noun) {
			free(name->noun);
			name->noun = nullptr;
		}
		if(name->typePlace) {
			free(name->typePlace);
			name->typePlace = nullptr;
		}
		if(name->ofSomething) {
			free(name->ofSomething);
			name->ofSomething = nullptr;
		}
		if(name->andSomething) {
			free(name->andSomething);
			name->andSomething = nullptr;
		}

		free(name);
		name = nullptr;
	}
}