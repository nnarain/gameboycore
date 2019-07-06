#pragma once

#include <memory>
#include <string>

//! View interface
class View
{
public:
    virtual std::string name() = 0;
    virtual void render() = 0;
};