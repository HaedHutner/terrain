#include <Terrain.h>

int main()
{
	Terrain terrain;

	auto gameplayThread = std::thread([&]() {
		terrain.Start();
	});

	auto renderThread = std::thread([&]() {
		terrain.StartRenderer();
	});

	renderThread.join();
	gameplayThread.join();

    exit(EXIT_SUCCESS);
}