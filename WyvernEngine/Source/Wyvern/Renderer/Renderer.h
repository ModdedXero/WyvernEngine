#pragma once

#include "Framebuffer.h"
#include "CameraRenderer.h"

#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Graphics/Mesh.h>
#include <Wyvern/Core/Components/MeshRenderer.h>
#include <Wyvern/Core/Components/Transform.h>

namespace Wyvern::Render
{
	class Renderer
	{
	public:
		static void Construct();
		static void Destruct();

		static void BeginScene(CameraRenderer* cameraRenderer, Transform* cameraPosition, Vector4 clearColor = { 0.1f, 0.1f, 0.25f, 1.0f });
		static void EndScene();

		static void DrawMesh(Transform* transform, MeshRenderer* renderer, Mesh* mesh, int entityID);
		static void DrawMesh(Transform* transform, Ref<Material> material, std::vector<Vector3> vertices, std::vector<Vector2> uvs, std::vector<Vector4> colors, std::vector<int> indices, int entityID);

		static Framebuffer* GetFramebuffer() { return s_Framebuffer; }

	private:
		static void BeginBatch();
		static void EndBatch();
		static void Flush();

	private:
		static Framebuffer* s_Framebuffer;
	};
}