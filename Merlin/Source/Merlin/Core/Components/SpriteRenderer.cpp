#include "mlpch.h"
#include "SpriteRenderer.h"

#include <Merlin/Core/Scene/Entity.h>
#include <Merlin/Core/Scene/SerializeHelper.h>

namespace Merlin
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