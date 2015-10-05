#include "main.hpp"

DODContent::DODContent() {
	/*	ATTACK *********************************************************************************************/
	/*		SLASH ******************************************************************************************/
	/*			SWORD **************************************************************************************/

	DOD_ATTACK_SLASH_SWORD =
		DODParseDODFileIntoDODTags("res/random/dod/attack/slash/sword_1h.txt");

	/******************************************************************************************************/
	/*	TOURNAMENT GENERATOR ******************************************************************************/
	/******************************************************************************************************/

	DOD_GENERATOR_TOURNAMENT_ADJECTIVE =
		DODParseDODFileIntoDODTags("res/random/dod/generator/tournament/adjective.txt");
	DOD_GENERATOR_TOURNAMENT_NOUN =
		DODParseDODFileIntoDODTags("res/random/dod/generator/tournament/noun.txt");
	DOD_GENERATOR_TOURNAMENT_TYPE_PLACE =
		DODParseDODFileIntoDODTags("res/random/dod/generator/tournament/type_place.txt");
	DOD_GENERATOR_TOURNAMENT_OF_SOMETHING =
		DODParseDODFileIntoDODTags("res/random/dod/generator/tournament/of_something.txt");
	DOD_GENERATOR_TOURNAMENT_AND_SOMETHING =
		DODParseDODFileIntoDODTags("res/random/dod/generator/tournament/and_something.txt");

	/*	TRAIT *********************************************************************************************/
	/*		ACTION ****************************************************************************************/
	/*			INSULT ************************************************************************************/

	DOD_TRAIT_ACTION_INSULT =
		DODParseDODFileIntoDODTags("res/random/dod/trait/action/insult.txt");
	DOD_TRAIT_ACTION_INSULT_1 =
		DODParseDODFileIntoDODTags("res/random/dod/trait/action/insult_1.txt");
	DOD_TRAIT_ACTION_INSULT_2 =
		DODParseDODFileIntoDODTags("res/random/dod/trait/action/insult_2.txt");
}

DODContent::~DODContent() {
	/*	ATTACK ********************************************************************************************/
	/*		SLASH *****************************************************************************************/
	/*			SWORD *************************************************************************************/

	DODFreeDODTag(DOD_ATTACK_SLASH_SWORD);
	DOD_ATTACK_SLASH_SWORD = nullptr;

	/******************************************************************************************************/
	/*	TOURNAMENT GENERATOR ******************************************************************************/
	/******************************************************************************************************/

	DODFreeDODTag(DOD_GENERATOR_TOURNAMENT_ADJECTIVE);
	DOD_GENERATOR_TOURNAMENT_ADJECTIVE = nullptr;
	DODFreeDODTag(DOD_GENERATOR_TOURNAMENT_NOUN);
	DOD_GENERATOR_TOURNAMENT_NOUN = nullptr;
	DODFreeDODTag(DOD_GENERATOR_TOURNAMENT_TYPE_PLACE);
	DOD_GENERATOR_TOURNAMENT_TYPE_PLACE = nullptr;
	DODFreeDODTag(DOD_GENERATOR_TOURNAMENT_OF_SOMETHING);
	DOD_GENERATOR_TOURNAMENT_OF_SOMETHING = nullptr;
	DODFreeDODTag(DOD_GENERATOR_TOURNAMENT_AND_SOMETHING);
	DOD_GENERATOR_TOURNAMENT_AND_SOMETHING = nullptr;

	/*	TRAIT *********************************************************************************************/
	/*		ACTION ****************************************************************************************/
	/*			INSULT ************************************************************************************/

	DODFreeDODTag(DOD_TRAIT_ACTION_INSULT);
	DOD_TRAIT_ACTION_INSULT = nullptr;
	DODFreeDODTag(DOD_TRAIT_ACTION_INSULT_1);
	DOD_TRAIT_ACTION_INSULT_1 = nullptr;
	DODFreeDODTag(DOD_TRAIT_ACTION_INSULT_2);
	DOD_TRAIT_ACTION_INSULT_2 = nullptr;
}