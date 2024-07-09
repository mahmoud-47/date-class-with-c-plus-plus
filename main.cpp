#include "date.hpp"

int main(){
    try{
        // date d;
        // date d1("12-9-2001");
        // // date demain = d1.next();
        // date demain = d1 - (-2);
        // // date hier = d1.previous();
        // std::cout << demain << std::endl;
        // // std::cout << hier << std::endl;

        date d1("15-12-2008");
        date x(1, 12, 2008);
        date d2("16-12-2008");

        int diff = d1 - d2;
        std::cout << diff << std::endl;

        std::cout << (d1 < d2) << std::endl;

    }catch(DateException d){
        std::cout << "Error : " << d.get_message() << std::endl;
    }

    return 0;
}