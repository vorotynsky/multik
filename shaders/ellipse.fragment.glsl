// Copyright (c) 2020 Vorotynsky Maxim

#version 400 core

uniform mat4 u_mvp;
uniform vec2 u_resolution;
out vec4 color;

float pow2(float x) { return x * x; }

float stepper()
{
    vec4 sm = (u_mvp * vec4(1.0f));
    float stepper = sm[0] + sm[1] + sm[2] + sm[3];
    return stepper / 4;
}

void main()
{
    vec2 d = (gl_FragCoord.xy / u_resolution.xy) * 2 - vec2(1.0);
    vec4 pos = u_mvp * vec4(d, 0.0, 0.0);
    vec4 center = u_mvp * vec4(0.0);

    float r = distance(pos, center);
    r = step(stepper(), r);
    color = vec4(0.192f, 0.96f, 0.512f, 1.0f - r);
}
