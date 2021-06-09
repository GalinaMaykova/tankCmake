
#include <map>;
#include <any>;
#include <iostream>
#include "command.h"
#include "move.h"
#include "myVector.h"
#include "uobject.h"
#include "rotate.h"

#include "gmock\gmock.h"
class MockMOVE : public IMovable
{
public:
    MockMOVE(myVector& position, myVector& velocity) : m_position(position), m_velocity(velocity) {}
    myVector getPosition()
    {
        return m_position;
    }
    void setPosition(myVector value)
    {
        m_position = value;
    }
    myVector getVelocity()
    {
        return m_velocity;
    }
    myVector m_position;
    myVector m_velocity;
};

TEST(TANK_test, test_change_position)
{
    std::vector<int> p(2);
    p[0] = 12;
    p[1] = 5;
    myVector pos(p);
    std::vector<int> v(2);
    v[0] = -7;
    v[1] = 3;
    myVector vel(v);
    MockMOVE mock_mover(pos, vel);
    MoveCommand moveCmd(mock_mover);
    moveCmd.execute();
    ASSERT_EQ(5, mock_mover.getPosition().m_body[0]);
    ASSERT_EQ(8, mock_mover.getPosition().m_body[1]);
}

TEST(TANK_test, test_no_position)
// как с помощью мок-объекта проверить реальную функциональность MovableAdapter и выброс им исключения?
// вопрос по заданию: "невозможно прочитать положение у объекта" - имелось ввиду отсутствие положения как такового (свойства - position)?
{
    std::vector<int> v(2);
    v[0] = -7;
    v[1] = 3;
    myVector vel(v);
    UObject tank;
    tank.setObj("Velocity", vel);
    MovableAdapter mAdapter(tank);
    MoveCommand moveCmd(mAdapter);
    ASSERT_THROW(moveCmd.execute(), std::runtime_error);

}

TEST(TANK_test, test_no_velocity)
{
    std::vector<int> p(2);
    p[0] = 12;
    p[1] = 5;
    myVector pos(p);
    UObject tank;
    tank.setObj("Position", pos);
    MovableAdapter mAdapter(tank);
    MoveCommand moveCmd(mAdapter);
    ASSERT_THROW(moveCmd.execute(), std::runtime_error);
}

class MockMOVEPos : public MockMOVE
{
public:
    MockMOVEPos(myVector& position, myVector& velocity) : MockMOVE(position, velocity)
    {}
    void setPosition(myVector value)
    {
        std::cout << "TEST_ERR: MockMOVEPos - set position exeption" << std::endl;
        throw std::runtime_error("set position exeption");
    }
};


TEST(TANK_test, test_exption_set_position)
{
    std::vector<int> p(2);
    p[0] = 12;
    p[1] = 5;
    myVector pos(p);
    std::vector<int> v(2);
    v[0] = -7;
    v[1] = 3;
    myVector vel(v);
    MockMOVEPos mock_mover(pos, vel);
    MoveCommand moveCmd(mock_mover);
    ASSERT_THROW(moveCmd.execute(), std::runtime_error);
}




