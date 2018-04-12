#include <iostream>
#include <algorithm>

using namespace::std;

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

int main()
{
	char result2[90];
	char *s2 = "zglgozozoogle";
	deleteRepeatLetters(s2, result2);
	cout << result2 << endl;

	return 0;
}