#ifndef RL_DICTIONARY_OF_DOOM_HPP
#define RL_DICTIONARY_OF_DOOM_HPP

//NOTE: Limited to 128 chars for a line.
//NOTE: Each tag can be 32 chars in length.
//NOTE: Each value of a tag can be 32 chars in length.
//NOTE: All lines must end with an hashtag.

global_variable unsigned int DOD_LINE_SIZE = 128;
global_variable unsigned int DOD_TAG_SIZE = 32;
global_variable unsigned int DOD_VALUE_SIZE = 32;

typedef struct dod_tag {
	char* tag;
	char* value;

	//NOTE: This vairable is allocated dynamically by code, don't allocate in constructor.
	char** content;
	int amountOfContent;
	int maxAmountOfContent;

	//NOTE: If there are sub tags, the father tag sets his subtag as this one, and this subtag sets
	//the nexttag for the following subtags of the father tag.
	dod_tag* subTag;
	dod_tag* fatherTag;
	dod_tag* nextTag;

	bool isDeleted;
} dod_tag;

dod_tag*
DODAllocateDODTag();

void
DODFreeDODTag(dod_tag* dodTag);

void
DODFreeContentDODTag(dod_tag* dodTag);

dod_tag*
DODParseDODFileIntoDODTags(char* path);

dod_tag*
DODParseDODFileIntoDODTags(char* path);

char*
DODGetRandomContent(dod_tag* list, char* tag, char* value, char* subTag = 0, char* subValue = 0);

#endif