#ifndef DECODER_HPP
#define DECODER_HPP

#include "Tree.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <stdexcept>

class Decoder {
private:
    Tree huffmanTree;

public:
    void decodeFile(const std::string& encodedFilePath, const std::string& outputFilePath);
};

#endif // DECODER_HPP

void Decoder::decodeFile(const std::string& encodedFilePath, const std::string& outputFilePath) {
    std::ifstream encodedFile(encodedFilePath, std::ios::binary);
    if (!encodedFile) {
        throw std::runtime_error("Failed to open encoded file.");
    }

    uint32_t tableSize;
    encodedFile.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));

    std::map<int, std::vector<bool>> strTable;
    for (uint32_t i = 0; i < tableSize; ++i) {
        int chr;
        encodedFile.read(reinterpret_cast<char*>(&chr), sizeof(chr));

        uint32_t codeLength;
        encodedFile.read(reinterpret_cast<char*>(&codeLength), sizeof(codeLength));

        std::vector<bool> code;
        uint8_t byte = 0;
        int bitCount = 0;
        for (uint32_t j = 0; j < codeLength; ++j) {
            if (bitCount == 0) {
                encodedFile.get(reinterpret_cast<char&>(byte));
            }
            code.push_back((byte & (1 << (7 - bitCount))) != 0);
            bitCount = (bitCount + 1) % 8;
        }
        strTable[chr] = code;
    }

    huffmanTree.bulid_from_table(strTable);

    uint32_t bitstreamLength;
    encodedFile.read(reinterpret_cast<char*>(&bitstreamLength), sizeof(bitstreamLength));

    std::vector<bool> encodedBits;
    char byte;
    int bitsRead = 0;
    while (encodedFile.get(byte)) {
        for (int i = 0; i < 8; ++i) {
            if (bitsRead < bitstreamLength) {
                encodedBits.push_back(byte & (1 << (7 - i)));
                bitsRead++;
            }
        }
        if (bitsRead >= bitstreamLength) break;
    }

    std::string decodedStr = huffmanTree.decompress_str(encodedBits);

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Failed to open output file.");
    }

    outputFile << decodedStr;
    outputFile.close();
}
