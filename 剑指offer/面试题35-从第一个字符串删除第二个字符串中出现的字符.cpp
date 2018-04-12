#include <iostream>
#include <algorithm>

using namespace::std;

void deleteLetters(const char *srcStr, const char *s2, char *result)
{
	const int hashSize = 256;
	unsigned int hashTable[hashSize];
	memset(hashTable, 0, sizeof(hashTable));
	for (char *p = const_cast<char*>(s2); *p != '\0'; ++p)
		++hashTable[*p];
	int j, i;
	for (i = 0, j = 0; i < strlen(srcStr); ++i) {
		if (hashTable[srcStr[i]] == 0)
			result[j++] = srcStr[i];
	}
	result[j] = '\0';
}

char* deleteLetters(const char *srcStr, const char *s2)
{
	char *result = new char[90];
	const int hashSize = 256;
	unsigned int hashTable[hashSize];
	memset(hashTable, 0, sizeof(hashTable));
	for (char *p = const_cast<char*>(s2); *p != '\0'; ++p)
		++hashTable[*p];
	int j, i;
	for (i = 0, j = 0; i < strlen(srcStr); ++i) {
		if (hashTable[srcStr[i]] == 0)
			result[j++] = srcStr[i];
	}
	result[j] = '\0';

	return result;
}

int main()
{

	char *srcStr = "We are students";
	char *toBeDelete = "aeiou";
	char result[90];
	deleteLetters(srcStr, toBeDelete, result);
	cout << result << endl;

	cout << deleteLetters(srcStr, toBeDelete) << endl;

	return 0;
}