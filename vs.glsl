#version 410

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 vt;

out vec2 texture_coords;
uniform float offsetz;


uniform float xTranslate;
uniform float yTranslate;


uniform mat4 scale;
uniform mat4 view;
uniform mat4 proj;

void main () {
	texture_coords = vt;
	gl_Position =  proj * view * scale * vec4 (vp, 1.0, 1.0);
}
