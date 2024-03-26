#include "DrawCall.hpp"

namespace multik::render
{
    DrawCall::DrawCall() : mode(GL_TRIANGLES) { }
    DrawCall::DrawCall(int mode) : mode(mode) { }

    void DrawCall::Draw(int count) const
    { 
        glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
    }
    
    DrawCall DrawCall::Triangles()
    {
        return DrawCall(GL_TRIANGLES);
    }

    #define MULTIK_RENDER_DRAWCALL(name, glval) DrawCall DrawCall::name() { return DrawCall(glval); }

    MULTIK_RENDER_DRAWCALL(Points, GL_POINTS);
    MULTIK_RENDER_DRAWCALL(Lines, GL_LINES);
    MULTIK_RENDER_DRAWCALL(Quads, GL_QUADS);
    MULTIK_RENDER_DRAWCALL(TriStrip, GL_TRIANGLE_STRIP);
    MULTIK_RENDER_DRAWCALL(TriFan, GL_TRIANGLE_FAN);
    MULTIK_RENDER_DRAWCALL(Polygon, GL_POLYGON);
    MULTIK_RENDER_DRAWCALL(LineStrip, GL_LINE_STRIP);

    #undef MULTIK_RENDER_DRAWCALL

    DrawCall DrawCall::LineStrip(bool loop)
    {
        return DrawCall(loop ? GL_LINE_LOOP : GL_LINE_STRIP);
    }
}
