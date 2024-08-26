#include <cstdint>
class tree_node
{
public:
    bool leaf;
    int chr;
    uint64_t freq;
    tree_node *left;
    tree_node *right;
    tree_node(uint64_t freq, tree_node *left, tree_node *right) : leaf(0), chr(0), freq(freq), left(left), right(right) {}
    tree_node(uint64_t freq) : leaf(0), chr(0), freq(freq), left(nullptr), right(nullptr) {}
    tree_node(int chr, uint64_t freq) : leaf(1), chr(chr), freq(freq), left(nullptr), right(nullptr) {}
    tree_node* merge(tree_node* left,tree_node* right){
        return new tree_node(right->freq+left->freq,left,right);
    }
};