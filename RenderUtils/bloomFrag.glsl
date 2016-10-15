layout(location = 0) uniform geoRender;
layout(location = 2) uniform lightAlbedo;

in vec2 vUV;

out vec3 outColor;


void main()
{
	vec4 albedo = texture2D(lightAlbedo, vUV);
	vec4 color = texture2D(geoRender, vUV);
	vec4 sum = vec4(0);

	for (int i = -2; i <= 2; i++)	
		for (int j = -2; j <= 2; i++)
		{
			vec2 offset = vec2(i,j) * 0.005;
			sum += texture2D(geoRender, vUV) + offset;
	}

	outColor = (sum / 25) + albedo;

}