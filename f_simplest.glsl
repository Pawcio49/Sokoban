#version 330

uniform sampler2D textureMap0;

in vec4 i_color;
in vec4 l;
in vec4 n;
in vec4 v;
in vec2 iTexCoord0;

out vec4 pixelColor; //Output variable. Almost final pixel color.
void main(void) {
    vec4 ml = normalize(l);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);

    vec4 mr = reflect(-ml, mn);

	vec4 texColor = texture(textureMap0,iTexCoord0);

	vec4 kd = texColor;
	vec4 ks = vec4(1,1,1,1);

	float nl = clamp(dot(mn, ml), 0, 1);
	float rv = pow(clamp(dot(mr, mv), 0, 1), 50);
	pixelColor = vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb * rv, 0);
}
