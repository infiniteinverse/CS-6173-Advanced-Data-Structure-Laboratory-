#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

int main(){
    int status = std::system("mkdir opp");
    if(!status){
        // dir command is working 
        std::cout<< "Command executed successfully";
    }
    else{
        std::cout<< "Command executed unsuccessfully";

    }
    return 0;
}