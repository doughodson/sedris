
#ifndef __map_data_HPP__
#define __map_data_HPP__

#include <map>
#include <cstring>

void initialize_map_data();

struct strCmp {
   bool operator()(const char* s1, const char* s2) const {
      return std::strcmp(s1, s2) < 0;
   }
};

extern std::map<const char*, int, strCmp> srfParamMap;
extern std::map<const char*, int, strCmp> srfTypeMap;
extern std::map<const char*, int, strCmp> ormMap;
extern std::map<const char*, int, strCmp> rtMap;


#endif
