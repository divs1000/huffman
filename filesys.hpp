#include<Tree.hpp>
#include<fstream>
#include<filesystem>
namespace fs=std::filesystem;
class encoder{
    Tree tree;
    std::string in_str;
    std::vector<bool> out_str;
public:
    void in_file(fs::path input_path){
        int start,stop,size;
        std::ifstream fin(input_path,std::ios::binary);
        if(!fin.is_open()){
            std::cout<<"Could not open file."<<std::endl;
            return;
        }
        fin.seekg(0, std::ios::beg);
        start = fin.tellg();
        fin.seekg(0, std::ios::end);
        stop = fin.tellg();
        fin.seekg(0, std::ios::beg);
        size=stop-start;
        char* data=new char[size];
        fin.read(data,size);
        in_str=data;
        delete data;
        tree.build(in_str);
        tree.extract_str_table();
        out_str=tree.compress_str(in_str);
    }
    void out_file(fs::path output_path){
        std::ofstream fout(output_path,std::ios::binary);
        if(!fout.is_open()){
            std::cout<<"Could not write into file."<<std::endl;
            return;
        }
        
    }
};