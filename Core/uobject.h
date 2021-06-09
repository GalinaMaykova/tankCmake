#pragma once

#include <map>;
#include <any>;

class UObject
{
public:
    std::any& getObj(std::string key) // ������ ���������� ������ �� ������, ����� ��������� ����������
    {
            return m_uobj.at(key);
    }

    void setObj(std::string key, std::any ptr)
    {
        m_uobj.insert(std::make_pair(key, ptr));
    }
    std::map<std::string, std::any> m_uobj;
};
