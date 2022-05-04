#pragma once

namespace Wyvern::Renderer
{
	struct FrameBufferSpecs
	{
		unsigned int Width, Height;
		unsigned int Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FrameBufferSpecs& specs);
		~Framebuffer();

		void Invalidate();
		void Resize(const Vector2& size);

		void Bind();
		void Unbind();

		unsigned int GetColorAttachmentRendererID() const { return m_ColorAttachment; }
	private:
		unsigned int m_RendererID;
		unsigned int m_ColorAttachment;
		unsigned int m_DepthAttachment;

		FrameBufferSpecs m_Specs;
	};
}