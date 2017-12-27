#version 330
in Data
{
	vec3 Position;
	vec3 Normal;
	vec4 ex_Color;
} data;

out vec4 out_Color;

struct light{
	vec3 dir;
	vec3 col;
};

uniform mat4 ModelViewMatrix;

 
void main(void)
{
	float ka = 0.1f;
	float kd = 0.3f;
	float ks = 0.6f;
	float sp = 3.0f;

	light lights[3];

	lights[0].dir = vec3(0.f, -1.f, 0.f);
	lights[1].dir = vec3(-1.f, 0.f, 0.f);
	lights[2].dir = vec3(0.f, 0.f, -1.f);

	lights[0].col = vec3(1.f, 0.1f, 0.1f);
	lights[1].col = vec3(0.1f, 1.f, 0.1f);
	lights[2].col = vec3(0.1f, 0.1f, 1.f);

	
	vec3 ambientSum = vec3(0);
	vec3 diffuseSum = vec3(0);
	vec3 specSum = vec3(0);

	vec3 ambient, diffuse, specular;
 
	vec3 N = normalize(data.Normal);
	vec3 V = normalize(- data.Position );
	

    ambientSum = ka*vec3(data.ex_Color);
	for(int i=0;i<3;i++)
	{	
		vec3 L = normalize(vec3(ModelViewMatrix * -vec4(lights[i].dir,0)));
		float diff = max(dot(N,L),0.0f);
		diffuse =  kd*diff * lights[i].col ;
		diffuseSum += diffuse;

		vec3 R = reflect(-L,N);
		specular = lights[i].col * ks * pow( max( dot(R,V), 0.0), sp);
		specSum += specular;

	}	

	vec4 result = vec4(ambientSum + diffuseSum+specSum,1);
	out_Color = result;
}
