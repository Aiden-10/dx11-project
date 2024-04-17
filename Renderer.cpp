#include "Renderer.h"

Renderer::Renderer(Window& window)
	: window(window) 
{
	createDevice(window);
	createRenderTarget();
}

void Renderer::createDevice(Window& window) 
{
	// Define our swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.getHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	// Create the swap chain, device and device context
	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION,
		&swapChainDesc, &swap_chain,
		&device, nullptr, &device_context);

	// Check for error
	if (result != S_OK) {
		MessageBox(nullptr, "Error creating DX11", "Error", MB_OK);
		exit(0);
	}

	// Create the rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	HRESULT hr = device->CreateRasterizerState(&rasterizerDesc, &rasterizer_state);
	if (result != S_OK) { MessageBoxA(NULL, "Failed to create rasterizer state", "Error", MB_ICONEXCLAMATION | MB_OK); }

	spriteBatch = std::make_unique<DirectX::SpriteBatch>(device_context);
	spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Data\\Fonts\\comic_sans_ms_16.spritefont");


}

void Renderer::DrawString(const char text[])
{
	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), text, DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	spriteBatch->End();
}


void Renderer::createRenderTarget() {
	ID3D11Texture2D* backBuffer;
	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	device->CreateRenderTargetView(backBuffer, nullptr, &render_target_view);
	backBuffer->Release();
}

void Renderer::beginFrame() {
	// Bind render target
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr);

	// Set viewport
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, window.winSize.x, window.winSize.y);
	device_context->RSSetViewports(1, &viewport);

	// set rasterizer state
	device_context->RSSetState(rasterizer_state);

	// Set the background color
	float clearColor[] = { .25f, .5f, 1, 1 };
	device_context->ClearRenderTargetView(render_target_view, clearColor);
}

void Renderer::endFrame() {
	// Swap the front buffer with the back buffer
	swap_chain->Present(1, 0);
}

ID3D11Device* Renderer::getDevice() {
	return device;
}

ID3D11DeviceContext* Renderer::getDeviceContext() {
	return device_context;
}