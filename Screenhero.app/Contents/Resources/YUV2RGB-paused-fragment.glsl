uniform sampler2D yTex, uTex, vTex;

//uniform sampler2D sceneTex; // 0
void main ()
{
    float Y = texture2D(yTex, gl_TexCoord[0].xy).x-0.0625;
    float U = texture2D(uTex, gl_TexCoord[1].xy).x-0.5;
    float V = texture2D(vTex, gl_TexCoord[2].xy).x-0.5;

    Y += texture2D(yTex, gl_TexCoord[0].xy+0.001).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy+0.003).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy+0.005).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy+0.007).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy+0.009).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy+0.011).x-0.0625;
    
    Y += texture2D(yTex, gl_TexCoord[0].xy-0.001).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy-0.003).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy-0.005).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy-0.007).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy-0.009).x-0.0625;
    Y += texture2D(yTex, gl_TexCoord[0].xy-0.011).x-0.0625;
    
    Y = Y / 12.0;
    
    float R = 1.164*Y           + 1.793*V;
    float G = 1.164*Y - 0.213*U - 0.533*V;
    float B = 1.164*Y + 2.112*U;

    gl_FragColor = vec4(R/2.0, G/2.0, B/2.0, 1.0);
}