#include "main.hpp"

Tournament::Tournament() :
	first(nullptr), second(nullptr), third(nullptr), fourth(nullptr),
	amountOfContenders(0), currentAmountOfContenders(0), amountOfMatchs(0), currentAmountOfMatchs(0),
	nextMatch(nullptr),
	type(TOUR_BRACKET_UNKNOWN), currentType(TOUR_BRACKET_UNKNOWN),
	name(nullptr), id(0), gold(0), hasPlayer(false)
{
}

Tournament::~Tournament() {
	first = nullptr;
	second = nullptr;
	third = nullptr;
	fourth = nullptr;

	amountOfContenders = 0;
	currentAmountOfContenders = 0;
	allContenders.clear();
	currentContenders.clear();

	amountOfMatchs = 0;
	currentAmountOfMatchs = 0;
	allMatchs.clearAndDelete();
	currentMatchs.clearAndDelete();

	nextMatch = nullptr;

	type = TOUR_BRACKET_UNKNOWN;
	currentType = TOUR_BRACKET_UNKNOWN;

	FreeTournamentName(name);
	id = 0;

	gold = 0;

	hasPlayer = false;
}

int
Tournament::GetAmountOfMatchsByBracket(TOUR_BRACKET type) {
	switch (type) {
		case TOUR_BRACKET_UNKNOWN:			return(-1);
		case TOUR_BRACKET_1V1_OVER:			return(0);
		case TOUR_BRACKET_1V1_FINAL:		return(1);
		case TOUR_BRACKET_1V1_SEMI:			return(2);
		case TOUR_BRACKET_1V1_QUARTER:		return(4);
		case TOUR_BRACKET_1V1_R8:			return(8);
		case TOUR_BRACKET_1V1_R16:			return(16);
		case TOUR_BRACKET_1V1_R32:			return(32);
		default:							return(-1);
	}
}

char*
Tournament::BracketToString(TOUR_BRACKET bracket) {
	switch (bracket) {
		case TOUR_BRACKET_UNKNOWN:			return("Unknown Bracket");
		case TOUR_BRACKET_1V1_R32:			return("Round of 32");
		case TOUR_BRACKET_1V1_R16:			return("Round of 16");
		case TOUR_BRACKET_1V1_R8:			return("Round of 8");
		case TOUR_BRACKET_1V1_QUARTER:		return("Quarter Finals");
		case TOUR_BRACKET_1V1_SEMI:			return("Semi Finals");
		case TOUR_BRACKET_1V1_FINAL:		return("Finals");
		case TOUR_BRACKET_1V1_OVER:			return("Tournament Over");
		default:							return("Non Existant Bracket");
	}
}

void
Tournament::GenerateRandomContenders(unsigned int numberOfContenders) {
	for(unsigned int n = 0; n < numberOfContenders; ++n) {
		Actor* actor = CreateActorFullRandomOrc();

		currentAmountOfContenders++;

		allContenders.push(actor);
		currentContenders.push(actor);

		e->AddActorToWorld(actor);
	}
}

void
Tournament::PopulateTournament(bool withPlayer) {
	GenerateRandomContenders((withPlayer) ? amountOfContenders - 1 : amountOfContenders);

	if(withPlayer) {
		currentAmountOfContenders++;

		allContenders.push(e->player);
		currentContenders.push(e->player);

		hasPlayer = true;
	}

	GenerateRandomMatchs(amountOfContenders / 2);

	nextMatch = currentMatchs.get(0);
}

void
Tournament::SimulateTournament() {
	bool isRunning = true;

	do {
		Match* match = nullptr;
		match_result* result = nullptr;

		for(int n = 0; n < currentMatchs.size(); ++n) {
			match = currentMatchs.get(n);
			result = match->SimulateMatch();

			HandleMatchLoser(match, result);
		}

		if(currentContenders.size() > 1) {
			ChangeToNextRound();
		}
		else {
			AnnounceWinner(result);
			isRunning = false;
		}
	} while(isRunning);
}

void
Tournament::ChangeToNextRound() {
	currentType = (TOUR_BRACKET)(((int)currentType) - 1);

	GenerateRandomMatchs(GetAmountOfMatchsByBracket(currentType));
}

void
Tournament::HandleMatchLoser(Match* match, match_result* result) {
	e->gui->Message(TCODColor::white, "%s killed %s", result->first->name, result->second->name);

	currentAmountOfContenders--;
	currentAmountOfMatchs--;

	currentContenders.remove(result->second);
	e->RestActorFromWorld(result->second);

	if(result->third) {
		currentContenders.remove(result->third);
		e->RestActorFromWorld(result->third);
	}

	if(result->fourth) {
		currentContenders.remove(result->fourth);
		e->RestActorFromWorld(result->fourth);
	}

	currentMatchs.remove(match);
}

bool
Tournament::PrintTournamentInformation() {
    TCODConsole* console = &GUI_CONSOLE_VIEW_TOURNAMENT;

	console->setDefaultForeground(TCODColor(200, 180, 50));
	console->printFrame(0, 0, GUI_VIEW_TOURNAMENT_WIDTH, GUI_VIEW_TOURNAMENT_HEIGHT, true,
		TCOD_BKGND_DEFAULT, "%s", name->fullName);

	console->setDefaultForeground(TCODColor::white);
	console->print(16, 38, "...Press ENTER to close");

	console->print(2, 2, "id: %d", id);
	console->print(2, 3, "type: %s", TournamentType());
	console->print(2, 4, "contenders: %d", amountOfContenders);

	console->print(2, 6, "prize: %u gold", gold);

	console->print(2, 8, "options:");

	e->gui->HighlightOption(console, 6, 9, "Join");

	TCODConsole::blit(console, 0, 0, GUI_VIEW_TOURNAMENT_WIDTH, GUI_VIEW_TOURNAMENT_HEIGHT, TCODConsole::root,
		e->screenWidth / 2 - GUI_VIEW_TOURNAMENT_WIDTH / 2,
		e->screenHeight / 2 - GUI_VIEW_TOURNAMENT_HEIGHT / 2);
	TCODConsole::flush();

	TCOD_key_t key;
	bool exitMenu = false;
	bool returnToMain = false;

	do {
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);

		if(key.vk == TCODK_CHAR) {
			if(key.c == 'j' || key.c == 'J') {
				e->SetRunningTournament(this);
				exitMenu = true;
				returnToMain = true;
			}
		}
		else if(key.vk == TCODK_ENTER) {
			exitMenu = true;
		}
	} while(!exitMenu);

	return(returnToMain);
}

void
Tournament::AnnounceWinner(match_result* result) {
	first = result->first;
	second = result->second;
	third = result->third;
	fourth = result->fourth;

	e->gui->Message(TCODColor::red, "%s is the grand winner!!!", first->name);

	first->gold += gold;
}

char*
Tournament::TournamentType() {
	switch (type) {
		case TOUR_BRACKET_UNKNOWN: 			return("UNKNOWN"); break;
		case TOUR_BRACKET_1V1_OVER: 		return("1 v 1"); break;
		case TOUR_BRACKET_1V1_FINAL: 		return("1 v 1"); break;
		case TOUR_BRACKET_1V1_SEMI: 		return("1 v 1"); break;
		case TOUR_BRACKET_1V1_QUARTER: 		return("1 v 1"); break;
		case TOUR_BRACKET_1V1_R8: 			return("1 v 1"); break;
		case TOUR_BRACKET_1V1_R16: 			return("1 v 1"); break;
		case TOUR_BRACKET_1V1_R32: 			return("1 v 1"); break;
		case TOUR_BRACKET_1V1V1_OVER: 		return("1 v 1 v 1"); break;
		case TOUR_BRACKET_1V1V1_FINAL: 		return("1 v 1 v 1"); break;
		case TOUR_BRACKET_1V1V1_SEMI: 		return("1 v 1 v 1"); break;
		case TOUR_BRACKET_1V1V1_QUARTER: 	return("1 v 1 v 1"); break;
		case TOUR_BRACKET_1V1V1_R8: 		return("1 v 1 v 1"); break;
		case TOUR_BRACKET_1V1V1_R16: 		return("1 v 1 v 1"); break;
		case TOUR_BRACKET_1V1V1_R32:		return("1 v 1 v 1"); break;
		default: 							return("WHAT!"); break;
	}
}

Tournament1V1::Tournament1V1() :
Tournament()
{
}

Tournament1V1::~Tournament1V1() {
}

TOUR_BRACKET
Tournament1V1::GetCurrentBracket() {
	if(currentAmountOfContenders == 1) {
		return(TOUR_BRACKET_1V1_OVER);
	}
	else if(currentAmountOfContenders == 2) {
		return(TOUR_BRACKET_1V1_FINAL);
	}
	else if(currentAmountOfContenders >= 3 && currentAmountOfContenders <= 4) {
		return(TOUR_BRACKET_1V1_SEMI);
	}
	else if(currentAmountOfContenders >= 5 && currentAmountOfContenders <= 8) {
		return(TOUR_BRACKET_1V1_QUARTER);
	}
	else if(currentAmountOfContenders >= 9 && currentAmountOfContenders <= 16) {
		return(TOUR_BRACKET_1V1_R8);
	}
	else if(currentAmountOfContenders >= 17 && currentAmountOfContenders <= 32) {
		return(TOUR_BRACKET_1V1_R16);
	}
	else if(currentAmountOfContenders >= 33 && currentAmountOfContenders <= 64) {
		return(TOUR_BRACKET_1V1_R32);
	}
	else {
		return(TOUR_BRACKET_UNKNOWN);
	}
}

void
Tournament1V1::GenerateTournament() {
	//TODO: Only doing small stuff for now.
	int percentageDivision = RandomNumberInRange(1, 2);

	switch(percentageDivision) {
		case 1: 	type = TOUR_BRACKET_1V1_QUARTER;
					amountOfContenders = 8;
					currentAmountOfContenders = 0;
					break;
		case 2: 	type = TOUR_BRACKET_1V1_R8;
					amountOfContenders = 16;
					currentAmountOfContenders = 0;
					break;
		case 3: 	type = TOUR_BRACKET_1V1_R16;
					amountOfContenders = 32;
					currentAmountOfContenders = 0;
					break;
		case 4: 	type = TOUR_BRACKET_1V1_R32;
					amountOfContenders = 64;
					currentAmountOfContenders = 0;
					break;
		default: 	type = TOUR_BRACKET_1V1_QUARTER;
					amountOfContenders = 8;
					currentAmountOfContenders = 0;
					break;
	}

	amountOfMatchs = amountOfContenders - 1;

	currentType = type;
}

void
Tournament1V1::GenerateRandomMatchs(unsigned int numberOfMatchs) {
	for(unsigned int n = 0, index = 0; n < numberOfMatchs; ++n, index += 2) {
		Actor* contender1 = currentContenders.get(index);
		Actor* contender2 = currentContenders.get(index + 1);

		Match* match = new Match1V1();
		match->SetMatch(GetCurrentBracket(), contender1, contender2);

		currentAmountOfMatchs++;

		allMatchs.push(match);
		currentMatchs.push(match);
	}
}

bool
Tournament1V1::SimulateMatch() {
	Match* match = nextMatch;
	match_result* result = match->SimulateMatch();

	HandleMatchLoser(match, result);

	if(currentContenders.size() == 1) {
		AnnounceWinner(result);
		return(true);
	}
	else {
		if(currentMatchs.isEmpty()) {
			ChangeToNextRound();
		}

		nextMatch = currentMatchs.get(0);
	}

	return(false);
}

bool
Tournament1V1::AdvanceMatch() {
	Match* match = e->runningMatch;
	match_result* result = match->result;

	HandleMatchLoser(match, result);

	if(currentContenders.size() == 1) {
		AnnounceWinner(result);
		return(true);
	}
	else {
		if(currentMatchs.isEmpty()) {
			ChangeToNextRound();
		}

		nextMatch = currentMatchs.get(0);
	}

	return(false);
}

int
Tournament1V1::PrintTournamentCurrentStandings() {
	Match* match = nullptr;

	int menuXTournamentName = 2;
	int menuYTournamentName = 2;
	int menuXBracket = 4;
	int menuYBracket = 4;
	int menuX = 6;
	int menuY = 6;

	bool isNextMatch = true;
	char* nextMatchString = "";

	TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
	TCODConsole::root->print(menuXTournamentName, menuYTournamentName, "%s", name->fullName);

	TOUR_BRACKET lastBracket = allMatchs.get(allMatchs.size() - 1)->bracket;

	for (int n = 0; n < allMatchs.size(); ++n) {
		TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
		TCODConsole::root->print(menuXBracket, menuYBracket, "%s:", BracketToString(lastBracket));
		
		match = allMatchs.get(n);

		if(match->bracket == lastBracket) {

			if(match->result) {
				TCODConsole::root->print(menuX, menuY, "%s vs %s",
										 match->contender1->name, match->contender2->name);
				TCODConsole::root->print(menuX + 30, menuY, "(Winner: %s)", match->result->first->fullName);
			}
			else {
				if(isNextMatch) {
					nextMatchString = ToString("%s vs %s", match->contender1->name, match->contender2->name);

					TCODConsole::root->setDefaultForeground(TCODColor::lightBlue);
					TCODConsole::root->print(menuX - 2, menuY, "> %s", nextMatchString);

					isNextMatch = false;
				}
				else {
					TCODConsole::root->print(menuX, menuY, "%s vs %s",
											 match->contender1->name, match->contender2->name);
				}
			}

			menuY += 2;
		}

		if(lastBracket != allMatchs.get(allMatchs.size() - 1)->bracket) {
			lastBracket = allMatchs.get(allMatchs.size() - 1)->bracket;
		}
	}

	menuY += 2;
	TCODConsole::root->setDefaultForeground(TCODColor::lightBlue);
	TCODConsole::root->print(menuX - 4, menuY, "Next Match: %s", nextMatchString);

	if(first) {
		menuY += 2;

		TCODConsole::root->setDefaultForeground(TCODColor::red);
		TCODConsole::root->print(menuX, menuY, "%s is the grand winner!!!", first->name);
		TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);

		menuY = 0;
	}

	TCODConsole::flush();

	return(menuY);
}

Tournament1V1V1::Tournament1V1V1() :
Tournament()
{
}

Tournament1V1V1::~Tournament1V1V1() {
}

TOUR_BRACKET
Tournament1V1V1::GetCurrentBracket() {
	if(currentAmountOfContenders <= 2) {
		return(TOUR_BRACKET_1V1V1_OVER);
	}
	else if(currentAmountOfContenders == 3) {
		return(TOUR_BRACKET_1V1V1_FINAL);
	}
	else if(currentAmountOfContenders >= 4 && currentAmountOfContenders <= 6) {
		return(TOUR_BRACKET_1V1V1_SEMI);
	}
	else if(currentAmountOfContenders >= 7 && currentAmountOfContenders <= 12) {
		return(TOUR_BRACKET_1V1V1_QUARTER);
	}
	else if(currentAmountOfContenders >= 13 && currentAmountOfContenders <= 24) {
		return(TOUR_BRACKET_1V1V1_R8);
	}
	else if(currentAmountOfContenders >= 25 && currentAmountOfContenders <= 48) {
		return(TOUR_BRACKET_1V1V1_R16);
	}
	else if(currentAmountOfContenders >= 49 && currentAmountOfContenders <= 96) {
		return(TOUR_BRACKET_1V1V1_R32);
	}
	else {
		return(TOUR_BRACKET_UNKNOWN);
	}
}

void
Tournament1V1V1::GenerateTournament() {
	//TODO: Only doing small stuff for now.
	int percentageDivision = RandomNumberInRange(1, 2);

	switch(percentageDivision) {
		case 1: 	type = TOUR_BRACKET_1V1V1_QUARTER;
					amountOfContenders = 12;
					currentAmountOfContenders = 0;
					break;
		case 2: 	type = TOUR_BRACKET_1V1V1_R8;
					amountOfContenders = 24;
					currentAmountOfContenders = 0;
					break;
		case 3: 	type = TOUR_BRACKET_1V1V1_R16;
					amountOfContenders = 48;
					currentAmountOfContenders = 0;
					break;
		case 4: 	type = TOUR_BRACKET_1V1V1_R32;
					amountOfContenders = 96;
					currentAmountOfContenders = 0;
					break;
		default: 	type = TOUR_BRACKET_1V1V1_QUARTER;
					amountOfContenders = 12;
					currentAmountOfContenders = 0;
					break;
	}

	amountOfMatchs = amountOfContenders - 1;

	currentType = type;
}

void
Tournament1V1V1::GenerateRandomMatchs(unsigned int numberOfMatchs) {
	for(unsigned int n = 0, index = 0; n < numberOfMatchs; ++n, index += 3) {
		Actor* contender1 = currentContenders.get(index);
		Actor* contender2 = currentContenders.get(index + 1);
		Actor* contender3 = currentContenders.get(index + 2);

		Match* match = new Match1V1V1();
		match->SetMatch(GetCurrentBracket(), contender1, contender2, contender3);

		currentAmountOfMatchs++;

		allMatchs.push(match);
		currentMatchs.push(match);
	}
}

bool
Tournament1V1V1::SimulateMatch() {
	Match* match = e->runningMatch;
	match_result* result = match->SimulateMatch();

	HandleMatchLoser(match, result);

	if(currentContenders.size() == 1) {
		AnnounceWinner(result);
		return(true);
	}
	else {
		if(currentMatchs.isEmpty()) {
			ChangeToNextRound();
		}

		nextMatch = currentMatchs.get(0);
	}

	return(false);
}

bool
Tournament1V1V1::AdvanceMatch() {
	Match* match = nextMatch;
	match_result* result = match->result;

	HandleMatchLoser(match, result);

	if(currentContenders.size() == 1) {
		AnnounceWinner(result);
		return(true);
	}
	else {
		if(currentMatchs.isEmpty()) {
			ChangeToNextRound();
		}

		nextMatch = currentMatchs.get(0);
	}

	return(false);
}

int
Tournament1V1V1::PrintTournamentCurrentStandings() {
	Match* match = nullptr;

	int menuXTournamentName = 2;
	int menuYTournamentName = 2;
	int menuXBracket = 4;
	int menuYBracket = 4;
	int menuX = 6;
	int menuY = 6;

	bool isNextMatch = true;

	TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
	TCODConsole::root->print(menuXTournamentName, menuYTournamentName, "%s", name->fullName);

	TOUR_BRACKET lastBracket = allMatchs.get(allMatchs.size() - 1)->bracket;

	for (int n = 0; n < allMatchs.size(); ++n) {
		TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
		TCODConsole::root->print(menuXBracket, menuYBracket, "%s:", BracketToString(lastBracket));
		
		match = allMatchs.get(n);

		if(match->bracket == lastBracket) {

			if(match->result) {
				TCODConsole::root->print(menuX, menuY, "%s vs %s vx %s",
										 match->contender1->name, match->contender2->name, match->contender3->name);
				TCODConsole::root->print(menuX + 30, menuY, "(Winner: %s)", match->result->first->fullName);
			}
			else {
				if(isNextMatch) {
					TCODConsole::root->setDefaultForeground(TCODColor::lightBlue);
					TCODConsole::root->print(menuX - 2, menuY, "> %s vs %s vs %s",
											 match->contender1->name, match->contender2->name, match->contender3->name);

					isNextMatch = false;
				}
				else {
					TCODConsole::root->print(menuX, menuY, "%s vs %s vs %s",
											 match->contender1->name, match->contender2->name, match->contender3->name);
				}
			}

			menuY += 2;
		}

		if(lastBracket != allMatchs.get(allMatchs.size() - 1)->bracket) {
			lastBracket = allMatchs.get(allMatchs.size() - 1)->bracket;
		}
	}

	if(first) {
		menuY += 2;

		TCODConsole::root->setDefaultForeground(TCODColor::red);
		TCODConsole::root->print(menuX, menuY, "%s is the grand winner!!!", first->name);
		TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);

		menuY = 0;
	}

	TCODConsole::flush();

	return(menuY);
}

Match::Match() :
	contender1(nullptr), contender2(nullptr), contender3(nullptr),
	result(nullptr), bracket(TOUR_BRACKET_UNKNOWN)
{
}

Match::~Match() {
	//NOTE: Don't delete them, they might be useful for other stuff, hall of fame, history, stuff like that.
	contender1 = nullptr;
	contender2 = nullptr;
	contender3 = nullptr;
	result = nullptr;
	bracket = TOUR_BRACKET_UNKNOWN;
}

Match1V1::Match1V1() :
	Match()
{
}

Match1V1::~Match1V1() {
}

match_result*
Match1V1::SimulateMatch() {
	match_result* result = (match_result*)malloc(sizeof(match_result));

	//TODO: Use a system of percentage, rather than direct power comparison, good enough for now though.
	if(contender1->power >= contender2->power) {
		result->first = contender1;
		result->second = contender2;
	}
	else {
		result->first = contender2;
		result->second = contender1;
	}

	result->third = nullptr;
	result->fourth = nullptr;

	this->result = result;

	return(result);
}

void
Match1V1::SetMatch(TOUR_BRACKET bracket, Actor* c1, Actor* c2, Actor* c3, Actor* c4) {
	this->bracket = bracket;
	this->contender1 = c1;
	this->contender2 = c2;
	this->contender3 = nullptr;
}

Match1V1V1::Match1V1V1() :
	Match()
{
}

Match1V1V1::~Match1V1V1() {
}

match_result*
Match1V1V1::SimulateMatch() {
	match_result* result = (match_result*)malloc(sizeof(match_result));

	float power1 = contender1->power;
	float power2 = contender2->power;
	float power3 = contender3->power;

	//TODO: Use a system of percentage, rather than direct power comparison, good enough for now though.
	if(power1 >= power2 && power1 >= power3) {
		result->first = contender1;

		if(power2 >= power3) {
			result->second = contender2;
			result->third = contender3;
		}
		else {
			result->second = contender3;
			result->third = contender2;
		}
	}
	else if(power2 >= power1 && power2 >= power3) {
		result->first = contender2;

		if(power1 >= power3) {
			result->second = contender1;
			result->third = contender3;
		}
		else {
			result->second = contender1;
			result->third = contender3;
		}
	}
	else if(power3 >= power1 && power3 >= power2) {
		result->first = contender3;

		if(power1 >= power2) {
			result->second = contender1;
			result->third = contender2;
		}
		else {
			result->second = contender2;
			result->third = contender1;
		}
	}

	result->fourth = nullptr;

	this->result = result;

	return(result);
}

void
Match1V1V1::SetMatch(TOUR_BRACKET bracket, Actor* c1, Actor* c2, Actor* c3, Actor* c4) {
	this->bracket = bracket;
	this->contender1 = c1;
	this->contender2 = c2;
	this->contender3 = c3;
}