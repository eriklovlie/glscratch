/*----------------- "exampleVertexShader.vert" -----------------*/

#version 400

// in_Position was bound to attribute index 0("shaderAttribute")
in  vec3 in_Position;

void main()
{
    gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}
/*--------------------------------------------------------------*/
