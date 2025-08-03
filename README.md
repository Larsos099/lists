# lists

## Table of Contents
### How to install *lists*
### How to use *lists*


## How to install *lists*?
Just simply drag in the three header files into your project, include them and you're ready to use *lists*


## How to use *lists*?

You just need to create an LinkedList / CircularLinkedList object and you can use it easily.
```cpp
#include <iostream>
#include "LinkedList.hpp"
int main(int argc, char** argv) {
    lists::LinkedList list;
    list.push_back(7);
    list.push_front(6);
    int a = list.get_by_index(0);
    int b = list.get_by_index(1);
    std::cout << "first: " << a << std::endl << "second: " << b << std::endl;
    return 0;
}
```


```sh
./example
first: 6
second: 7
```