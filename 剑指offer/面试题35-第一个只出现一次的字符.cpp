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


int main()
{

	char *str = "abaccdeff";
	cout << firstNotRepeatingChar(str) << endl;
	return 0;
}