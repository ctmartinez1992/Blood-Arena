#include "main.hpp"

dod_tag*
DODAllocateDODTag() {
	dod_tag* result = (dod_tag*)calloc(1, sizeof(dod_tag));

	result->tag = (char*)calloc(DOD_TAG_SIZE, sizeof(char));
	result->value = (char*)calloc(DOD_VALUE_SIZE, sizeof(char));

	result->isDeleted = false;

	return(result);
}

void
DODFreeDODTag(dod_tag* dodTag) {
	DODFreeContentDODTag(dodTag);

	if(dodTag->subTag) {
		if(!dodTag->subTag->isDeleted) {
			DODFreeDODTag(dodTag->subTag);
			dodTag->subTag = nullptr;
		}
	}

	if(dodTag->fatherTag) {
		if(!dodTag->fatherTag->isDeleted) {
			DODFreeDODTag(dodTag->fatherTag);
			dodTag->fatherTag = nullptr;
		}
	}

	if(dodTag->nextTag) {
		if(!dodTag->nextTag->isDeleted) {
			DODFreeDODTag(dodTag->nextTag);
			dodTag->nextTag = nullptr;
		}
	}

	free(dodTag);
	dodTag = nullptr;
}

void
DODFreeContentDODTag(dod_tag* dodTag) {
	if(dodTag->tag) {
		free(dodTag->tag);
		dodTag->tag = nullptr;
	}

	if(dodTag->value) {
		free(dodTag->value);
		dodTag->value = nullptr;
	}

	if(dodTag->content) {
		for(int index = 0; index < dodTag->amountOfContent; ++index) {
			if(dodTag->content[index]) {
				free(dodTag->content[index]);
				dodTag->content[index] = nullptr;
			}
		}

		free(dodTag->content);
		dodTag->content = nullptr;
	}

	dodTag->amountOfContent = 0;
	dodTag->maxAmountOfContent = 0;

	dodTag->isDeleted = true;
}

internal_function bool
DODIsTag(char* line) {
	return(line[0] == '!' && line[1] == '!');
}

internal_function dod_tag*
DODGetDODTag(char* line) {
	char* tag = (char*)calloc(DOD_TAG_SIZE, sizeof(char));
	char* value = (char*)calloc(DOD_VALUE_SIZE, sizeof(char));

	char* tagAddress = tag;
	char* valueAddress = value;

	bool foundEqual = false;

	while(*line != '#') {
		if(!foundEqual && *line == '=') {
			foundEqual = true;
			line++;
			continue;
		}

		if(foundEqual) {
			*value = *line;
			value++;
		}
		else {
			*tag = *line;
			tag++;
		}

		line++;
	}

	dod_tag* result = DODAllocateDODTag();

	MemoryCopy(result->tag, tagAddress, DOD_TAG_SIZE);
	MemoryCopy(result->value, valueAddress, DOD_VALUE_SIZE);

	free(tagAddress);
	free(valueAddress);

	return(result);
}

internal_function char*
DODGetRandomValue(char* path, dod_tag* dodTag) {
	return("");
	//TODO:
}

internal_function void
DODRemoveTrailingExcess(char* content) {
	int contentSize = CharPointerLength(content);

	content[contentSize - 2] = 0;
	content[contentSize - 3] = 0;
}

dod_tag*
DODParseDODFileIntoDODTags(char* path) {
	dod_tag* result = nullptr;

	if(path) {
		char* contentLine = (char*)calloc(DOD_LINE_SIZE, sizeof(char));
		char* line = (char*)calloc(DOD_LINE_SIZE, sizeof(char));

		FILE* file = nullptr;

		if(fopen_s(&file, path, "r") == 0) {
			if(fgets(contentLine, DOD_LINE_SIZE, file) != 0) {
				RemovePrecedingTabsFromString(contentLine, line);

				if(DODIsTag(line)) {
					result = DODGetDODTag(line);
				}
			}

			dod_tag* lastFatherTag = result;
			dod_tag* currentDODTag = result;
			int amountOfContentInOneDODTag = 0;

			while(fgets(contentLine, DOD_LINE_SIZE, file) != 0) {
				RemovePrecedingTabsFromString(contentLine, line);

				if(DODIsTag(line)) {
					dod_tag* subOrNextTag = DODGetDODTag(line);

					if(CompareCharPointers(subOrNextTag->tag, currentDODTag->tag)) {
						currentDODTag->nextTag = subOrNextTag;
						currentDODTag->fatherTag = lastFatherTag;
					}
					else if(CompareCharPointers(subOrNextTag->tag, lastFatherTag->tag)) {
						lastFatherTag->nextTag = subOrNextTag;
						subOrNextTag->fatherTag = lastFatherTag->fatherTag;
					}
					else {
						subOrNextTag->fatherTag = currentDODTag;
						lastFatherTag = currentDODTag;
						currentDODTag->subTag = subOrNextTag;
					}

					currentDODTag = subOrNextTag;
					amountOfContentInOneDODTag = 0;
				}
				else {
					currentDODTag->subTag = nullptr;

					if(amountOfContentInOneDODTag == currentDODTag->maxAmountOfContent) {
						currentDODTag->maxAmountOfContent += 10;
						int newContentSize = currentDODTag->maxAmountOfContent * sizeof(char*);
					    char** tmpContent = (char**)realloc(currentDODTag->content, newContentSize);

					    if(tmpContent) {
					        currentDODTag->content = tmpContent;
					    }
					}

					int lineLength = CharPointerLength(line);

					currentDODTag->content[currentDODTag->amountOfContent] = (char*)calloc(lineLength, sizeof(char));
					MemoryCopy(currentDODTag->content[currentDODTag->amountOfContent], line, lineLength);

					currentDODTag->amountOfContent++;
					amountOfContentInOneDODTag++;
				}
			}

			free(contentLine);
			free(line);

			fclose(file);
		}
		else {
			std::cout << "dod, GetValue, file did not open." << std::endl;
		}
	}

	return(result);
}

internal_function char*
DODSearchThroughNextTags(dod_tag* dodTag, char* tag, char* value, char* subTag = 0, char* subValue = 0) {
	if(subTag && subValue) {
		dod_tag* nextDODTag = dodTag;

		while(nextDODTag) {
			if(CompareCharPointers(nextDODTag->tag, tag)) {
				if(CompareCharPointers(nextDODTag->value, value)) {
					char* result = DODSearchThroughNextTags(nextDODTag->subTag, subTag, subValue);

					if(result) {
						return(result);
					}
				}
			}

			nextDODTag = nextDODTag->nextTag;
		}
	}

	while(dodTag) {
		if(CompareCharPointers(dodTag->tag, tag)) {
			if(CompareCharPointers(dodTag->value, value)) {
				if(dodTag->content) {
					//NOTE: Getting the contentSize by subtracting 2, we lose the \n and final \0
					int randomIndex = RandomNumberInRange(0, dodTag->amountOfContent - 1);
					int contentSize = CharPointerLength(dodTag->content[randomIndex]) - 2;

					//NOTE: Copying the content with 1 less of size removes the #.
					char* result = (char*)calloc(contentSize, sizeof(char));
					MemoryCopy(result, dodTag->content[randomIndex], contentSize - 1);

					return(result);
				}
			}
		}

		dodTag = dodTag->nextTag;
	}

	return("");
}

char*
DODGetRandomContent(dod_tag* list, char* tag, char* value, char* subTag, char* subValue) {
	dod_tag* dodTag = list->subTag;
	char* result = "";

	if(dodTag->subTag) {
		result = DODSearchThroughNextTags(dodTag, tag, value, subTag, subValue);
	}
	else if(dodTag->content) {
		result = DODSearchThroughNextTags(dodTag, tag, value);
	}

	return(result);
}