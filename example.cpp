/*

/BUILD: clang++ -std=c++11 example.cpp
/RUN:   ./example

*/

#include <string>
#include <vector>
#include "citizentwice_str.h" 
#include <cassert>

namespace str = citizentwice_str;

int main() {
  // left/right
  assert(str::left("A",0) == "");
  assert(str::left("",0) == "");
  assert(str::left("",1024) == "");
  assert(str::left("A",1) == "A");
  assert(str::left("AB",1) == "A");
  assert(str::left("AB",2) == "AB");
  assert(str::left("AB",400) == "AB");
  assert(str::left("1_______",4) == "1___");
  assert(str::left("1_______",200) == "1_______");
  assert(str::left("1&*$781237812",4) == "1&*$");
  assert(str::left("1&*$781237812",12) == "1&*$78123781");
  assert(str::left("1&*$781237812",13) == "1&*$781237812");
  assert(str::right("A",0) == "");
  assert(str::right("",0) == "");
  assert(str::right("",1024) == "");
  assert(str::right("A",1) == "A");
  assert(str::right("AB",1) == "B");
  assert(str::right("AB",2) == "AB");
  assert(str::right("AB",400) == "AB");
  assert(str::right("_______1",4) == "___1");
  assert(str::right("_______1",200) == "_______1");
  assert(str::right("1&*$781237812",4) == "7812");
  assert(str::right("1&*$781237812",12) == "&*$781237812");
  assert(str::right("1&*$781237812",13) == "1&*$781237812");
  // ends/starts with
  assert(str::starts_with("FILE.TXT","FILE."));
  assert(str::starts_with("a","a"));
  assert(str::starts_with("az","a"));
  assert(str::starts_with("Ok!!!!","Ok!"));  
  assert(str::starts_with("",""));  
  assert(str::starts_with("A",""));  
  assert(str::ends_with("FILE.TXT",".TXT"));
  assert(str::ends_with("a","a"));
  assert(str::ends_with("az","z"));
  assert(str::ends_with("Ok!!!!","!!!"));  
  assert(str::ends_with("",""));  
  assert(str::ends_with("A",""));  
  // substring before/after with
  assert(str::substring_before("FILE.TXT",".") == "FILE");
  assert(str::substring_before("FILE.TXT","$$$") == "");
  assert(str::substring_before("FILE.TXT","ILE.TXT") == "F");
  assert(str::substring_before("","X") == "");
  assert(str::substring_before("X","") == "X");
  assert(str::substring_before("","") == "");
  assert(str::substring_after("FILE.TXT",".") == "TXT");
  assert(str::substring_after("FILE.TXT","$$$") == "");
  assert(str::substring_after("FILE.TXT","FILE.TX") == "T");
  assert(str::substring_after("","X") == "");
  assert(str::substring_after("X","") == "X");
  assert(str::substring_after("","") == "");
  // trim
  assert(str::trim(" \t\r\nZ \t\r\n") == "Z");
  assert(str::trim("") == "");
  assert(str::trim(" ") == "");
  assert(str::trim("Ek`'L<,xLxc4(e$3p|1{>tRyUie") == "Ek`'L<,xLxc4(e$3p|1{>tRyUie");
  assert(str::ltrim("Z \t\r\n") == "Z \t\r\n");
  assert(str::rtrim(" \t\r\nZ") == " \t\r\nZ");
  // upper/lower case conversion
  assert(str::to_upper("a") == "A");
  assert(str::to_upper("a#.$z") == "A#.$Z");
  assert(str::to_upper("_naMe123") == "_NAME123");
  assert(str::to_upper("_u#)Bn%#uJLFWoMbb9M*'IUB%rmqL6zr") == "_U#)BN%#UJLFWOMBB9M*'IUB%RMQL6ZR");
  assert(str::to_upper("") == "");
  assert(str::to_lower("A") == "a");
  assert(str::to_lower("A#.$Z") == "a#.$z");
  assert(str::to_lower("_NaMe123") == "_name123");
  assert(str::to_lower("_U#)BN%#UJLFWOMBB9M*'IUB%RMQL6ZR") == "_u#)bn%#ujlfwombb9m*'iub%rmql6zr");
  assert(str::to_lower("") == "");
  // split
  assert(str::split("A,B,C",",") == (std::vector<std::string> {"A","B","C"}) );
  assert(str::split("ABC",",")[0] == "ABC");
  assert(str::split("ABC","")[0] == "ABC");
  // join
  assert(str::join((std::vector<std::string> {"A","B","C"}),",") == "A,B,C");
  assert(str::join((std::vector<std::string> {"A","B","C"}),"") == "ABC");
  assert(str::join((std::vector<std::string> {"A"}),"...") == "A");
  assert(str::join((std::vector<std::string> {"A","Z"}),"...") == "A...Z");
  assert(str::join((std::vector<std::string> {}),",") == "");
  // regex match yes/no
  assert(str::re_does_match("NAD.DP.[0-9]{13}::9", "NAD+DP+4200112233445::9")); // ship-to
  // regex get capture #1 - (cmd line)
  assert(str::re_get_match("--input-file=([^\\s]+)","--input-file=Nice_Name_Without_spaces.txt")  // cmd-line
    == "Nice_Name_Without_spaces.txt");
  assert(str::re_get_match("([0-9]+(\\.[0-9]+){0,1}).*", "1231.2412-b+c") == "1231.2412");
  assert(str::re_get_match("([0-9]+(\\.[0-9]+){0,1}).*", "8997433 * Z + q") == "8997433");
  // replace
  assert(str::replace_all("a", "a", "b")  == "b");
  assert(str::replace_alli("a", "A", "b")  == "b");
  assert(str::replace_all("", "a", "b")  == "");
  assert(str::replace_alli("", "A", "b")  == "");
  assert(str::replace_all("Z", "a", "b")  == "Z");
  assert(str::replace_alli("Z", "A", "b")  == "Z");
  assert(str::replace_all("Z", "", "b")  == "Z");
  assert(str::replace_alli("Z", "", "b")  == "Z");
  assert(str::replace_all("aZa", "a", "b")  == "bZb");
  assert(str::replace_alli("aZa", "A", "b")  == "bZb");
  assert(str::replace_all("aZa", "a", "")  == "Z");
  assert(str::replace_alli("aZa", "A", "")  == "Z");
  assert(str::replace_all("I twice presented him a kingly crown, which he did twice refuse.", "twice", "thrice") 
    == "I thrice presented him a kingly crown, which he did thrice refuse.");
  assert(str::replace_alli("I Twice presented him a kingly crown, which he did twiCe refuse.", "TWICe", "thrice")   
    == "I thrice presented him a kingly crown, which he did thrice refuse.");
  return 0;
}