// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>
#include <string>

struct ICommand 
{ 
    virtual ~ICommand() = default;
};

class Command final : public ICommand
{
public:
    static Command *transform(const std::string &name, float x, float y);
    static Command *scale(const std::string &name, float x, float y);
    static Command *rotate(const std::string &name, float angle);

    const std::string &getName() const;
    const glm::mat4 &getMatrix() const;

    void reverse();

    virtual ~Command() = default;
private:
    std::string name;
    glm::mat4 matrix;
};

struct Undo final : public ICommand
{ 
    Undo() = default;
    virtual ~Undo() = default;
};
