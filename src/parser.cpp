#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::string row;
    std::ifstream in;
    in.open("");
    while(!in.eof()){
        in >> row;
    }
    in.close();
    return 0;
}