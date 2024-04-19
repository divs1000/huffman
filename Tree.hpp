#include <map>
#include <unordered_map>
#include <stack>
#include <Tree_node.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
class Tree
{
    tree_node *root = nullptr;
    std::map<int, std::vector<bool>> str_table;

public:
    Tree() {}
    std::map<int, std::vector<bool>> get_str_table()
    {
        return str_table;
    }
    void build(std::string &str)
    {
        if (str.size() < 2)
        {
            std::cerr << "Atleast two elements are required." << std::endl;
            exit(4);
        }
        std::unordered_map<int, uint64_t> freq_table;
        for (auto chr : str)
            freq_table[chr]++;
        auto cmp = [](tree_node *a, tree_node *b)
        {
            if (a->freq != b->freq)
                return a->freq > b->freq;
            return a->chr > b->chr;
        };
        std::priority_queue<tree_node *, std::vector<tree_node *>, std::function<bool(tree_node *, tree_node *)>> heap(cmp);
        for (auto it : freq_table)
            heap.push(new tree_node(it.first, it.second));
        while (heap.size() > 1)
        {
            tree_node *node1 = heap.top();
            heap.pop();
            tree_node *node2 = heap.top();
            heap.pop();
            heap.push(node1->merge(node2));
        }
        root = heap.top();
    }
    void extract_str_table(tree_node *node, std::vector<bool> str)
    {
        if (node == nullptr)
        {
            std::cerr << "Something went wrong in Tree::extract" << std::endl;
            exit(1);
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            if (!node->leaf)
            {
                std::cerr << "Something went wrong in Tree::extract" << std::endl;
                exit(2);
            }
            str_table[node->chr] = str;
            return;
        }
        str.push_back(0);
        extract_str_table(node->left, str);
        str.back() = 1;
        extract_str_table(node->right, str);
    }
    std::vector<bool> compress_str(std::string &str)
    {
        std::vector<bool> out_str;
        for (auto chr : str)
            out_str.emplace_back(str_table[int(chr)]);
        return out_str;
    }
    std::string decompress_str(std::vector<bool> &input_str)
    {
        std::string result;
        for (int i = 0; i < input_str.size();)
        {
            tree_node *node = root;
            if (root->leaf)
            {
                std::cerr << "Something went wrong in Tree::decompress_str" << std::endl;
                exit(3);
            }
            while (!node->leaf)
            {
                if (input_str[i] == 0)
                    node = node->left;
                else
                    node = node->right;
                i++;
            }
            result.push_back(char(node->chr));
        }
        return result;
    }
    void build_from_str(int chr, std::vector<bool> &str)
    {
        if (root == nullptr)
            root = new tree_node(0, nullptr, nullptr);
        tree_node *curr = root;
        for (int i = 0; i < str.size(); i++)
        {
            if (i == str.size() - 1)
            {
                if (str[i] == 0)
                {
                    if (curr->left == nullptr)
                        curr->left = new tree_node(chr, 0);
                    else
                        curr = curr->left;
                }
                else
                {
                    if (curr->right == nullptr)
                        curr->right = new tree_node(chr, 0);
                    else
                        curr = curr->right;
                }
            }
            if (str[i] == 0)
            {
                if (curr->left == nullptr)
                    curr->left = new tree_node(0, nullptr, nullptr);
                else
                    curr = curr->left;
            }
            else
            {
                if (curr->right == nullptr)
                    curr->right = new tree_node(0, nullptr, nullptr);
                else
                    curr = curr->right;
            }
        }
    }
    void bulid_from_table(std::map<int, std::vector<bool>> &str_table)
    {
        for (auto i : str_table)
            this->build_from_str(i.first, i.second);
    }
};
