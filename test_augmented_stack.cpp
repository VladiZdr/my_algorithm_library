#include <iostream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include "augmented_stack.h" 

using namespace std;

int main(){

//push pop tests
{
    AugmentedStack<int> s;

    s.push(5);
    s.push(3);
    s.push(8);
    s.push(2);
    s.push(7);

    assert(s.min() == 2);

    assert(s.pop() == 7);
    assert(s.min() == 2);

    assert(s.pop() == 2);
    assert(s.min() == 3);
}
//average tests
{
    AugmentedStack<int> s;

    bool threw = false;

    try {
        s.average();
    } catch (const underflow_error&) {
        threw = true;
    }

    assert(threw); //stack empty
}
{
    AugmentedStack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    assert(s.average() == 3); // (1+2+3+4+5)/5 = 3
}
//min tests
{
    AugmentedStack<int> s;

    bool threw = false;

    try {
        s.min();
    } catch (const underflow_error&) {
        threw = true;
    }

    s.push(10);
    s.push(4);
    s.push(6);

    assert(s.min() == 4);

    assert(threw);
}

    cout<<"All test passed";
}