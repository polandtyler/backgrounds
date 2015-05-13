uniform sampler2D texSampler;

void main()
{
    gl_FragColor = texture2D(texSampler, gl_TexCoord[0].st );
}