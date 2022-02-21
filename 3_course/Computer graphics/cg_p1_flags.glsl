// //Use ctrl+shift+G for live preview a fragment shaders

// точность переменных шейдера
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

vec4 SeychellesFlag(vec2 position)
{
    vec4 color = vec4(0);
    if ((position.x)*2.0 <= position.y &&
    position.y <= 0.66)
    color = vec4(vec2(0),vec2(1));
    else if ((position.x)*0.95 <= position.y &&
    position.y <= 0.66)
    color = vec4(1.0, 0.85, 0.0, 1.0);
    else if ((position.x)*0.45 <= position.y &&
    position.y <= 0.66)
    color = vec4(1.0, 0.0, 0.0, 1.0);
    else if ((position.x)*0.2 <= position.y &&
    position.y <= 0.66)
    color = vec4(1.0, 1.0, 1.0, 1.0);
    else if ((position.x)*0.0 <= position.y &&
    position.y <= 0.66)
    color = vec4(0.0, 0.5, 0.1, 1.0);

    return color;
}

// author Tunyan Edmon, group 607-91
void main()
{
    vec2 position = gl_FragCoord.xy/u_resolution.xy;
    gl_FragColor = SeychellesFlag(position);
}
