#pragma once
#include "Log.h"
#include <string>
#include <glad/glad.h>

namespace Engine {

	class VertexBuffer {
	private:
		uint32_t id;

		const uint32_t size; //Buffer size in bytes
	public:
		VertexBuffer(const void* data, uint32_t size, GLenum usage);
		~VertexBuffer();

		void bind();
		void unbind();

		void SetData(const void* data, uint32_t offset, uint32_t size);

		uint32_t GetBufferSize();
	};
}