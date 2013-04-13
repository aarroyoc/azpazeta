#ifndef AZPMAP_HPP
#define AZPMAP_HPP 

#include "map.hpp"

class AzpMap
{
public:
	AzpMap(wxString file);
	AzpMapData GetData();
	int64_t ArrayData[20][20];
	int64_t EventData[20][20];
private:
	AzpMapData map;


};
#endif
