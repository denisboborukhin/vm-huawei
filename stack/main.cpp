#include <iostream>

#include "stack.h"

int main ()
{
    my_containers::stack<int> stack (10);

    stack.push (3);
    stack.push (2);
    stack.pop ();

    stack.empty ();
    std::cout << stack.top () << '\n';
    std::cout << "size: " << stack.size () << '\n';

    my_containers::stack<int> stack2 {stack};
    
    stack2.push (5);
    std::cout << stack2.top () << "\nsize: " << stack2.size () << '\n';

    stack = stack2;

    stack.push (14);
    std::swap (stack, stack2);

    stack2.push (2);
    std::cout << stack2.size () << '\n';
    std::cout << stack2.empty () << '\n';
    stack2.pop ();
    stack2.pop ();
    std::cout << stack2.empty () << '\n';

    return 0;
}
