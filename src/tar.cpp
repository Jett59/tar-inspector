#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;

using std::ifstream;
using std::ios;

using std::string;
using std::memcmp;

using std::vector;

static inline int octalToBinary (unsigned char* octal, int size) {
    int result = 0;
    for (int i = 0; i < size; i ++) {
        result *= 8;
        result += octal [i] - '0';
    }
    return result;
}

class FileData {
    public:
    const unsigned int size;
    const string name;
    const void* data;
    FileData(unsigned int size, string name, void* data) : size(size), name(name), data(data) {}
};

void printFileData(unsigned char* archive, int fileSize) {
    int offset = 0;
    while (!memcmp(archive + offset, "ustar", 5)) {
        offset ++;
    }
    while (offset < fileSize) {
        cout << "File: " <<(archive + 345) << "/" << (archive + offset) << endl;
        int size = octalToBinary (archive + offset + 124, 11);
        cout << "Size: " << size << endl;
        offset += (size + 511) / 512 * 512 + 1;
    }
}

int main (int argc, char* argv []) {
    cout << "Tar Inspector" << endl;
    if (argc < 2) {
        cerr << "Please specify a file" << endl;
        return -1;
    }
    ifstream input;
    input.open(argv[1], ios::binary);
    if (!input) {
        cerr << "Error openning file!" << endl;
        return -1;
    }
    int fileSize = 0;
 vector<unsigned char> fileContent;
    while (!input.eof()) {
        char c;
        input >> c;
        fileContent.push_back(c);
        fileSize++;
    }
    input.close();
    printFileData(fileContent.data(), fileSize);
}
