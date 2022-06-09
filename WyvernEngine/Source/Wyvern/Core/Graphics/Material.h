#pragma once

#include "Shader.h"

#include <Wyvern/Core/UUID.h>
#include <Wyvern/Core/WyvernObject.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	namespace Render
	{
		class ModelImporter;
	}

	struct Material : public WyvernObject
	{
		friend class Render::ModelImporter;
	public:
		Material();
		Material(Tools::FileSystem material);

		virtual void _DrawProperties() override;

		Vector4 BaseColor() const { return m_BaseColor; }

	public:
		Shader GetShader() const { return *m_Shader; }

		void SetShader(Tools::FileSystem& shaderPath);

	private:
		Tools::FileSystem m_MaterialPath;
		Tools::FileSystem m_ShaderPath;
		Shader* m_Shader;

		Vector4 m_BaseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	private:
		void LoadMaterial();
		void SaveMaterial();
	};
}