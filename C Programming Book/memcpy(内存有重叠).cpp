
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;

void* memcpyx(void *dst, const void *src, size_t len)
{
	void *ret = dst;
	if (dst <= src
		|| (char*)dst >= (char*)src + len) {
		while (len--) {
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else {
		src = (char*)src + len - 1;
		dst = (char*)dst + len - 1;
		while (len--) {
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;
		}
	}
	return ret;
}

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	char s[8];
	sprintf(s, "%s", argv[1]);
	memcpyx(s + 6, s, strlen(s));
	printf("%s\n", s);
	return 0;
}




