
#ifndef __map_data_HPP__
#define __map_data_HPP__

#include <map>
#include <string>

void initialize_map_data();

extern std::map<const std::string, int> srfParamMap;
extern std::map<const std::string, int> srfTypeMap;
extern std::map<const std::string, int> ormMap;
extern std::map<const std::string, int> rtMap;

#endif
