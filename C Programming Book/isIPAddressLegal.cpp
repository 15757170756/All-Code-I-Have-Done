/***************************************
IPv6的地址长度为128b，是IPv4地址长度的4倍。
于是IPv4点分十进制格式不再适用，采用十六进制表示。I
Pv6有3种表示方法。
一、冒分十六进制表示法
格式为X:X:X:X:X:X:X:X，其中每个X表示地址中的16b，
以十六进制表示，例如：
ABCD:EF01:2345:6789:ABCD:EF01:2345:6789
这种表示法中，每个X的前导0是可以省略的，例如：
2001:0DB8:0000:0023:0008:0800:200C:417A→ 2001:DB8:0:23:8:800:200C:417A

二、0位压缩表示法
FF01:0:0:0:0:0:0:1101 → FF01::1101
0:0:0:0:0:0:0:1 → ::1
0:0:0:0:0:0:0:0 → ::

三、内嵌IPv4地址表示法
为了实现IPv4-IPv6互通，IPv4地址会嵌入IPv6地址中，
此时地址常表示为：X:X:X:X:X:X:d.d.d.d，
前96b采用冒分十六进制表示，
而最后32b地址则使用IPv4的点分十进制表示，
例如::192.168.0.1与::FFFF:192.168.0.1就是两个典型的例子，
注意在前96b中，压缩0位的方法依旧适用[3]。
****************************************/

//使用正则表达式判断IPV6是否合法
#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
using namespace::std;

// RFC5952 outlines canonical formatting for rendering IPv6 addresses as 
// text. Hex values in an address SHOULD be lowercase.  Addresses can be
// shortened ONCE using the symbol '::'.  Whitespace is actually processed
// as part of the pattern, so use \\s to match whitespace.

int main() {
	std::string ipv6 =
		"(?:"
		// For the first 6 fields, match addresses with no jump (::)...
		"  (?:                                              (?:[0-9a-f]{1,4}:){6}"
		// ...or a jump.
		"  |                                             :: (?:[0-9a-f]{1,4}:){5}"
		"  | (?:                         [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:){4}"
		"  | (?: (?:[0-9a-f]{1,4}:){0,1} [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:){3}"
		"  | (?: (?:[0-9a-f]{1,4}:){0,2} [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:){2}"
		"  | (?: (?:[0-9a-f]{1,4}:){0,3} [0-9a-f]{1,4})? :: (?:[0-9a-f]{1,4}:)   "
		"  | (?: (?:[0-9a-f]{1,4}:){0,4} [0-9a-f]{1,4})? ::                      "
		"  )                                                                     "
		// Match the base10/16 addresses with no jump (suffix of above).
		"  (?: [0-9a-f]{1,4} : [0-9a-f]{1,4}                                     "
		"      | (?: (?: 25[0-5] | 2[0-4][0-9] | [01]?[0-9]?[0-9])\\.){3}        "
		"        (?: (?: 25[0-5] | 2[0-4][0-9] | [01]?[0-9]?[0-9]))              "
		"  )                                                                     "
		// Not any above. Check to see if jump is between last 2 fields of addr.
		"  | (?: (?:[0-9a-f]{1,4}:){0,5} [0-9a-f]{1,4})? :: [0-9a-f]{1,4}        "
		"  | (?: (?:[0-9a-f]{1,4}:){0,6} [0-9a-f]{1,4})? ::                      "
		")";
	// End of ipv6 string pattern.

	// Convert readable pattern above into the applicable regex pattern.
	ipv6.erase(std::remove_if(ipv6.begin(), ipv6.end(), ::isspace), ipv6.cend());

	std::regex ipv6_pattern(ipv6);
	const std::string test = "ipv4 model 127.0.0.1 "
		"live 2001:0db8:0000:0000:0000:ff00:0042:8329 "
		"another 2001:0db8::ff00:0042:8329 "
		"2404:6800:4004:801::2003"
		"zip form ::1 ";
	auto result = std::sregex_iterator(test.cbegin(), test.cend(), ipv6_pattern);
	const auto results_end = std::sregex_iterator();

	if (result != results_end) {
		std::cout << "Found "
			<< std::distance(result, results_end)
			<< " IPv6 address matches.\n";

		while (result != results_end) {
			std::cout << (*result++).str() << '\n';
		}
	}
}















#include <iostream>     
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void split(const string &s, char delim, vector<string> &resultStr);
bool isIPV4Addresslegal(string &IPV4Address);
bool isIPV6Addresslegal(string &IPV6Address);

int main(int argc, char *argv[])
{
	vector<string> ipv4s = { "13.456.34.23", "1.0.0.0", "127.0.0.100",
		"192.168.01.1", "255.255.255.256", "0.0.0" };
	for (int i = 0; i < ipv4s.size(); ++i) {
		bool isIPV4 = isIPV4Addresslegal(ipv4s[i]);
		cout << boolalpha << isIPV4 << noboolalpha << endl;
	}

	return 0;
}

void split(const string &s, char delim, vector<string> &resultStr)
{
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		if (item.length() > 0)
			resultStr.push_back(item);
}

bool isIPV4Addresslegal(string &IPV4Address)
{
	size_t addressLength = IPV4Address.length();
	vector<string> eachPartofAddress;
	char splitElem = '.';
	split(IPV4Address, splitElem, eachPartofAddress);
	if (addressLength != 0 && addressLength <= 15 && eachPartofAddress.size() == 4) {
		size_t counter = 0;
		for (int i = 0; i < eachPartofAddress.size(); ++i) {
			string partOfAddress = eachPartofAddress[i];
			if (partOfAddress[0] == '0' && stoi(partOfAddress) != 0)
				return false;
			else if (stoi(partOfAddress) >= 0 && stoi(partOfAddress) <= 255)
				counter++;
		}
		if (counter == 4)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool isIPV6Addresslegal(string &IPV6Address)
{

	return false;
}