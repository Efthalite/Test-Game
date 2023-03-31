#version 460 core
layout(location = 0) in vec3 inPos;

uniform vec4 Change;

void main()
{
    gl_Position = Change + vec4(inPos, 1.0f) - vec4(0.5, 0.5, 0.0, 0.0);
}