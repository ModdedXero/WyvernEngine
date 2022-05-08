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
}