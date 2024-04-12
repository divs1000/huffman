#include<map>
#include<unordered_map>
#include<stack>
#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<functional>
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
class Tree{
    tree_node* root=nullptr;
    std::map<int,std::string> str_table;
public:
    Tree(){}
    void build(std::string& str){
        if(str.size()<2){
            std::cerr<<"Atleast two elements are required."<<std::endl;
            exit(4);
        }
        std::unordered_map<int,uint64_t> freq_table;
        for(auto chr:str)freq_table[chr]++;
        auto cmp=[](tree_node* a,tree_node* b){
            if(a->freq!=b->freq)return a->freq>b->freq;
            return a->chr<b->chr;
        };
        std::priority_queue<tree_node*,std::vector<tree_node*>,std::function<bool(tree_node*,tree_node*)>> heap(cmp);
        for(auto it:freq_table)heap.push(new tree_node(it.first,it.second));
        while(heap.size()>1){
            tree_node* node1=heap.top();
            heap.pop();
            tree_node* node2=heap.top();
            heap.pop();
            tree_node* a=node1->merge(node2,node1);
            heap.push(a);
        }
        root=heap.top();
    }
    void extract_str_table_recur(tree_node* node,std::string str){
        if(node==nullptr){
            std::cerr<<"Something went wrong in Tree::extract"<<std::endl;
            exit(1);
        }
        if(node->left==nullptr&&node->right==nullptr){
            if(!node->leaf){
                std::cerr<<"Something went wrong in Tree::extract"<<std::endl;
                exit(2);
            }
            str_table[node->chr]=str;
            return;
        }
        str.push_back('0');
        extract_str_table_recur(node->left,str);
        str.back()='1';
        extract_str_table_recur(node->right,str);
    }
    void extract_str_table(){
        extract_str_table_recur(root,std::string());
    }
    std::string compress_str(std::string& str){
        std::string out_str;
        for(auto chr:str){
            out_str+=str_table[chr];
        }
        return out_str;
    }
    std::string decompress_str(std::string& input_str){
        std::string result;
        for(int i=0;i<input_str.size();){
            tree_node* node=root;
            if(root->leaf){
                std::cerr<<"Something went wrong in Tree::get_str"<<std::endl;
                exit(3);
            }
            while(!node->leaf){
                if(input_str[i]=='0')node=node->left;
                else node=node->right;
                i++;
            }
            result.push_back(char(node->chr));
        }
        return result;
    }
};
int main(){
    std::string s;
    std::cin>>s;
    Tree t;
    t.build(s);
    t.extract_str_table();
    auto v=t.compress_str(s);
    std::cout<<v<<std::endl;
    std::cout<<t.decompress_str(v)<<std::endl;
    std::cout<<float(v.size())/s.size()<<std::endl;
}