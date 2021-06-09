#include <map>;
#include <any>;
#include <iostream>
#include "command.h"
#include "move.h"
#include "myVector.h"
#include "uobject.h"
#include "rotate.h"

#include "gmock\gmock.h"

class MockROTATE : public IRotable
{
public:
    MockROTATE(int& direction, int& angularVelocity)
        : m_direction(direction), m_angularVelocity(angularVelocity) {}
    int getDirection()
    {
        return m_direction;
    }
    void setDirection(int value)
    {
        m_direction = value;
    }
    int getAngularVelocity()
    {
        return m_angularVelocity;
    }
    int m_direction;
    int m_angularVelocity;
};

TEST(TANK_test, test_change_direction)
{
    int dir = 45;
    int avel = 370;
    MockROTATE mock_rotate(dir, avel);
    RotateCommand rotateCmd(mock_rotate);
    rotateCmd.execute();
    ASSERT_EQ(55, mock_rotate.getDirection());
}

TEST(TANK_test, test_minus_change_direction)
{
    int dir = 45;
    int avel = -55;
    int maxdir = 360;
    MockROTATE mock_rotate(dir, avel);
    RotateCommand rotateCmd(mock_rotate);
    rotateCmd.execute();
    ASSERT_EQ(-10, mock_rotate.getDirection());
}


TEST(TANK_test, test_no_direction)
{
    int avel = 370;
    UObject tank;
    tank.setObj("AngularVelocity", avel);
    RotableAdapter rAdapter(tank);
    RotateCommand rotateCmd(rAdapter);
    ASSERT_THROW(rotateCmd.execute(), std::runtime_error);
}

TEST(TANK_test, test_no_angularVelocity)
{
    int dir = 45;
    UObject tank;
    tank.setObj("Direction", dir);
    RotableAdapter rAdapter(tank);
    RotateCommand rotateCmd(rAdapter);
    ASSERT_THROW(rotateCmd.execute(), std::runtime_error);
}

