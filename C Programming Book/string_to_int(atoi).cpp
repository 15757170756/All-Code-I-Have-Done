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
