#pragma once

namespace Wyvern::Renderer
{
	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		unsigned int Width, Height;
		FramebufferAttachmentSpecification Attachments;
		unsigned int Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpecification& specs);
		~Framebuffer();

		void Invalidate();

		void Resize(const Vector2Int& size);
		int ReadPixel(unsigned int attachmentIndex, int x, int y);
		void ClearColorAttachment(unsigned int attachmentIndex, int value);
		FramebufferSpecification& GetSpecification() { return m_Specification; }

		void Bind();
		void Unbind();
		void BindColorAttachmentTexture(unsigned int index = 0);

		unsigned int GetColorAttachmentRendererID(unsigned int index = 0) const 
		{
			WV_CORE_ASSERT(index < m_ColorAttachments.size(), ""); return m_ColorAttachments[index];
		}

	private:
		unsigned int m_RendererID;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecs;
		FramebufferTextureSpecification m_DepthAttachmentSpec;

		std::vector<unsigned int> m_ColorAttachments;
		unsigned int m_DepthAttachment;
	};
}