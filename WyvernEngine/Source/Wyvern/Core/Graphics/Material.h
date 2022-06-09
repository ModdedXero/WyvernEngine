#pragma once

#include "Shader.h"

#include <Wyvern/Core/UUID.h>
#include <Wyvern/Core/WyvernObject.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	struct Material : public WyvernObject
	{
		friend class ModelImporter;
	public:
		Material();
		Material(Tools::FileSystem material);

		virtual void _DrawProperties() override;

		Vector4 BaseColor() const { return m_BaseColor; }

	public:
		UUID GetUUID() const { return m_UUID; }
		Shader GetShader() const { return *m_Shader; }

		void SetShader(Tools::FileSystem& shaderPath);

	private:
		UUID m_UUID;
		Tools::FileSystem m_MaterialPath;
		Tools::FileSystem m_ShaderPath;
		Shader* m_Shader;

		Vector4 m_BaseColor;

	private:
		void LoadMaterial();
		void SaveMaterial();
	};
}