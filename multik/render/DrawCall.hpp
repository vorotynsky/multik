// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>

namespace multik::render
{
    class DrawCall
    {
    public:
        void Draw(int count) const;

        static DrawCall Triangles();
        static DrawCall Points();
        static DrawCall Lines();
        static DrawCall Quads();
        static DrawCall TriStrip();
        static DrawCall TriFan();
        static DrawCall Polygon();

        static DrawCall LineStrip();
        static DrawCall LineStrip(bool loop);

        DrawCall();

    private:
        DrawCall(int mode);
        int mode;
    };
}
