#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <ctime>
#include <atomic>
#include <mutex>

#include <TerrainWorld.h>

#include <renderer/Camera.h>
#include <renderer/TerrainRenderer.h>

class Terrain {

	int screenX = 1280, screenY = 720;

	std::atomic<bool> isWorking{ true };

	std::mutex m;

	Camera camera{ 90.0, 3.0, 1.0, screenX, screenY };
	TerrainWorld world{ "Test", HeightMapGenerator() };

	TerrainRenderer renderer{ m, world, camera, isWorking };

public:

	Terrain();

	void Start();

	void StartRenderer();

};

#endif