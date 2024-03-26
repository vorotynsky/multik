#pragma once

namespace multik::core
{
    class Application 
    {
    protected:
        Application() = default;

        virtual void Loop() = 0;
        virtual void Init() = 0;
        void Close()
        {
            run = false;
        }

    public:
        void Run()
        {
            Init();
            while(run)
                Loop();
        }

        virtual ~Application() = default;

    private:
        bool run = true;
    };
}
