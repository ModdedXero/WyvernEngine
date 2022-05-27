#pragma once

#include <Wyvern/Core/Math/Math.h>
#include <Wyvern/Core/Scene/UUID.h>
#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Scene/Scene.h>
#include <Wyvern/Core/Physics/Physics.h>
#include <Wyvern/Renderer/CameraRenderer.h>
#include <Wyvern/Utils/FileSystem.h>
#include <Wyvern/Core/Graphics/Sprite.h>

#include <yaml-cpp/yaml.h>
#include <string>

namespace YAML
{
	template<>
	struct convert<Wyvern::Vector2>
	{
		static YAML::Node encode(const Wyvern::Vector2& rhs)
		{
			YAML::Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Vector2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Wyvern::Vector3>
	{
		static YAML::Node encode(const Wyvern::Vector3& rhs)
		{
			YAML::Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Vector3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Wyvern::Vector4>
	{
		static YAML::Node encode(const Wyvern::Vector4& rhs)
		{
			YAML::Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Vector4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Wyvern::PhysicsBody>
	{
		static YAML::Node encode(const Wyvern::PhysicsBody& rhs)
		{
			YAML::Node node;
			node.push_back((int)rhs);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::PhysicsBody& rhs)
		{
			rhs = (Wyvern::PhysicsBody)node.as<int>();
			return true;
		}
	};

	template<>
	struct convert<Wyvern::Render::CameraMode>
	{
		static YAML::Node encode(const Wyvern::Render::CameraMode& rhs)
		{
			YAML::Node node;
			node.push_back((int)rhs);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Render::CameraMode& rhs)
		{
			rhs = (Wyvern::Render::CameraMode)node.as<int>();
			return true;
		}
	};

	template<>
	struct convert<Wyvern::UUID>
	{
		static YAML::Node encode(const Wyvern::UUID& rhs)
		{
			YAML::Node node;
			node.push_back(rhs);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::UUID& rhs)
		{
			rhs = Wyvern::UUID(node.as<uint64_t>());
			return true;
		}
	};

	template<>
	struct convert<Wyvern::Entity>
	{
		static YAML::Node encode(const Wyvern::Entity& rhs)
		{
			YAML::Node node;
			node.push_back(rhs.GetUUID());
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Entity& rhs)
		{
			if (node.as<uint64_t>() == 0) return true;

			rhs = Wyvern::Scene::CreateEntity(Wyvern::Scene::GetActiveScene(), Wyvern::UUID(node.as<uint64_t>()));
			return true;
		}
	};

	template<>
	struct convert<Wyvern::Sprite>
	{
		static YAML::Node encode(const Wyvern::Sprite& rhs)
		{
			YAML::Node node;

			node.push_back(rhs.GetTexture()->GetPath());
			for (auto& vec : rhs.GetTexCoords())
			{
				node.push_back(vec);
			}

			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Sprite& rhs)
		{
			if (!node.IsSequence() || node.size() != 5)
				return false;

			std::vector<Wyvern::Vector2> coords;
			coords.push_back(node[1].as<Wyvern::Vector2>());
			coords.push_back(node[2].as<Wyvern::Vector2>());
			coords.push_back(node[3].as<Wyvern::Vector2>());
			coords.push_back(node[4].as<Wyvern::Vector2>());

			rhs.SetTexture(Wyvern::Texture2D::Create(node[0].as<std::string>()));
			rhs.SetTexCoords(coords);

			return true;
		}
	};

	template<>
	struct convert<Wyvern::Utils::FileSystem>
	{
		static YAML::Node encode(const Wyvern::Utils::FileSystem& rhs)
		{
			YAML::Node node;
			node.push_back(rhs);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Utils::FileSystem& rhs)
		{
			rhs = Wyvern::Utils::FileSystem(node[0].as<std::string>());
			return true;
		}
	};
}

namespace Wyvern
{
	YAML::Emitter& operator <<(YAML::Emitter& out, const Vector2& vec);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Vector3& vec);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Vector4& vec);

	YAML::Emitter& operator <<(YAML::Emitter& out, const PhysicsBody& body);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Render::CameraMode& cameraMode);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Sprite& sprite);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Entity& entity);
}