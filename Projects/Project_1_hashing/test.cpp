#include <iostream>

class abstractTest
{
public:
    virtual int testFunction() = 0;
    class nestedClass
    {
    protected:
        int n;

    public:
        nestedClass(int a = 0) : n(a) {}
        virtual nestedClass &operator++(){};
    };
};

class derrived : public abstractTest, public abstractTest::nestedClass
{
public:
    virtual int testFunction()
    {
        return n;
    }

    virtual abstractTest::nestedClass &operator++()
    {
        ++n;
        return *this;
    }
};

int main()
{
    derrived obj;

    obj.testFunction();
    ++obj;
    obj.testFunction();
}