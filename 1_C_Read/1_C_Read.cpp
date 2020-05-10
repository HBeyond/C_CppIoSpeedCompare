#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string file_path =
        "/home/beyoung/Desktop/mac-ubuntu-share/work/0_Mine/1_C++/18_readWriteSpeed/readWriteSpeed/data/read/101.txt";
    FILE* fp = fopen(file_path.c_str(), "r");
    if (!fp) {
        cout << "open file fail" << endl;
    }
    // get the size of the contents in file
    fseek(fp, 0, SEEK_END);  // set the pointer to the end
    int bufferSize = ftell(fp);
    cout << bufferSize << endl;
    fseek(fp, 0, SEEK_SET);  // set the pointer to the beginning
    fclose(fp);              // for time test, close it after get size
    // reopen and read
    vector<double> time;
    for (int var = 0; var < 10; ++var) {
        char* buffer = (char*)malloc(sizeof(char) * bufferSize);
        clock_t start = clock();
        fp = fopen(file_path.c_str(), "rb");
        fread(buffer, sizeof(char), bufferSize, fp);
        clock_t end = clock();
        cout << "tick_beforeMatch = " << double(end - start) / CLOCKS_PER_SEC << endl;
        time.emplace_back(double(end - start) / CLOCKS_PER_SEC);
        // output
        //        cout << buffer << endl;
    }
    double sum, mean;
    for (int var = 0; var < 10; ++var) {
        sum += time[var];
    }
    cout << "mean = " << sum / 10 << endl;

    return 0;
}
