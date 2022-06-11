#version 330

uniform sampler2D textureMap0;

//in vec4 l;
in vec4 n;
in vec4 v;
in vec2 iTexCoord0;

in float d[4];
in vec4 l[4];

out vec4 pixelColor; //Output variable. Almost final pixel color.

void main(void) {
	vec4 mn = normalize(n);
    vec4 mv = normalize(v);
	vec4 texColor = texture(textureMap0,iTexCoord0);
	vec4 kd = texColor;

	vec4 ml[4];
	vec4 mr[4];
	float nls[4];
	float rvs[4];
	float nl = 0;
	float rv = 0;

	for(int i=0;i<4;i++){
    	ml[i] = normalize(l[i]);
		nls[i] = clamp(dot(mn, ml[i]), 0, 1);
		nls[i] = nls[i] * d[i];
		nl = nl + nls[i];

		mr[i] = reflect(-ml[i], mn);
		rvs[i] = pow(clamp(dot(mr[i], mv), 0, 1), 50);
		rv = rv + rvs[i];
	}
    
	vec4 ks = vec4(0.2,0.2,0.2,1);

	pixelColor = vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb * rv, 0);
}
