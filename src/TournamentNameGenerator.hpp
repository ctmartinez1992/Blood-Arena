#ifndef RL_TOURNAMENT_NAME_GENERATOR_HPP
#define RL_TOURNAMENT_NAME_GENERATOR_HPP

typedef struct tournament_name {
	char* fullName;
	char* adjective;
	char* noun;
	char* typePlace;
	char* ofSomething;
	char* andSomething;
} tournament_name;

tournament_name*
GenerateRandomTournamentName();

void
FreeTournamentName(tournament_name* name);

#endif