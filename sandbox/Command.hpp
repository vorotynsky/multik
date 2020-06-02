// Copyright (c) 2020 Vorotynsky Maxim

#pragma once

#include <gl.h>
#include <string>
#include <multik/types/reference.hpp>
#include <multik/graphics/Shape.hpp>

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

class ConstructCommand : public ICommand 
{
public:
    virtual ~ConstructCommand() = default;
    const std::string &getName() const;
    virtual typename multik::Uniq<multik::graphics::Shape> shape() const = 0;

protected:
    ConstructCommand(const std::string &name);
private:
    std::string name;
};

struct ConstructLine : public ConstructCommand
{
    ConstructLine(const std::string &name, float x, float y, float h, float w);
    typename multik::Uniq<multik::graphics::Shape> shape() const override;

private:
    float x, y, h, w;
};

struct ConstructRect : public ConstructCommand
{
    ConstructRect(const std::string &name, float x, float y, float h, float w);
    typename multik::Uniq<multik::graphics::Shape> shape() const override;

private:
    float x, y, h, w;
};

struct ConstructEllipse : public ConstructCommand
{
    ConstructEllipse(const std::string &name);
    typename multik::Uniq<multik::graphics::Shape> shape() const override;
};
