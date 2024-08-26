#include <iostream>
#include <string>
#include "Decoder.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <encoded_file> <output_file>" << std::endl;
        return 1;
    }

    std::string encodedFilePath = argv[1];
    std::string outputFilePath = argv[2];

    Decoder decoder;
    try {
        decoder.decodeFile(encodedFilePath, outputFilePath);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
