#ifndef RL_DOD_CONTENT_HPP
#define RL_DOD_CONTENT_HPP

class DODContent {
public:
	DODContent();
	~DODContent();

	/*	ATTACK ********************************************************************************************/
	/*		SLASH *****************************************************************************************/
	/*			SWORD *************************************************************************************/

	dod_tag* DOD_ATTACK_SLASH_SWORD;

	/******************************************************************************************************/
	/*	TOURNAMENT GENERATOR ******************************************************************************/
	/******************************************************************************************************/

	dod_tag* DOD_GENERATOR_TOURNAMENT_ADJECTIVE;
	dod_tag* DOD_GENERATOR_TOURNAMENT_NOUN;
	dod_tag* DOD_GENERATOR_TOURNAMENT_TYPE_PLACE;
	dod_tag* DOD_GENERATOR_TOURNAMENT_OF_SOMETHING;
	dod_tag* DOD_GENERATOR_TOURNAMENT_AND_SOMETHING;

	/*	TRAIT *********************************************************************************************/
	/*		ACTION ****************************************************************************************/
	/*			INSULT ************************************************************************************/

	dod_tag* DOD_TRAIT_ACTION_INSULT;
	dod_tag* DOD_TRAIT_ACTION_INSULT_1;
	dod_tag* DOD_TRAIT_ACTION_INSULT_2;
};

#endif