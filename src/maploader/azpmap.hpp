#ifndef AZPMAP_HPP
#define AZPMAP_HPP 

#include "map.hpp"

#define BLUE_AND_RED_TILES 0
#define VADRIX_TILES 1

class AzpMap
{
public:
	AzpMap(wxString file);
	AzpMapData GetData();
	int64_t GetArrayData(int posx,int posy);
	int64_t EventData[20][20];
	int32_t TileSets[64][2];
private:
	AzpMapData map;
	int64_t ArrayData[20][20];


};
#endif
