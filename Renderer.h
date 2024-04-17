#pragma once
#include "Window.h"
#include <d3d11.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>


class Renderer
{
public:
	Renderer(Window& window);
	void beginFrame();
	void endFrame();

	void DrawString(const char text[]);

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

private:
	void createDevice(Window& window);
	void createRenderTarget();

	IDXGISwapChain* swap_chain = { nullptr };
	ID3D11Device* device = { nullptr };
	ID3D11DeviceContext* device_context = { nullptr };
	ID3D11RenderTargetView* render_target_view = { nullptr };
	ID3D11RasterizerState* rasterizer_state = { nullptr };
	D3D11_TEXTURE2D_DESC back_buffer_desc;

	// Font ptrs
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;

	Window& window;
};