#pragma once

#include "myVector.h"
#include "uobject.h"
#include <iostream>
class IMovable
{
public:
    virtual myVector getPosition() = 0;
    virtual void setPosition(myVector newPos) = 0;

    virtual myVector getVelocity() = 0;
    virtual ~IMovable() { /*std::cout << "IMovableDestructor" << std::endl;*/ };
};


class MovableAdapter : public IMovable
{
public:

    MovableAdapter(UObject& obj) :m_obj(obj)
    {}

    myVector getPosition()
    {
        try 
        {
            return  std::any_cast<myVector>(m_obj.getObj("Position"));
        }
        //getObj - может выбросить исключение отсутствие объекта, каст вектора - исключение несоответствия типов
        catch(std::out_of_range& ex)
        { 
            std::cout << "FATAL_ERR: no position in MovableObject, ex.what() = "  << ex.what() << std::endl;
            throw std::runtime_error("not position");
        }
        catch(std::bad_any_cast& ex)
        {
            std::cout << "FATAL_ERR: bad type position in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not position");
        }
    }

    void setPosition(myVector value)
    {
       m_obj.getObj("Position") = value;
    }
    myVector getVelocity()
    {
        try
        {
            return std::any_cast<myVector>(m_obj.getObj("Velosity"));
        }
        catch (std::out_of_range& ex)
        {
            std::cout << "FATAL_ERR: no velosity in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not position");
        }
        catch (std::bad_any_cast& ex)
        {
            std::cout << "FATAL_ERR: bad type velosity in MovableObject, ex.what() = " << ex.what() << std::endl;
            throw std::runtime_error("not position");
        }
    }

private:
        UObject& m_obj;
};

class MoveCommand : public Command
{
public:
    MoveCommand(IMovable& movable) : m_movable(movable)
    {}

    void execute()
    {
        myVector temp = m_movable.getPosition() + m_movable.getVelocity();
        m_movable.setPosition(temp);
    }

private:
    IMovable& m_movable;
};