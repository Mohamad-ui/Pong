#ifndef UTILS_Hpp
#define UTILS_Hpp

#include <iostream>


template<typename...Args>
    void println(Args... args) {
        (std::cout <<... << args) << std::endl;
        }    

template<typename...Args>
    void print(Args... args) {
        (std::cout <<... << args);
        }    
    
template<typename...Args>
    void input(Args&... args) {
        (std::cin >>... >> args);
        }        
    

#endif
