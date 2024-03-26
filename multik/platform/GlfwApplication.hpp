#pragma once

#include <gl.h>
#include "../core/Application.hpp"

namespace multik::platform
{
    class GlfwApplication : public multik::core::Application
    {
    protected:
        void Loop() final;
        void Init() override;
        virtual void Draw() = 0;
        GlfwApplication(int width, int height);

    public:
        virtual ~GlfwApplication();

    private:
        int width;
        int height;
        GLFWwindow *window;
    };
}
