#version 330 core
out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;

uniform float uTime;
    //uniform vec4 uColor = vec3(1.0);

//uniform sampler2D ourTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
        //FragColor = Color; //vec4(1.0f, 0.5f, 0.2f, 1.0f); - no longer assigning an abitrary color to the pixels
	//FragColor = Color * (cos(uTime) * 0.5 + 0.5);

   // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
  // FragColor = texture(ourTexture, TexCoord);

   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
} 