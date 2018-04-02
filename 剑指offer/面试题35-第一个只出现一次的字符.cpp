#include <iostream>
#include <algorithm>

using namespace::std;

char firstNotRepeatingChar(char *str)
{
	if (str == nullptr)
		return '\0';
	const int tableSize = 256;
	unsigned int hashTable[tableSize];
	memset(hashTable, 0, sizeof(hashTable));
	for (char *pHashKey = str; *pHashKey != '\0'; ++pHashKey)
		hashTable[*pHashKey]++;

	for (char *pHashKey = str; *pHashKey != '\0'; ++pHashKey)
		if (hashTable[*pHashKey] == 1)
			return *pHashKey;

	return '\0';
}

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

void deleteRepeatLetters(const char *srcStr, char* result)
{
	const int hashSize = 256;
	bool hashTable[hashSize];
	memset(hashTable, false, sizeof(hashTable));
	hashTable[srcStr[0]] = true;
	result[0] = srcStr[0];
	int i, j;
	for (i = 1, j = 1; i < strlen(srcStr); ++i) {
		if (hashTable[srcStr[i]] == false)
			result[j++] = srcStr[i];
		hashTable[srcStr[i]] = true;
	}
	result[j] = '\0';
}

bool isAnagram(char *s1, char *s2)
{
	const int hashSize = 256;
	unsigned int hashTable[hashSize];
	memset(hashTable, false, sizeof(hashTable));
	for (char *p = s1; *p != '\0'; ++p)
		++hashTable[*p];
	for (char *p = s2; *p != '\0'; ++p)
		--hashTable[*p];

	for (int i = 0; i < hashSize; ++i)
		if (hashTable[i] != 0)
			return false;
	return true;
}


int main()
{

	char *str = "abaccdeff";
	cout << firstNotRepeatingChar(str) << endl;
	char *srcStr = "We are students";
	char *toBeDelete = "aeiou";
	char result[90];
	deleteLetters(srcStr, toBeDelete, result);
	cout << result << endl;

	cout << deleteLetters(srcStr, str) << endl;

	char result2[90];
	char *s2 = "zglgozozoogle";
	deleteRepeatLetters(s2, result2);
	cout << result2 << endl;

	char *bianweici1 = "slient";
	char *bianweici2 = "listei";
	cout << boolalpha << isAnagram(bianweici1, bianweici2) << noboolalpha << endl;

	return 0;
}