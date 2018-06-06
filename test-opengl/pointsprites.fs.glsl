#version 450

out vec4 fcolor;

void main()
{
    vec2 coord = gl_PointCoord - vec2(0.5f, 0.5f);
    float radius = dot(coord, coord);
    radius = sqrt(radius);
    if (radius > 0.5f) discard;

    fcolor = vec4(clamp(1 - abs(radius - 0.0f), 0, 1),
                  clamp(1 - abs(radius - 0.25f), 0, 1),
                  clamp(1 - abs(radius - 0.5f), 0, 1),
                  0.5f);
}