#pragma once

#include "Shader.h"

#include <Wyvern/Core/UUID.h>
#include <Wyvern/Core/WyvernObject.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	struct Material : public WyvernObject
	{
	public:
		Material();
		Material(Tools::FileSystem material);

		virtual std::string _ObjectType() const override { return typeid(Material).name(); }
		virtual void _DrawProperties() override;

	public:
		UUID GetUUID() const { return m_UUID; }
		Shader GetShader() const { return *m_Shader; }

	public:
		void SetShader(Tools::FileSystem& shaderPath);

	private:
		UUID m_UUID;
		Tools::FileSystem m_MaterialPath;
		Tools::FileSystem m_ShaderPath;
		Shader* m_Shader;

	private:
		void LoadMaterial();
		void SaveMaterial();
	};
}