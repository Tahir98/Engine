#pragma once
#include "Graphics/Interface/VertexArray.h"
#include "Graphics/Interface/VertexBuffer.h"
#include "Graphics/Interface/IndexBuffer.h"
#include "Graphics/Interface/Shader.h"
#include "Graphics/Interface/Texture.h"
#include "Camera/PerspectiveCamera.h"

namespace Engine {

	class SpherecalSkybox {
	private:
		VertexBuffer* vb = nullptr;
		VertexArray va;
		IndexBuffer* ib = nullptr;
		Shader* shader = nullptr;
		Texture* hdri = nullptr;

		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;

		uint32_t indexCount = -1;

		uint32_t segment = 20;
		glm::vec3 rotationAngles;
		glm::mat4 rotationMatrix;
	public:
		SpherecalSkybox(std::string filePath, glm::vec3 rotation = glm::vec3(0,0,0)) : rotationAngles(rotation){
			for (int i = 0; i < 2 * segment + 1; i++) {
				float angleY = 180.0f / segment * (i);
				for (int j = 0; j < segment + 1; j++) {
					float angleX = 180.0f / segment * j;

					glm::vec3 position;
					position.x = cosf(glm::radians(angleY)) * sinf(glm::radians(angleX));
					position.y = cosf(glm::radians(angleX));
					position.z = sinf(glm::radians(angleY)) * sinf(glm::radians(angleX));

					glm::vec3 texCoord;

					texCoord.x = (float)i /(2.0f * segment);
					texCoord.y = 1.0f - (float)j / segment;
					texCoord.z = 0;

					vertices.push_back(position);
					vertices.push_back(texCoord);
				}
			}

			for (int i = 0; i < 2 * segment; i++) {
				for (int j = 0; j < segment; j++) {
					indices.push_back(i * (segment + 1) + j);
					indices.push_back(i * (segment + 1) + j + 1);
					indices.push_back((i + 1) * (segment + 1) + j);

					indices.push_back((i + 1) * (segment + 1) + j);
					indices.push_back(i * (segment + 1) + j + 1);
					indices.push_back((i + 1) * (segment + 1) + j + 1);
				}
			}

			vb = nullptr; //new Engine::VertexBuffer(vertices.data(), sizeof(glm::vec3) * vertices.size(), GL_STATIC_DRAW);

			va.bind();
			vb->bind();

			va.PushElement(vb, 3, Engine::VertexArray::FLOAT, false);
			va.PushElement(vb, 3, Engine::VertexArray::FLOAT, false);

			ib = nullptr; //new Engine::IndexBuffer(indices.data(), sizeof(uint32_t)  * indices.size(), GL_STATIC_DRAW);

			shader = new Engine::Shader("Shaders/skybox.shader");

			hdri = new Engine::Texture(filePath);

			indexCount = indices.size();

			vertices.clear();
			vertices.shrink_to_fit();
			indices.clear();
			indices.shrink_to_fit();

			rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngles.x, glm::vec3(1, 0, 0));
			rotationMatrix = glm::rotate(rotationMatrix, rotationAngles.y, glm::vec3(0, 1, 0));
			rotationMatrix = glm::rotate(rotationMatrix, rotationAngles.z, glm::vec3(0, 0, 1));
		}

		~SpherecalSkybox() {
			delete vb;
			delete ib;
			delete shader;
			delete hdri;
		}

		void draw(PerspectiveCamera& camera) {
			glEnable(GL_DEPTH_TEST);

			va.bind();
			vb->bind();
			ib->bind();
			shader->bind();
			hdri->bind();
			hdri->SetActiveTextureSlot(0);

			shader->SetUniform2ui("texSize", hdri->getWidth(), hdri->getHeight());
			shader->SetUniform1i("hdriTex", 0);
			shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(rotationMatrix));
			shader->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
			shader->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		}

		void setRotation(glm::vec3 rotation) {
			this->rotationAngles = rotation;

			rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngles.x), glm::vec3(1, 0, 0));
			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationAngles.y), glm::vec3(0, 1, 0));
			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationAngles.z), glm::vec3(0, 0, 1));
		}
	};

}

