#ifndef RL_DEFINES_HPP
#define RL_DEFINES_HPP

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
//TODO: Remove this once you std::strings from defines.cpp
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

//Internal to the file
#define internal_function static

//Variable persists inside a scope
#define local_persist static

//The variable is global and can be acessed anywhere
#define global_variable static

#define Pi32 3.14159265359f

//Assert
//TODO: Complete assertion macro.
#define Assert(Expression) if(!(Expression)) { *(int *)(0) = (0); }

//From bytes to ...
#define Kilobytes(Value) ((Value) * 1024LL)
#define Megabytes(Value) (Kilobytes(Value) * 1024LL)
#define Gigabytes(Value) (Megabytes(Value) * 1024LL)
#define Terabytes(Value) (Gigabytes(Value) * 1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

//MARK: Generic structs.
typedef struct p2i {
	int x;
	int y;

	bool operator==(p2i& other) {
		return (x == other.x && y == other.y);
	}
} p2i;

//MARK: Generic functions that serve various purposes.
//TODO: This function is garbage, do it in a math way.
bool
IsPointAdjacentToPoint(int p1x, int p1y, int p2x, int p2y);

float inline __fastcall
FastSqrtf(float n) {
	_asm fld n
	_asm fsqrt
	_asm fst n
}

int inline __fastcall
FastRoundf(float n) {
	float round_to_nearest = 0.5f;
	int i;

	__asm {
		fld n
			fadd st, st(0)
			fadd round_to_nearest
			fistp i
			sar i, 1
	}

	return(i);
}

int inline
Floorf(float n) {
	return int(n + 65536.) - 65536;
}
 
int inline
Ceilf(float n) {
	return 65536 - int(65536. - n);
}

template<typename T>
void
CleanPointer(T* p) {
	if(p) {
		delete p;
		p = nullptr;
	}
}

template<typename T>
void
CleanPointerArray(T* p) {
	if(p) {
		delete[] p;
		p = nullptr;
	}
}

void inline
MemoryCopy(void* dst, void* src, size_t size) {
	char* charSrc = (char*)src;
	char* charDst = (char*)dst;

	char* tmp = (char*)calloc(size, sizeof(char));

	for (size_t i = 0; i < size; ++i) {
		tmp[i] = charSrc[i];
	}

	for (size_t i = 0; i < size; ++i) {
		charDst[i] = tmp[i];
	}

	free(tmp);
}

int
Minimum(int n1, int n2);

int
Maximum(int n1, int n2);

//NOTE: Must '\0' terminated. The '\0' also counts.
size_t
CharPointerLength(char* string);

//NOTE: Must '\0' terminated.
void
ConcatenateCharPointers(size_t srcACount, char* srcA,
						size_t srcBCount, char* srcB,
						size_t dstCount, char* dst);

//NOTE: Must '\0' terminated.
char*
ConcatenateCharPointers(char* dst, char* src);

//NOTE: Limited to 256 chars.
char*
ToString(char* text, ...);

void
RemoveTrailingNewLineFromString(char* string);

//NOTE: Returns the new string. Does not delete the given string.
void
RemovePrecedingTabsFromString(char* stringSrc, char* stringDst);

//NOTE: Must '\0' terminated. Returns true if they're equal.
bool
CompareCharPointers(char* s1, char* s2);

char*
FindCharInString(char* string, char c);

char
CharToUpperCase(char c1);

char*
DecideIndefiniteArticle(char* word);

//TODO: Make sure file is valid.
int
CountLinesInFile(char* path);

//TODO: Make sure file is valid.
char*
ReadLineFromFileByRandomIndex(char* path);

//TODO: Remove, or make it that it works universally.
void
MergeTwoFiles(char* path1, char* path2);

void
Split(std::string& s, char delim, std::vector<std::string>* elems);

void
ReadFileToString(std::string path, std::string* text);

unsigned int
SafeTruncateUInt64(unsigned long long value);

char*
UnsignedIntToCharPointer(unsigned int n);

char*
LongLongToCharPointer(long long value, char* string, int radix);

char*
FloatToCharPointer(float value);

unsigned int
Log10(unsigned int n);

int
CountDigitsInInteger(int number);

int inline
RandomNumberInRange(int min, int max) {
	int r = 0;
	int range = 1 + max - min;
	int buckets = RAND_MAX / range;
	int limit = buckets * range;

	int d = RAND_MAX;

	do {
		r = rand();
	} while (r >= limit);

	return(min + (r / buckets));
}

bool inline
PercentageChance(int percentage) {
	return((RandomNumberInRange(0, 99) + 1) <= percentage);
}

bool
CheckRectangleOverlap(int x11, int y11, int x12, int y12,
					  int x21, int y21, int x22, int y22);

#endif