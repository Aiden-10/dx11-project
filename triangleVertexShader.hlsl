cbuffer ConstantBuffer : register(b0)
{
    float AnimationTime;
};

struct Vertex
{
    float2 position : POSITION;
    float3 color : COLOR;
};

struct Output
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

Output main(Vertex input)
{
    Output output;

    // Define rotation angle based on animation time
    float angle = AnimationTime; // Adjust the speed of rotation as needed

    // Calculate cosine and sine of the rotation angle
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    // Rotate the vertex position around the origin
    float2 rotatedPosition;
    rotatedPosition.x = input.position.x * cosAngle - input.position.y * sinAngle;
    rotatedPosition.y = input.position.x * sinAngle + input.position.y * cosAngle;

    // Set the rotated position
    output.position = float4(rotatedPosition, 0, 1);

    // Pass through the color
    output.color = input.color;

    return output;
}
