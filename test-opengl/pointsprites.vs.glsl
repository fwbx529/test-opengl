#version 450

layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 normal;

void main()
{
    gl_PointSize = 2.0f;
    gl_Position = vec4(position, 1.0f);
}
