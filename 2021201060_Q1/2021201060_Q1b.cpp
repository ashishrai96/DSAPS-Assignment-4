#include <iostream>
#include <map>


long *get_suffix_array(std::string str){

    std::map<std::string, size_t> map{};
    size_t len = str.length();

    for(size_t i{0}; i<len; i++){
        map.insert(std::make_pair(str.substr(i), i));
    }

    long *index = new long[len];

    auto it = map.begin();
    long i {0};
    while(it != map.end()) {
        index[i++] = it->second;
        it++;
    }

    return index;

}

int main(){
    std::string str{};
    long k;
    std::cin >> str >> k;
    
    long *s_arr = get_suffix_array(str);
    size_t len {(str).length()};
    
    long max {-1};
    for(size_t i{0}; i<len-k+1; i++) {
        long start {s_arr[i]};
        long end {s_arr[i+k-1]};
        long t {0};
        while(start<len && end<len) {
            if(str[start] == str[end]){
                t++;
                start++;
                end++;
            }
        }
        
        max = (t>max)? t : max;
    }

    if(max == 0){
        max = -1;
    }

    std::cout << max << std::endl;

    return 0;
}