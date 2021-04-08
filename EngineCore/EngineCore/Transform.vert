#version 330 

//Uniform for world transform and view-proj
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//Vertex Attributes
in vec3 inPosition;

void main(){
	
	//Change to Homogeneous Coordinate
	vec4 pos = vec4(inPosition,1.0);
	//Output 4d coordinate
	gl_Position = pos * uWorldTransform * uViewProj;
}
