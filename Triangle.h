#pragma once

#include "Renderer.h"

struct Vertex {
	float x, y;
	float r, g, b;
};

class Triangle
{
public:
	Triangle(Renderer& renderer, Vertex vertices[]);
	~Triangle();
	void draw(Renderer& renderer);

	float animtime;
private:
	void createMesh(Renderer& renderer, Vertex vertices[]);
	void createShaders(Renderer& renderer);

	ID3D11Buffer* constant_buffer = nullptr;
	ID3D11Buffer* vertex_buffer = nullptr;
	ID3D11VertexShader* vertex_shader = nullptr;
	ID3D11PixelShader* pixel_shader = nullptr;
	ID3D11InputLayout* input_layout = nullptr;

	Vertex* vertices[];
};