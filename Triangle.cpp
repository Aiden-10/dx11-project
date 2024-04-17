#include "Triangle.h"
#include <fstream>
#include <vector>
#include <sstream>

struct ConstantBuffer
{
	float AnimationTime;
};

Triangle::Triangle(Renderer& renderer, Vertex vertices[]) 
{
	createMesh(renderer, vertices);
	createShaders(renderer);
}

Triangle::~Triangle()
{
	vertex_buffer->Release();
	vertex_shader->Release();
	pixel_shader->Release();
	input_layout->Release();
}

void Triangle::draw(Renderer& renderer)
{
	auto deviceContext = renderer.getDeviceContext();

	// Bind triangle layout
	deviceContext->IASetInputLayout(input_layout);
	// Bind triangle shaders
	deviceContext->VSSetShader(vertex_shader, nullptr, 0);
	deviceContext->PSSetShader(pixel_shader, nullptr, 0);

	// Bind the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Draw
	deviceContext->Draw(3, 0);
}

void Triangle::createMesh(Renderer& renderer, Vertex vertices[])
{
	// Create the vertex buffer
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(Vertex) * 3, D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &vertex_buffer);
}

void Triangle::createShaders(Renderer& renderer)
{
	// Create shaders
	std::ifstream vsFile("triangleVertexShader.cso", std::ios::binary);
	if (!vsFile.is_open()) {
		MessageBoxA(NULL, "Could not open 'triangleVertexShader.cso'!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	}
	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };

	std::ifstream psFile("trianglePixelShader.cso", std::ios::binary);
	if (!psFile.is_open()) {
		MessageBoxA(NULL, "Could not open 'trianglePixelShader.cso'!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	}
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	HRESULT hr;
	hr = renderer.getDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertex_shader);

	if (FAILED(hr)) {
		MessageBoxA(NULL, "Failed to create vertex shader!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	}


	hr = renderer.getDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixel_shader);

	if (FAILED(hr)) {
		MessageBoxA(NULL, "Failed to create pixel shader!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	}

	// Create input layouts
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	renderer.getDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &input_layout);
}