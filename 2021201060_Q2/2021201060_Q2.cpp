#include <iostream>
#include <vector>
#include <fstream>

typedef long long ll;

const int SEGMENT_SIZE = 1000;

class Node {
public:
    ll val {};
    std::string fname {};
    size_t fidx {};

    bool operator<(Node r){
        return this->val < r.val;
    }
};

void minHeapify(std::vector<Node> &vec, size_t i){
    size_t l = 2*i + 1;
    size_t r = 2*i + 2;
    size_t n = vec.size();

    size_t smallest = i;
    if(l < n && vec[l] < vec[smallest]){
        smallest = l;
    }

    if(r < n && vec[r] < vec[smallest]){
        smallest = r;
    }

    if(smallest != i){
        std::swap(vec[i], vec[smallest]);
        minHeapify(vec, smallest);
    }
}

void buildMinHead(std::vector<Node> &vec){
    ll n = vec.size();
    for(ll i{n/2}; i>=0; i--){
        minHeapify(vec, i);
    }
}

Node *extractMin(std::vector<Node> &vec){
    size_t n = vec.size();
    if(n < 0){
        return nullptr;
    }

    Node *min = new Node;
    *min = vec[0];
    vec[0] = vec[n-1];
    vec.pop_back();
    minHeapify(vec, 0);
    return min;
}

void write_temp_files(std::string fname, std::vector<ll> &vec){
    std::sort(vec.begin(), vec.end());
    std::ofstream ofs {};
    ofs.open(fname, std::ios::out|std::ios::app);
    for(size_t i{0}; i<vec.size(); i++){
        ofs << vec[i];
        if(i != vec.size()-1)
            ofs << ",";
    }
    vec.clear();
    ofs.close();
}

void create_temp_files(std::string &in_file, std::vector<std::string> &temp_files){
    std::ifstream fin {in_file, std::ios::in};
    long count {0};
    std::vector<ll> vec{};
    std::string buff{};
    while(std::getline(fin, buff, ',')){
        ll num = stoll(buff);
        vec.push_back(num);
        if(vec.size() == SEGMENT_SIZE){
            temp_files.push_back("temp"+std::to_string(count)+".txt");
            write_temp_files("temp"+std::to_string(count)+".txt", vec);
            count++;
        }
    }
    if(vec.size() != 0){
        temp_files.push_back("temp"+std::to_string(count)+".txt");
        write_temp_files("temp"+std::to_string(count)+".txt", vec);
    }

    fin.close();
}

int main(int argv, char *args[]){
    std::string in_file {args[1]};
    std::string out_file {args[2]};

    std::ofstream fout {out_file, std::ios::out|std::ios::app};

    std::vector<std::string> temp_files{};

    create_temp_files(in_file, temp_files);

    std::ifstream ifs {};
    std::vector<std::ifstream> vec_ifs(temp_files.size());

    for(size_t i{0}; i<temp_files.size(); i++){
        vec_ifs[i].open(temp_files[i], std::ios::in);
    }

    std::vector<Node> heap(temp_files.size());
    std::string buff{};
    for(size_t i{0}; i<vec_ifs.size(); i++){
        std::getline(vec_ifs[i], buff, ',');
        Node node{};
        node.val = stoll(buff);
        node.fname = temp_files[i];
        node.fidx = i;
        heap[i] = node;
    }

    while(heap.size()){
        buildMinHead(heap);
        Node *ptr = extractMin(heap);
        size_t j = ptr->fidx;
        fout << ptr->val;

        if(std::getline(vec_ifs[j], buff, ',')){
            Node node{};
            node.val = stoll(buff);
            node.fname = temp_files[j];
            node.fidx = j;
            heap.push_back(node);
        }
        
        if(heap.size()!=0){
            fout << ",";
        }
    }
    fout.close();

    for(auto &a:temp_files){
        remove(a.c_str());
    }

    return 0;
}