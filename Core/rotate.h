#pragma once

#include <iostream>
#include "myVector.h"
#include "uobject.h"
#include "command.h"

class IRotable
{
public:
    virtual int  getDirection() = 0;
    virtual void setDirection(int newPos) = 0;

    virtual int  getAngularVelocity() = 0;
  //  virtual int  getMaxDirections() = 0; // max_direction пока пусть будет 360, если позволить его менять на любое, то нужна дргуая логика в execute.
                                           // т.к например max_direction пользователь установит в 45, тогда при повороте на 50 градусов игрок 
                                           // будет явно удивлен повороту на 5 градусов. в будущем скорре надо добавить диапазон возможных поворотов к текущему положению.
    virtual ~IRotable() { /*std::cout << "IRotableDestructor" << std::endl;*/ };
};


class RotableAdapter : public IRotable
{
public:

    RotableAdapter(UObject& obj) :m_obj(obj)
    {}

    int getDirection()
    {
        try
        {
            return std::any_cast<int>(m_obj.getObj("Direction"));
        }
        catch (std::out_of_range& ex)
        {
            std::cout << "FATAL_ERR: no direction in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not direction");
        }
        catch (std::bad_any_cast& ex)
        {
            std::cout << "FATAL_ERR: bad type direction in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not direction");
        }
    }

    void setDirection(int value)
    {
        m_obj.getObj("Direction") = value;
    }
    int getAngularVelocity()
    {
        try
        {
            return std::any_cast<int>(m_obj.getObj("AngularVelocity"));
        }
        catch (std::out_of_range& ex)
        {
            std::cout << "FATAL_ERR: no angularVelocity in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not angularValocity");
        }
        catch (std::bad_any_cast& ex)
        {
            std::cout << "FATAL_ERR: bad type angularVelocity in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not angularValocity");
        }
    }

private:
    UObject& m_obj;
};

class RotateCommand : public Command
{
public:
    RotateCommand(IRotable& rotable) : m_rotable(rotable)
    {}

    void execute()
    {
        int temp = (m_rotable.getDirection() + m_rotable.getAngularVelocity()) % 360;
        m_rotable.setDirection(temp);
    }

private:
    IRotable& m_rotable;
};