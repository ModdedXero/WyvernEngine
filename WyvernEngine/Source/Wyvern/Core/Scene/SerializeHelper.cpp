#include "wvpch.h"
#include "SerializeHelper.h"

namespace Wyvern
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const Vector2& vec)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Vector3& vec)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Vector4& vec)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const PhysicsBody& body)
	{
		out << (int)body;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Render::CameraMode& cameraMode)
	{
		out << (int)cameraMode;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Sprite& sprite)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq;

		out << (std::string)sprite.GetTexture()->GetPath();
		out << sprite.GetTexCoords()[0];
		out << sprite.GetTexCoords()[1];
		out << sprite.GetTexCoords()[2];
		out << sprite.GetTexCoords()[3];

		out << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Entity& entity)
	{
		out << (uint64_t)entity.GetUUID();
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const Mesh& mesh)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq;

		out << mesh.GetModelPath();
		out << mesh.GetMeshIndex();

		out << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const std::vector<Wyvern::Ref<Wyvern::Material>>& rhs)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq;

		for (auto& mat : rhs)
		{
			out << (uint64_t)mat->uuid;
		}

		out << YAML::EndSeq;
		return out;
	}
}