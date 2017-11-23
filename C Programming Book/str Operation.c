/***************************************
ʵ�ֿ⺯��strlen
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
ʵ�ֿ⺯��strcpy
****************************************/
//��10�֣����������е�����������ǵ���    
//����п��ǵ�ԴĿ��ָ�������ص����������1�֣�       
char* strcpy(char* strDest, const char* strSrc)
{
	assert((strDest != NULL) && (strSrc != NULL));
	if (strDest == strSrc) { return strDest; }
	char *address = strDest;
	while ((*strDest++ = *strSrc++) != '\0');
	return address;
}


/***************************************
ʵ�ֿ⺯��strcmp
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
ʵ�ֿ⺯��strcat
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


//��лlaoyi19861011ָ��    
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

//@big��    
//Ҫ����src��dest���ص�����������Ǵ�β�Ϳ�ʼ�ƶ���û�����ˡ�    
//һ�������destС��src���ص������ʱ��Ҫ��ͷ��ʼ�ƶ���    
//��һ����dest����src���ص������ʱ��Ҫ��β��ʼ�ƶ���    
void *memmove(void *dest, const void *src, unsigned int count)
{
	assert(dest != NULL && src != NULL);
	char* pdest = (char*)dest;
	char* psrc = (char*)src;

	//pdest��psrc���棬�����߾���С��countʱ����β����ʼ�ƶ�. ���������ͷ����ʼ�ƶ�    
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