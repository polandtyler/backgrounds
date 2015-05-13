uniform sampler2D yTex, uTex, vTex;

void main()
{
    float Y = texture2D(yTex, gl_TexCoord[0].xy).x-0.0625;
    float U = texture2D(uTex, gl_TexCoord[1].xy).x-.5;
    float V = texture2D(vTex, gl_TexCoord[2].xy).x-.5;

    float R = 1.164*Y           + 1.793*V;
    float G = 1.164*Y - 0.213*U - 0.533*V;
    float B = 1.164*Y + 2.112*U;
    
    gl_FragColor = vec4(R, G, B, 1.0);
}