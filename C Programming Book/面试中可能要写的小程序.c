#include <assert.h>

/***************************************
实现库函数strlen
****************************************/
int strlen(const char *str)
{
	assert(str != NULL);
	int len = 0;
	while (*str++ != '\0')
		++len;
	return len;
}

/***************************************
实现库函数strcpy
****************************************/
//得10分，基本上所有的情况，都考虑到了    
//如果有考虑到源目所指区域有重叠的情况，加1分！       
char* strcpy(char* strDest, const char* strSrc)
{
	assert((strDest != NULL) && (strSrc != NULL));
	if (strDest == strSrc) { 
		return strDest; 
	}
	char *address = strDest;
	while ((*strDest++ = *strSrc++) != '\0');
	return address;
}


/***************************************
实现库函数strcmp
****************************************/
int strcmp(const char *s, const char *t)
{
	assert(s != NULL && t != NULL);
	while (*s && *t && *s == *t)
	{
		++s;
		++t;
	}
	return (*s - *t);
}


/***************************************
实现库函数strcat
****************************************/
char *strcat(char *strDes, const char *strSrc)
{
	assert((strDes != NULL) && (strSrc != NULL));
	char *address = strDes;
	while (*strDes != '\0')
		++strDes;
	while ((*strDes++ = *strSrc++) != '\0')
		NULL;
	return address;
}


//多谢laoyi19861011指正    
char *strstr(const char *strSrc, const char *str)
{
	assert(strSrc != NULL && str != NULL);
	const char *s = strSrc;
	const char *t = str;
	for (; *strSrc != '\0'; ++strSrc)
	{
		for (s = strSrc, t = str; *t != '\0' && *s == *t; ++s, ++t)
			NULL;
		if (*t == '\0')
			return (char *)strSrc;
	}
	return NULL;
}

char *strncat(char *strDes, const char *strSrc, unsigned int count)
{
	assert((strDes != NULL) && (strSrc != NULL));
	char *address = strDes;
	while (*strDes != '\0')
		++strDes;
	while (count-- && *strSrc != '\0')
		*strDes++ = *strSrc++;
	*strDes = '\0';
	return address;
}

int strncmp(const char *s, const char *t, unsigned int count)
{
	assert((s != NULL) && (t != NULL));
	while (*s && *t && *s == *t && count--)
	{
		++s;
		++t;
	}
	return (*s - *t);
}



void *memcpy(void *dest, const void *src, unsigned int count)
{
	assert((dest != NULL) && (src != NULL));
	void *address = dest;
	while (count--)
	{
		*(char *)dest = *(char *)src;
		dest = (char *)dest + 1;
		src = (char *)src + 1;
	}
	return address;
}

void *memccpy(void *dest, const void *src, int c, unsigned int count)
{
	assert((dest != NULL) && (src != NULL));
	while (count--)
	{
		*(char *)dest = *(char *)src;
		if (*(char *)src == (char)c)
			return ((char *)dest + 1);
		dest = (char *)dest + 1;
		src = (char *)src + 1;
	}
	return NULL;
}

void *memchr(const void *buf, int c, unsigned int count)
{
	assert(buf != NULL);
	while (count--)
	{
		if (*(char *)buf == c)
			return (void *)buf;
		buf = (char *)buf + 1;
	}
	return NULL;
}

int memcmp(const void *s, const void *t, unsigned int count)
{
	assert((s != NULL) && (t != NULL));
	while (*(char *)s && *(char *)t && *(char *)s == *(char *)t && count--)
	{
		s = (char *)s + 1;
		t = (char *)t + 1;
	}
	return (*(char *)s - *(char *)t);
}

//@big：    
//要处理src和dest有重叠的情况，不是从尾巴开始移动就没问题了。    
//一种情况是dest小于src有重叠，这个时候要从头开始移动，    
//另一种是dest大于src有重叠，这个时候要从尾开始移动。    
void *memmove(void *dest, const void *src, unsigned int count)
{
	assert(dest != NULL && src != NULL);
	char* pdest = (char*)dest;
	char* psrc = (char*)src;

	//pdest在psrc后面，且两者距离小于count时，从尾部开始移动. 其他情况从头部开始移动    
	if (pdest > psrc && pdest - psrc < count)
	{
		while (count--)
		{
			*(pdest + count) = *(psrc + count);
		}
	}
	else
	{
		while (count--)
		{
			*pdest++ = *psrc++;
		}
	}
	return dest;
}

void* memmove(void* dst, const void* src, size_t count)
{
	char* pdst = (char*)dst;
	char* psrc = (char*)src;

	if (pdst < psrc)
		for (size_t i = 0; i < count; ++i)
			*(pdst++) = *(psrc++);
	else {
		pdst += count - 1;
		psrc += count - 1;
		for (size_t i = 0; i < count; ++i)
			*(pdst--) = *(psrc--);
	}
	return dst;
}

void *memset(void *str, int c, unsigned int count)
{
	assert(str != NULL);
	void *s = str;
	while (count--)
	{
		*(char *)s = (char)c;
		s = (char *)s + 1;
	}
	return str;
}

//不对
int atoi(char s[])
{
	assert(s == nullptr);
	int i, n, sign;
	for (i = 0; isspace(s[i]); i++)//跳过空白符;
		sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == ' -')//跳过符号
		i++;
	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');//将数字字符转换成整形数字
	return sign *n;
}





//不对
// A utility function to check whether x is numeric
bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}

// A simple atoi() function. If the given string contains
// any invalid character, then this function returns 0
int myAtoi(char *str)
{
	if (str == NULL)
		return 0;

	int res = 0;  // Initialize result
	int sign = 1;  // Initialize sign as positive
	int i = 0;  // Initialize index of first digit

	// If number is negative, then update sign
	if (str[0] == '-')
	{
		sign = -1;
		i++;  // Also update index of first digit
	}

	// Iterate through all digits of input string and update result
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
			return 0; // You may add some lines to write error message
		// to error stream
		res = res * 10 + str[i] - '0';
	}

	// Return result with sign
	return sign*res;
}







//对头
int atoi3(const char *string)
/* String of ASCII digits, possibly
* preceded by white space.  For bases
* greater than 10, either lower- or
* upper-case digits may be used.
*/
{
	if (string == nullptr)
		return 0;

	register int result = 0;
	register unsigned int digit;
	int sign;

	/*
	* Skip any leading blanks.
	*/
	while (isspace(*string)) {
		string += 1;
	}

	/*
	* Check for a sign.
	*/

	if (*string == '-') {
		sign = 1;
		string += 1;
	}
	else {
		sign = 0;
		if (*string == '+') {
			string += 1;
		}
	}

	for (;; string += 1) {
		digit = *string - '0';
		if (digit > 9) {
			break;
		}
		result = (10 * result) + digit;
	}

	if (sign) {
		return -result;
	}
	return result;
}
