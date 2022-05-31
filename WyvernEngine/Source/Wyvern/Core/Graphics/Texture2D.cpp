#include "wvpch.h"
#include "Texture2D.h"

#include <Wyvern/Utils/FileSystem.h>x

#include <glad.h>
#include <stb_image.h>

namespace Wyvern
{
	namespace Tools
	{
		static GLenum TextureFormat(Texture2DFormat format)
		{
			switch (format)
			{
			case Wyvern::Texture2DFormat::RGBA: return GL_RGBA;
			default:
				break;
			}

			return GL_NONE;
		}

		static GLenum TextureWrap(Texture2DWrap wrap)
		{
			switch (wrap)
			{
			case Wyvern::Texture2DWrap::REPEAT: return GL_REPEAT;
			default:
				break;
			}

			return GL_NONE;
		}

		static GLenum TextureFilter(Texture2DFilter filter)
		{
			switch (filter)
			{
			case Wyvern::Texture2DFilter::NEAREST: return GL_NEAREST;
			case Wyvern::Texture2DFilter::LINEAR: return GL_LINEAR;
			default:
				break;
			}

			return GL_NONE;
		}
	}

	Texture2D::Texture2D(const Tools::FileSystem& file, const Texture2DSpecifications& specs)
		: m_Specs(specs), m_ID(0), m_Width(0), m_Height(0), m_Path(file)
	{
		glGenTextures(1, &m_ID);

		int nrChannels;
		stbi_set_flip_vertically_on_load(!specs.FlipVeritcally);
		std::string path = m_Path;
		unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &nrChannels, 0);

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, Tools::TextureFormat(specs.InternalFormat), m_Width, m_Height, 
			0, Tools::TextureFormat(specs.ImageFormat), GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Tools::TextureWrap(specs.Wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Tools::TextureWrap(specs.Wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Tools::TextureFilter(specs.Filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Tools::TextureFilter(specs.Filter));

		stbi_image_free(data);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	Ref<Texture2D> Texture2D::Create(const Tools::FileSystem& file, Texture2DSpecifications specs)
	{
		return CreateRef<Texture2D>(file, specs);
	}
}