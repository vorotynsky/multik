// Copyright (c) 2020 Vorotynsky Maxim

#include "entry.hpp"

int main(const int argc, const char **argv)
{
    std::cout << "Made with multik" << std::endl;

    multik::core::Application *app = multik::MainApplication();
    if (app == nullptr)
        return 1;
    
    app->Run();
    delete app;

    return 0;
}
