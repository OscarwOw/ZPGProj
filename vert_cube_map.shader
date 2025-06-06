#version 330
layout(location = 0) in vec3 vp;

uniform mat4 view;
uniform mat4 projection;

out vec3 fragmentLocalPosition;

void main () {
	vec4 pos = projection * view * vec4(vp, 1.0);
	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
	fragmentLocalPosition = vec3(vp.x, vp.y, -vp.z);
}
