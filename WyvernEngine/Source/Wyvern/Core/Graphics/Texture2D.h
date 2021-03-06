#pragma once

#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	enum class Texture2DFormat
	{
		None,

		RGBA
	};

	enum class Texture2DWrap
	{
		None,

		REPEAT
	};

	enum class Texture2DFilter
	{
		None,

		NEAREST,
		LINEAR
	};

	struct Texture2DSpecifications
	{
		Texture2DFormat InternalFormat = Texture2DFormat::RGBA;
		Texture2DFormat ImageFormat = Texture2DFormat::RGBA;

		Texture2DWrap Wrap = Texture2DWrap::REPEAT;
		Texture2DFilter Filter = Texture2DFilter::LINEAR;

		bool FlipVeritcally = false;
	};

	class Texture2D
	{
	public:
		Texture2D(const Tools::FileSystem& file, const Texture2DSpecifications& specs);

		void Bind() const;

		unsigned int GetID() const { return m_ID; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		Tools::FileSystem GetPath() const { return m_Path; }

		static Ref<Texture2D> Create(const Tools::FileSystem& file, Texture2DSpecifications specs = Texture2DSpecifications());
	private:
		Texture2DSpecifications m_Specs;
		Tools::FileSystem m_Path;

		unsigned int m_ID;
		int m_Width, m_Height;
	};
}