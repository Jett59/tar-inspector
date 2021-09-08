#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;

using std::ifstream;
using std::ios;

using std::string;

class FileData {
    public:
    const int size;
    const string name;
    const void* data;
    FileData(int size, string name, void* data) : size(size), name(name), data(data) {}
};

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
    string str;
    input >> str;
    cout << str << endl;
    input.close();
}
