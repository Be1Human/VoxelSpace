#version 330

//Tex coord input from vertex shader
in vec2 fragTexCoord;

//Output Color
out vec4 outColor;

//For Texture Sampling
uniform sampler2D uTexture;

void main(){
    //Sample Color from Texture
	outColor = texture(uTexture,fragTexCoord);
}