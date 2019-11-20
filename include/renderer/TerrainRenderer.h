#ifndef _HEIGHT_MAP_RENDERER_H
#define _HEIGHT_MAP_RENDERER_H

#include <TerrainWorld.h>

class TerrainRenderer {

	TerrainWorld world;

public:

	TerrainRenderer(TerrainWorld world);

	void startRenderer();

};

#endif