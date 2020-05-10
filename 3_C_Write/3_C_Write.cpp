#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string file_path =
        "/home/beyoung/Desktop/mac-ubuntu-share/work/0_Mine/1_C++/18_readWriteSpeed/readWriteSpeed/data/read/101.txt";
    string save_path =
        "/home/beyoung/Desktop/mac-ubuntu-share/work/0_Mine/1_C++/18_readWriteSpeed/readWriteSpeed/data/write";
    // read
    FILE* fp = fopen(file_path.c_str(), "rb");
    if (!fp) {
        cout << "open file fail" << endl;
    }
    // get the size of the contents in file
    fseek(fp, 0, SEEK_END);  // set the pointer to the end
    int bufferSize = ftell(fp);
    cout << bufferSize << endl;
    fseek(fp, 0, SEEK_SET);  // set the pointer to the beginning
    char* buffer = (char*)malloc(sizeof(char) * bufferSize);
    fp = fopen(file_path.c_str(), "r");
    fread(buffer, sizeof(char), bufferSize, fp);
    // output
    //    cout << buffer << endl;
    // write
    vector<double> time;
    for (int var = 0; var < 10; ++var) {
        string save_name = save_path + "/C_write_" + to_string(var) + ".txt";
        clock_t start = clock();
        FILE* fp2 = fopen(save_name.c_str(), "w");
        if (!fp2) {
            cout << "open file fail" << endl;
        }
        fwrite(buffer, sizeof(char), bufferSize, fp2);
        fclose(fp2);
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
