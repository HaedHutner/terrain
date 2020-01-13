#include <renderer/SkyboxRenderer.h>

#include <stb_image.h>

SkyboxRenderer::SkyboxRenderer()
{
}

void SkyboxRenderer::Init(Camera& camera)
{
	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);

	skyboxShader = Shader::FromFiles("./data/shader/skybox-vertex.glsl", "./data/shader/skybox-fragment.glsl");
	skyboxShader.Link();

	glGenBuffers(1, &skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SKYBOX_VERTICES), &SKYBOX_VERTICES, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glGenTextures(1, &skyboxTexture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

	skyboxShader.Use();
	skyboxShader.SetUniformInt("skyboxTexture", 0);

	std::vector<std::string> texture_faces = {
		"./data/texture/sky/miramar_ft.tga",
		"./data/texture/sky/miramar_bk.tga",
		"./data/texture/sky/miramar_up.tga",
		"./data/texture/sky/miramar_dn.tga",
		"./data/texture/sky/miramar_rt.tga",
		"./data/texture/sky/miramar_lf.tga"
	};

	int width, height, nrChannels;

	for (unsigned int i = 0; i < texture_faces.size(); i++)
	{
		unsigned char* data = stbi_load(texture_faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			printf("Cubemap texture failed to load at path: %s\n", texture_faces[i]);
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindVertexArray(0);
}

void SkyboxRenderer::Draw(Camera &camera)
{
	glBindVertexArray(skyboxVAO);

	glDepthMask(GL_FALSE);

	skyboxShader.Use();

	glm::mat4 translationlessView = glm::mat4(glm::mat3(camera.GetView()));

	skyboxShader.SetUniformMat4("view", translationlessView);
	skyboxShader.SetUniformMat4("projection", camera.GetProjection());
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthMask(GL_TRUE);

	glBindVertexArray(0);
}
