#include <Terrain.h>

Terrain::Terrain()
{
}

void Terrain::Start()
{
	while (isWorking) {

		m.lock();
		// printf("Camera Location: %4.5f, %4.5f, %4.5f ( %3d, %3d )\n", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z, ((int) camera.GetPosition().x) / CHUNK_WIDTH, ((int) camera.GetPosition().z) / CHUNK_WIDTH);
		world.GenerateChunksAt({ (int) camera.GetPosition().x, (int) camera.GetPosition().z }, 4);
		m.unlock();

		// printf("Generated chunks...\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void Terrain::StartRenderer()
{
	renderer.StartRenderer();
}
