#include <iostream>
#include <map>

void get_suffix_array(std::string str, int *suffix_array, int *lcp, size_t len){

    std::map<std::string, size_t> map{};

    for(size_t i{0}; i<len; i++){
        map.insert(std::make_pair(str.substr(i), i));
    }

    auto it = map.begin();
    int i {0};
    std::string prev{}, curr{};
    while(it != map.end()) {
        suffix_array[i] = it->second;
        curr = it->first;
        int match{0};
        while(match<prev.length() && match<curr.length() && prev[match]==curr[match]){
            match++;
        }
        lcp[i] = match;
        i++;
        it++;
        prev = curr;
    }
}

int main(){
    std::string str{}, rstr{}, str_new{};
    std::cin >> str;

    for(auto &c:str){
        rstr = c + rstr;
    }
    str_new = str+'~'+rstr;

    size_t n = str_new.length();
    int *sa = new int[n];
    int *lcp = new int[n];

    get_suffix_array(str_new, sa, lcp, n);
    
    size_t len{0}, idx{0};
    for(size_t i{1}; i<str_new.length(); i++) {
        if((sa[i-1] < str.length() && sa[i] > str.length()) || 
            (sa[i-1] > str.length() && sa[i] < str.length())) {
                if(lcp[i] > len) {
                    len = lcp[i];
                    idx = sa[i];
                }
            }
    }

    std::cout << str_new.substr(idx, len) << std::endl;

    return 0;
}