#ifndef RL_TOURNAMENT_HPP
#define RL_TOURNAMENT_HPP

typedef struct match_result {
	Actor* first;
	Actor* second;
	Actor* third;
	Actor* fourth;
} match_result;

enum TOUR_TYPE {
	TOUR_TYPE_UNKNOWN = 0,
	TOUR_TYPE_1V1,
	TOUR_TYPE_1V1V1,
};

enum TOUR_BRACKET {
	TOUR_BRACKET_UNKNOWN = 0,
	TOUR_BRACKET_1V1_OVER,
	TOUR_BRACKET_1V1_FINAL,
	TOUR_BRACKET_1V1_SEMI,
	TOUR_BRACKET_1V1_QUARTER,
	TOUR_BRACKET_1V1_R8,
	TOUR_BRACKET_1V1_R16,
	TOUR_BRACKET_1V1_R32,
	TOUR_BRACKET_1V1V1_OVER,
	TOUR_BRACKET_1V1V1_FINAL,
	TOUR_BRACKET_1V1V1_SEMI,
	TOUR_BRACKET_1V1V1_QUARTER,
	TOUR_BRACKET_1V1V1_R8,
	TOUR_BRACKET_1V1V1_R16,
	TOUR_BRACKET_1V1V1_R32
};

class Match {
public:
	Actor* contender1;
	Actor* contender2;
	Actor* contender3;

	match_result* result;

	TOUR_BRACKET bracket;

	Match();
	virtual ~Match();

	virtual match_result*
	SimulateMatch() = 0;

	virtual void
	SetMatch(TOUR_BRACKET bracket, Actor* c1, Actor* c2, Actor* c3 = nullptr, Actor* c4 = nullptr) = 0;
};

class Match1V1 : public Match {
public:
	Match1V1();
	~Match1V1();

	match_result*
	SimulateMatch();

	void
	SetMatch(TOUR_BRACKET bracket, Actor* c1, Actor* c2, Actor* c3 = nullptr, Actor* c4 = nullptr);
};

class Match1V1V1 : public Match {
public:
	Match1V1V1();
	~Match1V1V1();

	match_result*
	SimulateMatch();

	void
	SetMatch(TOUR_BRACKET bracket, Actor* c1, Actor* c2, Actor* c3 = nullptr, Actor* c4 = nullptr);
};

class Tournament {
public:
	Actor* first;
	Actor* second;
	Actor* third;
	Actor* fourth;

	unsigned int amountOfContenders;
	unsigned int currentAmountOfContenders;
	TCODList<Actor*> allContenders;
	TCODList<Actor*> currentContenders;

	unsigned int amountOfMatchs;
	unsigned int currentAmountOfMatchs;
	TCODList<Match*> allMatchs;
	TCODList<Match*> currentMatchs;

	//NOTE: Only used when player is in the tournament.
	Match* nextMatch;

	TOUR_BRACKET type;
	TOUR_BRACKET currentType;

	tournament_name* name;
	unsigned int id;

	unsigned int gold;

	bool hasPlayer;

	Tournament();
	virtual ~Tournament();

	int
	GetAmountOfMatchsByBracket(TOUR_BRACKET type);

	char*
	BracketToString(TOUR_BRACKET bracket);

	void
	GenerateRandomContenders(unsigned int numberOfContenders);

	void
	PopulateTournament(bool withPlayer = false);

	void
	SimulateTournament();

	void
	ChangeToNextRound();

	void
	HandleMatchLoser(Match* match, match_result* result);

	bool
	PrintTournamentInformation();

	void
	AnnounceWinner(match_result* result);

	char*
	TournamentType();

	virtual TOUR_BRACKET
	GetCurrentBracket() = 0;

	virtual void
	GenerateTournament() = 0;

	virtual void
	GenerateRandomMatchs(unsigned int numberOfMatchs) = 0;

	//NOTE: Returns true if it's the last match of the tournament.
	virtual bool
	SimulateMatch() = 0;

	//NOTE: Works as if it simulated the match, but it doesn't simulate it, it just assumes it was already played.
	//NOTE: Returns true if it's the last match of the tournament.
	virtual bool
	AdvanceMatch() = 0;

	virtual int
	PrintTournamentCurrentStandings() = 0;
};

class Tournament1V1 : public Tournament {
public:
	Tournament1V1();
	~Tournament1V1();

	TOUR_BRACKET
	GetCurrentBracket();

	void
	GenerateTournament();

	void
	GenerateRandomMatchs(unsigned int numberOfMatchs);

	//NOTE: Returns true if it's the last match of the tournament.
	bool
	SimulateMatch();

	//NOTE: Works as if it simulated the match, but it doesn't simulate it, it just assumes it was already played.
	//NOTE: Returns true if it's the last match of the tournament.
	bool
	AdvanceMatch();

	int
	PrintTournamentCurrentStandings();
};

class Tournament1V1V1 : public Tournament {
public:
	Tournament1V1V1();
	~Tournament1V1V1();

	TOUR_BRACKET
	GetCurrentBracket();

	void
	GenerateTournament();

	void
	GenerateRandomMatchs(unsigned int numberOfMatchs);

	//NOTE: Returns true if it's the last match of the tournament.
	bool
	SimulateMatch();

	//NOTE: Works as if it simulated the match, but it doesn't simulate it, it just assumes it was already played.
	//NOTE: Returns true if it's the last match of the tournament.
	bool
	AdvanceMatch();

	int
	PrintTournamentCurrentStandings();
};

#endif