#include <iostream>
#include "lambda.h"
#include <ctime>

int main() {
    Abstraction* abstract = new Abstraction(
        new Variable('x'),
        new Variable('x')
    );
    Abstraction* abstract2 = new Abstraction(
        new Variable('x'),
        new Variable('y')
    );
    Abstraction* abstract3 = new Abstraction(
        new Variable('x'),
        new Abstraction(
            new Variable('y'),
            new Variable('x')
        )
    );
    Abstraction* abstract4 = new Abstraction(
        new Variable('x'),
        new Abstraction(
            new Variable('y'),
            new Abstraction(
                new Variable('x'),
                new Variable('z')
            )
        )
    );
    Abstraction* abstract5 = new Abstraction(
        new Variable('x'),
        new Abstraction(
            new Variable('x'),
            new Abstraction(
                new Variable('x'),
                new Variable('x')
            )
        )
    );

    Application* application = new Application(abstract, new Variable('o'));
    Application* application2 = new Application(abstract2, new Variable('o'));
    Application* application3 = new Application(abstract3, new Variable('o'));
    Application* application4 = new Application(abstract4, new Variable('o'));
    Application* application5 = new Application(abstract5, new Variable('o'));

    std::cout << application->to_str() << " -> ";
    std::cout << application->evaluate()->to_str() << std::endl;
    std::cout << application2->to_str() << " -> ";
    std::cout << application2->evaluate()->to_str() << std::endl;
    std::cout << application3->to_str() << " -> ";
    std::cout << application3->evaluate()->to_str() << std::endl;
    std::cout << application4->to_str() << " -> ";
    std::cout << application4->evaluate()->to_str() << std::endl;
    std::cout << application5->to_str() << " -> ";
    std::cout << application5->evaluate()->to_str() << std::endl;
}
