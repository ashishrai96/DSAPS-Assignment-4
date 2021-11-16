#include <iostream>
#include <map>

int main(){
    std::map<std::string, size_t> map{};
    std::string str{};

    std::cin >> str;
    size_t len = str.length();
    str += str;

    for(size_t i{0}; i<str.length(); i++){
        map.insert(std::make_pair(str.substr(i), i));
    }

    auto it = map.begin();
    while(it != map.end()){
        if(it->second < len){
            std::cout << it->first.substr(0, len) << std::endl;
            break;
        }
        it++;
    }
    
    // it = map.begin();
    // while(it != map.end()){
    //     std::cout << it->first << " " << it->second << std::endl;
    //     it++;
    // }

    return 0;
}