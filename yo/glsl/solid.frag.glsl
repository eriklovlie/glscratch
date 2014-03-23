/*---------------- "exampleFragmentShader.frag" ----------------*/

#version 150 // Specify which version of GLSL we are using.

precision highp float; // Video card drivers require this line to function properly

out vec4 fragColor;

void main()
{
//	float col = float(gl_PrimitiveID % 8 + 1) / 8.0;
//    fragColor = vec4(col, col, 0.9, 1.0);

    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
/*--------------------------------------------------------------*/
