#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string file_path =
        "/home/beyoung/Desktop/mac-ubuntu-share/work/0_Mine/1_C++/18_readWriteSpeed/readWriteSpeed/data/read/101.bin";
    string save_path =
        "/home/beyoung/Desktop/mac-ubuntu-share/work/0_Mine/1_C++/18_readWriteSpeed/readWriteSpeed/data/write";
    // read
    ifstream rfs(file_path, ios::in | ios::binary);
    if (!rfs.is_open()) {
        cout << "open file fail" << endl;
    }
    // get the data lengh
    streampos pos = rfs.tellg();
    rfs.seekg(0, ios::end);
    int bufSize = rfs.tellg();
    rfs.seekg(pos);
    char* buffer = (char*)malloc(sizeof(char) * bufSize);
    rfs.read(buffer, bufSize);
    rfs.close();
    // output
    //    cout << buffer << endl;
    // write
    vector<double> time;
    for (int var = 0; var < 10; ++var) {
        string save_name = save_path + "/Cpp_write_" + to_string(var) + ".bin";
        clock_t start = clock();
        fstream wfs(save_name, ios::out | ios::binary);
        if (!wfs.is_open()) {
            cout << "open file fail" << endl;
        }
        wfs.write(buffer, bufSize);
        wfs.close();
        clock_t end = clock();
        cout << "tick_beforeMatch = " << double(end - start) / CLOCKS_PER_SEC << endl;
        time.emplace_back(double(end - start) / CLOCKS_PER_SEC);
    }
    // get mean
    double sum = 0;
    for (int var = 0; var < 10; ++var) {
        sum += time[var];
    }
    double mean = sum / double(9.0);
    cout << "mean = " << mean << endl;
    return 0;
}
