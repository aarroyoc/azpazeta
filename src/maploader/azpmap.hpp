#ifndef AZPMAP_HPP
#define AZPMAP_HPP 

#include "map.hpp"

class AzpMap
{
public:
	AzpMap(wxString file);
	AzpMapData GetData();
private:
	AzpMapData map;


};
#endif
