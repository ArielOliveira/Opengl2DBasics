#shader vertex
#version 330

in vec4 position;
uniform mat4 transform;
uniform mat4 camera;
uniform mat4 cameraParent;


void main()
{
	gl_Position = cameraParent * camera * transform * position;
}

#shader fragment
#version 330

out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
