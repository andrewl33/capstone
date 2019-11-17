//#version 330 core
// On macOS, only shader version 150 works, 330 isn’t supported
#version 150

uniform float distance;
uniform vec2 resolution;

out vec4 out_color;

void main()
{
    vec2 p = vec2((gl_FragCoord.x - resolution[0]) / distance, (gl_FragCoord.y - resolution[1]) / (distance/2));
    
    float thickness = 0.02;
    float radius = 0.5;
    float intensity = thickness/abs(radius - length(p));
    
    out_color = vec4(intensity, 0., intensity, .5);
}
