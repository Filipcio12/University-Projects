#include <string>
#include <iostream>

class Employee {
    public:
        std::string name;
        std::string position;
        unsigned int age;
        
        Employee() {}

        Employee(std::string n, std::string pos, unsigned int a) : name(n), position(pos), age(a) {}

        friend std::ostream& operator<<(std::ostream& os, const Employee& e)
        {
            os << e.name << ", " << e.position << ", " << e.age;
            return os;
        }
};