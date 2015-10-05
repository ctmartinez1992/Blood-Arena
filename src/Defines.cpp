#include "main.hpp"

bool
IsPointAdjacentToPoint(p2i p1, p2i p2) {
	if(p1.x == p2.x && p1.y == p2.y) {
		return(true);
	}

	if(p1.x == p2.x && (p2.y - p1.y) == 1) {
		return(true);
	}
	if((p2.x - p1.x) == 1 && (p2.y - p1.y) == 1) {
		return(true);
	}
	if((p2.x - p1.x) == 1 && p1.y == p2.y) {
		return(true);
	}
	if((p2.x - p1.x) == 1 && (p1.y - p2.y == 1)) {
		return(true);
	}

	if(p1.x == p2.x && (p1.y - p2.y) == 1) {
		return(true);
	}
	if((p1.x - p2.x) == 1 && (p1.y - p2.y) == 1) {
		return(true);
	}
	if((p1.x - p2.x) == 1 && p1.y == p2.y) {
		return(true);
	}
	if((p1.x - p2.x) == 1 && (p2.y - p1.y == 1)) {
		return(true);
	}

	return(false);
}

int
Minimum(int n1, int n2) {
	if(n1 <= n2) {
		return(n1);
	}
	else {
		return(n2);
	}
}

int
Maximum(int n1, int n2) {
	if(n1 <= n2) {
		return(n2);
	}
	else {
		return(n1);
	}
}

size_t
CharPointerLength(char* string) {
	size_t length = 0;

	while(*string++ != '\0') {
		++length;
	}

	return(++length);
}

void
ConcatenateCharPointers(size_t srcACount, char* srcA,
						size_t srcBCount, char* srcB,
						size_t dstCount, char* dst)
{
	Assert(*srcA && *srcB);
	Assert(srcACount + srcBCount <= dstCount);

	for(size_t i = 0; i < srcACount; ++i) {
		*dst++ = *srcA++;
	}

	for(size_t i = 0; i < srcBCount; ++i) {
		*dst++ = *srcB++;
	}

	*dst++ = 0;
}

char*
ConcatenateCharPointers(char* dst, char* src) {
	int i = 0;

	while(dst[i] != '\0') {
		i++;
	}

	while(*src != '\0') {
		dst[i++] = *src++;
	}

	dst[i] = '\0';

	return(dst);
}

char*
ToString(char* text, ...) {
	va_list ap;
	char* buffer = (char*)calloc(256, sizeof(char));

	va_start(ap, text);
	vsprintf_s(buffer, 256, text, ap);
	va_end(ap);

	int resultSize = CharPointerLength(buffer);
	char* result = (char*)calloc(resultSize, sizeof(char));

	MemoryCopy(result, buffer, resultSize);

	free(buffer);

	return(result);
}

void
RemoveTrailingNewLineFromString(char* string) {
	int stringSize = CharPointerLength(string);

	string[stringSize - 2] = '\0';
}

void
RemovePrecedingTabsFromString(char* stringSrc, char* stringDst) {
	int stringSize = CharPointerLength(stringSrc);
	int index = 0;
	int resultIndex = 0;

	while(index < stringSize) {
		if(stringSrc[index] != '\t') {
			stringDst[resultIndex++] = stringSrc[index];
		}

		index++;
	}
}

bool
CompareCharPointers(char* s1, char* s2) {
	size_t s1Length = CharPointerLength(s1);
	size_t s2Length = CharPointerLength(s2);

	if(s1Length != s2Length) {
		return(false);
	}

	for(size_t i = 0; i < s1Length; ++i) {
		if(s1[i] != s2[i]) {
			return(false);
		}
	}

	return(true);
}

char*
FindCharInString(char* string, char c) {
	while (*string && *string != c) {
		++string;
	}

	return(string);
}

char
CharToUpperCase(char c1) {
	char c2;

	c2 = (c1 >= 'a' && c1 <= 'z') ? ('A' + c1 - 'a') : c1;

	return(c2);
}

char*
DecideIndefiniteArticle(char* word) {
	char first = word[0];
	char second = word[1];

	if(first == 'a' || first == 'A' ||
	   first == 'e' || first == 'E' ||
	   first == 'i' || first == 'I' ||
	   first == 'o' || first == 'O' ||
	   first == 'u' || first == 'U' ||
	   (first == 'h' && second == 'u') || (first == 'H' && second == 'U'))
	{
		return("an");
	}
	else {
		return("a");
	}
}

int
CountLinesInFile(char* path) {
	FILE* file;
	fopen_s(&file, path, "r");

    int ch;
    int count = 0;

    do {
		ch = fgetc(file);
		
		if(ch == '\n' || ch == EOF) {
			count++;
		}
   } while(ch != EOF);    

   return(count);
}

char*
ReadLineFromFileByRandomIndex(char* path) {
	if(path) {
		char* result = (char*)calloc(25, sizeof(char));

		int linesInFile = CountLinesInFile(path);
		int randomIndex = RandomNumberInRange(1, linesInFile);

		FILE* file;
		fopen_s(&file, path, "r");

		int count = 1;

		while (++count < randomIndex) {
			fgets(result, 25, file);
		}

		fgets(result, 25, file);

		fclose(file);

		return(result);
	}

	return("");
}

void
MergeTwoFiles(char* path1, char* path2) {
	if(path1 && path2) {
		FILE* filew;
		fopen_s(&filew, "res/random/s.txt", "w");

		FILE* filer1;
		fopen_s(&filer1, path1, "r");
		FILE* filer2;
		fopen_s(&filer2, path2, "r");

		char* r1 = (char*)calloc(25, sizeof(char));
		char* r2 = (char*)calloc(25, sizeof(char));

		int count1 = 1;
		int count2 = 1;

		while(count1++ < 154) {
			fgets(r1, 25, filer1);
			RemoveTrailingNewLineFromString(r1);

			while(count2++ < 154) {
				fgets(r2, 25, filer2);
				fputs(ToString("%s %s", r1, r2), filew);
			}

			count2 = 1;

			fclose(filer2);
			fopen_s(&filer2, path2, "r");
		}

		fclose(filer1);
		fclose(filer2);
		fclose(filew);
	}
}

//TODO: use char*
void
Split(std::string& s, char delim, std::vector<std::string>* elems) {
	std::stringstream ss(s);
	std::string item;

	while(std::getline(ss, item, delim)) {
		elems->push_back(item);
	}
}

//TODO: use char*
void
ReadFileToString(std::string path, std::string* text) {
	std::string line = "";
	std::ifstream storyFile(path);

	if(storyFile.is_open()) {
		while(getline(storyFile, line)) {
			*text += line;
		}

		storyFile.close();
	}
}

unsigned int
SafeTruncateUInt64(unsigned long long value) {
	Assert(value <= 0xFFFFFFFF);

	unsigned int result = (unsigned int)value;

	return(result);
}

char*
UnsignedIntToCharPointer(unsigned int x) {
	unsigned int n = Log10(x) + 1;
	char* nArray = (char*)calloc(n + 1, sizeof(char));

	for(unsigned int i = 0; i < n; ++i, n /= 10) {
		nArray[i] = (x % 10) + '0';
	}

	return(nArray);
}

char*
LongLongToCharPointer(long long value, char* string, int radix) {
	int i;
	int size;
	int sign;
	char* sp;
	char tmp[65];
	char* tp = tmp;
	unsigned long long v;

	if(radix > 36 || radix <= 1) {
		return(0);
	}

	if(radix == 10 && value < 0LL) {
		sign = 1;
		v = -value;
	}
	else {
		sign = 0;
		v = (unsigned long long)value;
	}

	size = 0;

	while(v || tp == tmp) {
		i = v % (long long)radix;
		v = v / (long long)radix;

		if(i < 10) {
			*tp++ = (char)(i + '0');
		}
		else {
			*tp++ = (char)(i - 10 + 'a');
		}

		size++;
	}

	if(!string) {
		string = (char*)malloc(size);

		if(!string) {
			return(0);
		}
	}

	sp = string;

	if(sign) {
		*sp++ = '-';
	}

	while(tp > tmp) {
		*sp++ = *--tp;
	}

	*sp = '\0';

	return(string);
}

char*
FloatToCharPointer(float value) {
	char* result = (char*)calloc(15, sizeof(char));
	sprintf_s(result, 15, "%.1f", value);

	return(result);
}

unsigned int
Log10(unsigned int n) {
    return(n >= 1000000000u) ? 9 : (n >= 100000000u) ? 8 :
		  (n >= 10000000u) ? 7 : (n >= 1000000u) ? 6 :
		  (n >= 100000u) ? 5 : (n >= 10000u) ? 4 :
		  (n >= 1000u) ? 3 : (n >= 100u) ? 2 : (n >= 10u) ? 1u : 0u;
}

int
CountDigitsInInteger(int number) {
	if(number < 0) number = (number == INT_MIN) ? INT_MAX : -number;
	if(number > 999999999) return(10);
	if(number > 99999999) return(9);
	if(number > 9999999) return(8);
	if(number > 999999) return(7);
	if(number > 99999) return(6);
	if(number > 9999) return(5);
	if(number > 999) return(4);
	if(number > 99) return(3);
	if(number > 9) return(2);
	return(1);
}

bool
CheckRectangleOverlap(int x11, int y11, int x12, int y12,
					  int x21, int y21, int x22, int y22)
{
	return(x11 < x22 && x12 > x21 &&
		   y11 < y22 && y12 > y21);
}