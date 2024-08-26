#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "Tree.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <stdexcept>

class Encoder {
private:
    Tree huffmanTree;

public:
    void encodeFile(const std::string& inputFilePath, const std::string& outputFilePath);
};

#endif // ENCODER_HPP

void Encoder::encodeFile(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::string inputStr((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    huffmanTree.build(inputStr);
    huffmanTree.extract_str_table();

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Failed to open output file.");
    }

    uint32_t tableSize = huffmanTree.get_str_table().size();
    outputFile.write(reinterpret_cast<const char*>(&tableSize), sizeof(tableSize));

    for (const auto& entry : huffmanTree.get_str_table()) {
        int chr = entry.first;
        const std::vector<bool>& code = entry.second;

        outputFile.write(reinterpret_cast<const char*>(&chr), sizeof(chr));

        uint32_t codeLength = code.size();
        outputFile.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));

        uint8_t byte = 0;
        int bitCount = 0;
        for (bool bit : code) {
            if (bit) byte |= (1 << (7 - bitCount));
            bitCount++;
            if (bitCount == 8) {
                outputFile.put(byte);
                byte = 0;
                bitCount = 0;
            }
        }
        if (bitCount > 0) {
            outputFile.put(byte);
        }
    }

    std::vector<bool> encodedBits = huffmanTree.compress_str(inputStr);

    uint32_t bitstreamLength = encodedBits.size();
    outputFile.write(reinterpret_cast<const char*>(&bitstreamLength), sizeof(bitstreamLength));

    uint8_t byte = 0;
    int bitCount = 0;
    for (bool bit : encodedBits) {
        if (bit) byte |= (1 << (7 - bitCount));
        bitCount++;
        if (bitCount == 8) {
            outputFile.put(byte);
            byte = 0;
            bitCount = 0;
        }
    }
    if (bitCount > 0) {
        outputFile.put(byte);
    }

    outputFile.close();
}

