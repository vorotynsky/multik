#version 330 core

out vec4 frag_color;

uniform mat4 u_mvp;
uniform vec2 u_resolution;
uniform vec4 u_color;

// Source https://stackoverflow.com/a/62140017/9855653

float hit_sphere(vec3 origin, vec3 direction, vec3 center, float radius)
{
    vec3 oc = origin - center;
    float a = dot(direction, direction);
    float b = 2.0 * dot(oc, direction);
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;

    if (discriminant > 0.0)
    {
        float temp = (-b - sqrt(discriminant)) / (2*a);
        if (temp > 0.0)
            return 1.0;
        temp = (-b + sqrt(discriminant)) / (2*a);
        if (temp > 0.0)
            return 1.0;
    }
    return 0.0;
}

void main()
{
    vec2 xy = gl_FragCoord.xy / u_resolution.xy * 2.0 - 1.0;

    vec4 pn = inverse(u_mvp) * vec4(xy, -1.0, 1.0);
    vec4 pf = inverse(u_mvp) * vec4(xy, 1.0, 1.0);

    vec3 orig = pn.xyz/pn.w;
    vec3 dir  = pf.xyz/pf.w - orig;

    vec3  center = vec3(0.0);
    float radius = 1.0;
    float r = hit_sphere(orig, dir, center, radius);

    vec4 color = u_color;

    frag_color = mix(vec4(0.0), color, r);
}