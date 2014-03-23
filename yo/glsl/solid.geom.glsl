#version 400
 
layout(lines_adjacency) in;
layout (line_strip, max_vertices = 2) out;

void main()
{
    gl_Position = gl_in[1].gl_Position;
	gl_PointSize = 1.0;
	gl_PrimitiveID = gl_PrimitiveIDIn;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
	gl_PointSize = 1.0;
	gl_PrimitiveID = gl_PrimitiveIDIn;
    EmitVertex();
	EndPrimitive();
}
