#include <iostream>
#include <map>


int *get_suffix_array(std::string str){

    std::map<std::string, size_t> map{};
    size_t len = str.length();

    for(size_t i{0}; i<len; i++){
        map.insert(std::make_pair(str.substr(i), i));
    }

    int *index = new int[len];

    auto it = map.begin();
    int i {0};
    while(it != map.end()) {
        index[i++] = it->second;
        it++;
    }

    return index;

}

int main(){
    std::string str{};
    std::cin >> str;
    
    int *arr = get_suffix_array(str+str);
    size_t len {(str+str).length()};

    for(size_t i{0}; i<len; i++) {
        if(arr[i] < str.length()) {
            std::cout << (str+str).substr(arr[i], str.length());
            break;
        }
    }
    
   

    return 0;
}












/**
 * @brief 
 * 
 * str = dcabca
 * dcabca ~ acbacd <- str2
 * sa...
 * lcp....[ int ]
 * len = 1
 * idx;
 * ...sa -> sa.i < str.len and sa.i+1 > str.len or opposite
 *  lcp.i > len -> len=lcp.i, idx=sa.i
 * 
 * 
 * str2[idx:len]
 * 
 * 
 */
