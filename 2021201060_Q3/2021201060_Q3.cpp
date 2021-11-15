#include <iostream>
#include <queue>

typedef long long ll;

struct Node{
    char bit{};
    Node *left {nullptr};
    Node *right {nullptr};
};

const int BIT_LENGTH = 42;

std::string get_binary_number(ll tmp) {
    std::string bin(BIT_LENGTH, '0');
    int i{BIT_LENGTH-1};
    while(tmp){
        int bit = tmp&1;
        bin.at(i) = '0'+bit;
        tmp >>= 1;
        i--;
    }
    return bin;
}

void build_trie(std::string binary, Node *root) {
    Node *p = root;
    for(int i{0}; i<BIT_LENGTH; i++){
        if(binary.at(i) == '0'){
            if(p->left==nullptr){
                Node *tmp = new Node;
                tmp->bit = '0';
                p->left = tmp;
            }
            p = p->left;
        }
        else {
            if(p->right==nullptr){
                Node *tmp = new Node;
                tmp->bit = '1';
                p->right = tmp;
            }
            p = p->right;
        }
    }
}

const int COUNT = 4;
void print(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print(root->right, space);
 
    // Print current node after space
    // count
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<<root->bit<<"\n";
 
    // Process left child
    print(root->left, space);
}

ll find_max_xor(Node *root, std::string binary) {
    ll resp{0};
    Node *p = root;
    for(auto &bit : binary) {
        if(bit == '0'){
            if(p->right){
                resp = 2*resp + 1;
                p = p->right;
            }
            else if(p->left){
                resp = 2*resp + 0;
                p = p->left;
            }
            else {
                break;
            }
        }
        else{
            if(p->left){
                resp = 2*resp + 1;
                p = p->left;
            }
            else if(p->right){
                resp = 2*resp + 0;
                p = p->right;
            }
            else {
                break;
            }
        }
    }

    return resp;
}

int main() {
    long long n{}, q{};
    std::cin >> n >> q;
    
    Node *node = new Node;
    node->bit = '0';

    ll i {n};
    while(i--){
        ll tmp;
        std::cin >> tmp;
        std::string binary = get_binary_number(tmp);
        build_trie(binary, node);
    }

    // print(node, 4);

    while(q--){
        ll tmp;
        std::cin >> tmp;
        std::string binary = get_binary_number(tmp);
        ll ans = find_max_xor(node, binary);
        std::cout << ans << std::endl;
    }
    
    return 0;
}