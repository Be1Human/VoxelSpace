#version 330

//Uniforms for world transform and View-proj
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//Attribute 0 is position , 1 is tex coords
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

//Convert to Frag Shader
out vec2 fragTexCoord;

void main(){
    //Convert position to homogeneous coordinates
	vec4 pos = vec4(inPosition , 1.0);

	//Trnasform to World Space , then clip space
	gl_Position = pos * uWorldTransform * uViewProj;

	//Pass along the Texture coordinate to frag shader
	fragTexCoord = inTexCoord;
}