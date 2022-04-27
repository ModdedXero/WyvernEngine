#include "wvpch.h"
#include "SpriteRenderer.h"

#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Scene/SerializeHelper.h>

namespace Wyvern
{
	void SpriteRenderer::Serialize(YAML::Emitter& out)
	{
		out << YAML::Key << "SpriteRenderer";
		out << YAML::BeginMap;

		out << YAML::Key << "color" << YAML::Value << color;

		out << YAML::EndMap;
	}

	void SpriteRenderer::Deserialize(Entity* ent, YAML::Node& data)
	{
		SpriteRenderer* spriteRenderer = ent->AddComponent<SpriteRenderer>();

		spriteRenderer->color = data["color"].as<Vector4>();
	}
}