// Copyright (c) 2020 Vorotynsky Maxim

#include "Command.hpp"
#include <gl.h>

Command *Command::transform(const std::string &name, float x, float y)
{
    auto cmd = new Command();
    cmd->matrix = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.0f));
    cmd->name = name;
    return cmd;
}

Command *Command::scale(const std::string &name, float x, float y)
{
    auto cmd = new Command();
    cmd->matrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    cmd->name = name;
    return cmd;
}

Command *Command::rotate(const std::string &name, float angle)
{
    auto cmd = new Command();
    cmd->matrix = glm::rotate(glm::mat4(1.0f), angle / 180.0f * 3.14f, glm::vec3(0, 0, 1));
    cmd->name = name;
    return cmd;
}

void Command::reverse()
{
    matrix = glm::inverse(matrix);
}

const std::string &Command::getName() const
{
    return this->name;
}

const glm::mat4 &Command::getMatrix() const
{
    return this->matrix;
}
