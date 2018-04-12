#include <iostream>
#include <algorithm>

using namespace::std;

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
	char *bianweici1 = "slient";
	char *bianweici2 = "listei";
	cout << boolalpha << isAnagram(bianweici1, bianweici2) << noboolalpha << endl;

	return 0;
}