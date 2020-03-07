/*

C++ string util lib by Luigi Galli - citizentwice.nl

USED WITH PERMISSION OF THE AUTHOR

*/

#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <regex>
#include <type_traits>
#include <array>
#include <cassert>

namespace luigig_toolkit { 

	std::string to_lower(const char *s) {
		std::string _s{s};
		std::transform(_s.begin(), _s.end(), _s.begin(), ::tolower); 
		return _s;
	}

	std::string to_upper(const char *s) {
		std::string _s{s};
		std::transform(_s.begin(), _s.end(), _s.begin(), ::toupper);
		return _s;
	}

//  std::string to_lower(const char*s) {
//    std::string _s{s};
//    std::transform(_s.begin(), _s.end(), _s.begin(), ::tolower); 
//    return _s;
//  }
//
//  std::string to_upper(const char *s) {
//    std::string _s{s};
//    std::transform(_s.begin(), _s.end(), _s.begin(), ::toupper);
//    return _s;
//  } 

	
	std::vector<std::string> split(const std::string& s1, const std::string& s2 ) {
		std::vector<std::string> retval{};
		auto p = s1.find(s2);
		if (p == std::string::npos || s2.length() == 0 || s1.length() == 0) return retval;
		auto ip = s1.begin();
		while (p != -1 && ip < s1.end()) {
			retval.push_back(std::string{ip, s1.begin() + p});
			ip = s1.begin() + (p + s2.length());
			p = s1.find(s2, p+s2.length());
			if (p == std::string::npos ) break;
		}
		retval.push_back(std::string{ip, s1.end()});
		return retval;
	}
	
	std::string substring_before(const std::string& s, const std::string& lookfor) {
		auto p = s.find(lookfor);
		if (p == std::string::npos || s.length() == 0 || lookfor.length() == 0) return s;
		return std::string{s.begin(), s.begin() + p};
	}

	std::string substring_after(const std::string& s, const std::string& lookfor) {
		auto p = s.find(lookfor);
		if (p == std::string::npos || s.length() == 0 || lookfor.length() == 0) return s;
		return std::string{s.begin() + p + lookfor.length(), s.end()};
	}

	std::string ltrim(const std::string& s) {
		std::array<char,4> w{' ', 9, 10, 13};
		std::string delims{w.begin(),w.end()};
		auto p = s.find_first_not_of(delims);
		if (p == std::string::npos) {
			if (s.find_first_of(delims) != std::string::npos) {return {};}
			else {return s;}
		}
		return std::string{s.begin() + p, s.end()};
	}

	std::string rtrim(const std::string& s) {
		std::array<char,4> w{' ', 9, 10, 13};
		std::string delims{w.begin(),w.end()};
		auto p = s.find_last_not_of(delims);
		if (p == std::string::npos) {
			if (s.find_first_of(delims) != std::string::npos) {return {};}
			else {return s;}
		}
		return std::string{s.begin(), s.begin() + p + 1};
	}

	std::string trim(const std::string& s) {
		return ltrim(rtrim(s));
	}

	std::string left(const std::string& s, size_t chars) {
		if (chars >= s.length()) return s;
		return std::string{s.begin(), s.begin() + chars};
	}

	std::string right(const std::string& s, size_t chars) {
		if (chars >= s.length()) return s;
		return std::string{s.end() - chars, s.end()};
	}

	std::string replace_all(const std::string& str, const std::string& lookfor, const char* replwith) {
		std::string retval{};
		auto p = str.find(lookfor);
		if (p == std::string::npos || str.length() == 0 || lookfor.length() == 0) return str;
		auto ip = str.begin();
		while (p != -1 && ip < str.end()) {
			retval += (std::string{ip, str.begin() + p} + replwith);
			ip = str.begin() + (p + lookfor.length());
			p = str.find(lookfor, p+lookfor.length());
			if (p == std::string::npos ) break;
		}
		retval += std::string{ip, str.end()};
		return retval;
	}

	std::string replace_alli(const std::string& str, const std::string& lookfor, const char* replwith) {
		std::string retval{};
		std::string ustr{to_upper(str.c_str())}, ulookfor{to_upper(lookfor.c_str())};
		auto p = ustr.find(ulookfor);
		if (p == std::string::npos || str.length() == 0 || lookfor.length() == 0) return retval;
		auto ip = str.begin();
		while (p != -1 && ip < str.end()) {
			retval += (std::string{ip, str.begin() + p} + replwith);
			ip = str.begin() + (p + lookfor.length());
			p = ustr.find(ulookfor, p+ulookfor.length());
			if (p == std::string::npos ) break;
		}
		retval += std::string{ip, str.end()};
		return retval;
	}

	std::string join(const std::vector<std::string>& v, const std::string& s2 = "" ) {
		std::string retval{};
		if (v.empty()) return retval;
		for (auto i = v.begin(); i != (v.end() - 1) ; ++i) {
			retval += (*i + s2);
		}
		retval += *(v.end() - 1);
		return retval;
	}
	 
	std::string re_get_match(const char* re, const char* txt) { // const {
		if (re == nullptr || txt == nullptr) return "";
		std::string _re{re}, _txt{txt};
		if (_re.empty() || _txt.empty()) return "";
		std::regex _regex(_re);
		std::smatch _match;
		if (std::regex_match(_txt, _match, _regex)) {
			if (_match.size() >= 2) {
				return (_match[1]).str();
			}
		}
		return "";
	}

	std::string re_get_match(const std::string& re, const std::string& txt)  {
		return re_get_match(re.c_str(), txt.c_str());
	}

	bool starts_with(const char* str, const char* prefix) {
    if (str == nullptr || prefix == nullptr) { return false };
		while (*str && *prefix (*str == *prefix)) {
			str++;
			prefix++;
		}
		return (*prefix == 0);
	}

	bool ends_with(const char* str, const char* suffix) {
    if (str == nullptr || suffix == nullptr) { return false };
    auto bstr = str + stlren(str);
    auto bsuf = suffix + strlen(suffix);
    while ((bstr != str) && (bsuf != suffix) && (*bsuf == *bstr)) {
      bstr--;
      bsuf--;
    }
    return ((bsuf == suffix) && (*bstr == *bsuf) )
	}

	bool re_does_match(const char* re, const char* txt)  {
		if (re == nullptr || txt == nullptr) return "";
		std::string _re{re}, _txt{txt};
		if (_re.empty() || _txt.empty()) return "";
		std::regex _regex(_re);
		std::smatch _match;
		return std::regex_match(_txt, _match, _regex);
	}

	bool re_does_match(const std::string& re, const std::string& txt)  {
		return re_does_match(re.c_str(), txt.c_str());
	}

}

//// int test() {
//int main() {
//	std::string s = "WTF<br/>SERIOUSLY<br/>WTF!";	
//	// auto v = luigig_toolkit::split(s, "");
//	auto v = luigig_toolkit::split(s, "<br/>");
//	for (const auto& vs : v) {
//		std::cout << vs << std::endl;
//	}
//	std::cout << luigig_toolkit::join(v, " - ") << std::endl;
//	std::cout << luigig_toolkit::join(std::vector<std::string>{"A","B","C"}, " - ") << std::endl;
//	std::cout << "test of split/join..." ;
//	assert((luigig_toolkit::join(luigig_toolkit::split(s, "<br/>"), "<br/>")) == s ) ;
//	std::cout << "passed\n\n" ;
//	std::cout << "------------------------------\n" ;
//    auto rawname = "the filename URL is file://users/lg/temp/bla.txt ok?";
//	std::cout << "getting URL from <" << rawname << ">\n";
//	std::cout << luigig_toolkit::re_get_match(".*(file://[^ ]+).*", rawname) << std::endl; 
//	std::cout << "------------------------------\n" ;
//	std::cout << luigig_toolkit::replace_all("i twice presented him a kingly crown, which he did twice refuse.", "twice", "thrice") << std::endl; 
//	std::cout << luigig_toolkit::replace_alli("i Twice presented him a kingly crown, which he did twiCe refuse.", "TWICe", "thrice") << std::endl; 
//	std::cout << "------------------------------\n" ;
//	{
//		char _c = 'c', _b='B';
//		std::cout << _c << " & " << _b << " or " << luigig_toolkit::to_upper(_c) << " & " << luigig_toolkit::to_lower(_b) << "\n";
//		std::cout << "------------------------------\n" ;
//		std::cout << std::endl; 
//	}
//	{
//		std::string _c = "c", _b="B";
//		std::cout << _c << " & " << _b << " or " << luigig_toolkit::to_upper(_c) << " & " << luigig_toolkit::to_lower(_b) << "\n";
//		std::cout << "------------------------------\n" ;
//		std::cout << std::endl; 
//	}
//	{
//		std::string _w{"WHAT THE HELL"};
//		std::cout << "<" << luigig_toolkit::left(_w, 4) << "> & <" << luigig_toolkit::right(_w, 4) << ">\n";
//		std::cout << "------------------------------\n" ;
//		std::cout << std::endl; 
//	}
//	{
//		std::cout << "Regex match test = " << luigig_toolkit::re_does_match("([0-9]+(\\.[0-9]+){0,1}).*", "12312.412-b")  << "\n";
//		std::cout << "Regex match test = " << luigig_toolkit::re_get_match("([0-9]+(\\.[0-9]+){0,1}).*", "1231.2412-b")  << "\n";
//		std::cout << "------------------------------\n" ;
//		std::cout << std::endl; 
//	}
//	{
//		std::string a{"a+b = c+d"};
//		std::cout << "Substring of " <<a << " before '=' " << luigig_toolkit::substring_before(a, "=") << "\n";
//		std::cout << "Substring of " <<a << " after  '=' " << luigig_toolkit::substring_after(a, "=") << "\n";
//		std::cout << "------------------------------\n" ;
//		std::cout << std::endl; 
//	}
//	{
//		std::string a{"          SOME TEXT  \t\t\t\n"};
//		std::cout << "Trimmed text <" << luigig_toolkit::ltrim(luigig_toolkit::rtrim(a)) <<  ">\n";
//		std::cout << "------------------------------\n" ;
//		std::cout << std::endl; 
//	}
//	return 0;
//}