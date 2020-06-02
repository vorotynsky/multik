// Copyright (c) 2020 Vorotynsky Maxim

#include "Parser.hpp"
#include <string>


CommandParser::CommandParser(std::istream &input)
    : input(input) { }

ICommand *CommandParser::next()
{
    std::string cmd, name;
    input >> cmd;
    if (cmd == "undo")
        return new Undo();

    input >> name;
    if (*name.begin() != '[' || *(name.end()-1) != ']')
        throw std::string("wrong command");

    if (cmd == "translate")
    {
        float x, y;
        input >> x >> y;
        return Command::transform(name, x, y);
    }
    if (cmd == "scale")
    {
        float x, y;
        input >> x >> y;
        return Command::scale(name, x, y);
    }
    if (cmd == "rotate")
    {
        float deg;
        input >> deg;
        return Command::rotate(name, deg); 
    }

    if (cmd == "line")
    {
        float p[4];
        for (int i = 0; i < 4; i++) input >> p[i];
        return new ConstructLine(name, p[0], p[1], p[2], p[3]);
        
    }
    if (cmd == "rect")
    {
        float p[4];
        for (int i = 0; i < 4; i++) input >> p[i];
        return new ConstructRect(name, p[0], p[1], p[2], p[3]);
    }
    if (cmd == "ellipse")
    {
        return new ConstructEllipse(name);
    }
    throw std::string("unexpected command");
}
