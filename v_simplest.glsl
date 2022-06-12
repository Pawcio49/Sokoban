#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Attributes
in vec4 vertex; //Vertex coordinates in model space
in vec4 normal;
in vec2 texCoord0;

out vec4 n;
out vec4 v;
out vec2 iTexCoord0;


out vec4 l[4];
out float d[4];

void main(void) {
    float lightHigh = 9;
    float corner = 11;
    float lightMaxDistance = 28;

    vec4 lp[4];
    lp[0] = vec4(-corner, -corner, lightHigh, 1);
    lp[1] = vec4(corner, -corner, lightHigh, 1);
    lp[2] = vec4(-corner, corner, lightHigh, 1);
    lp[3] = vec4(corner, corner, lightHigh, 1);

    for(int i=0;i<4;i++){
        l[i] = normalize(V * lp[i] - V * M * vertex); //vector towards the light in eye space
        d[i] = distance(V*M*vertex, V*lp[i]); //zmierzenie odleglosc swiatla do wierzcholka
        d[i] = clamp(d[i], 0, lightMaxDistance); //przyciecie miejsc ktore co za daleko
        d[i] = 1 - d[i]/lightMaxDistance; //zmienienie zakresu d1 na <0,1> i odwrocenie liczb, zeby czym bylo blizej tym bylo jasniejsze
    }

    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //vector towards the viewer in eye space
    n = normalize(V * M * normal); //normal vector in eye space

    iTexCoord0 = texCoord0;
    gl_Position = P * V * M * vertex;
}
