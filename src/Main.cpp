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

int main()
{
	int screenX = 800, screenY = 600;

	std::atomic<bool> isWorking{ true };
	std::atomic<Camera> camera{ Camera(90.0, 3.0, 1.0, screenX, screenY) };
	std::atomic<TerrainWorld> world{ TerrainWorld("Test", HeightMapGenerator()) };

	auto gameplayThread = std::thread([&]() {
		while (isWorking) {

			TerrainWorld worldCopy = world.load();
			Camera cameraCopy = camera.load();
			worldCopy.GenerateChunksAt({ cameraCopy.GetPosition().x, cameraCopy.GetPosition().y }, 3);
			world.store(worldCopy);

			printf("Generated chunks...\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	});

	auto renderThread = std::thread([&]() {
		TerrainRenderer renderer = TerrainRenderer(world, camera, isWorking);
		renderer.StartRenderer(); // *isWorking = false somewhere in here
	});

	renderThread.join();
	gameplayThread.join();

    exit(EXIT_SUCCESS);
}