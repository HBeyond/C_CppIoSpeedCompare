#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string targetPath =
        "/home/beyoung/Desktop/mac-ubuntu-share/work/0_Mine/1_C++/18_readWriteSpeed/readWriteSpeed/data/read/101.bin";
    ifstream rfs(targetPath, ios::in | ios::binary);
    if (!rfs.is_open()) {
        cout << "open file fail" << endl;
    }
    // get the data lengh
    streampos pos = rfs.tellg();
    rfs.seekg(0, ios::end);
    int bufSize = rfs.tellg();
    rfs.seekg(pos);
    rfs.close();
    cout << bufSize << endl;
    // reopen and read
    for (int var = 0; var < 10; ++var) {
        ifstream rfs2(targetPath, ios::in | ios::binary);
        char* rBuffer = (char*)malloc(sizeof(char) * bufSize);
        clock_t start = clock();
        rfs2.read(rBuffer, bufSize);
        clock_t end = clock();
        cout << "tick_beforeMatch = " << double(end - start) / CLOCKS_PER_SEC << endl;
        // output
        //        cout << rBuffer << endl;
    }

    return 0;
}
