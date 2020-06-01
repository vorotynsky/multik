// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <iostream>
#include "Command.hpp"

class CommandParser final
{
public:
    CommandParser(std::istream &input);
    CommandParser(const CommandParser&) = delete;

    ICommand *next();

private:
    std::istream &input;
};
