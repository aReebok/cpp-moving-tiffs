#include <bits/stdc++.h>

#include <iostream>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <vector>

using namespace std;

/* 
File takes the given spreadsheet and rearranges items accordingly
usage: 

$ g++ main.cpp 
$ ./a.out 

*/
void print_vector(vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << "\t";
    }
    cout << endl;
}
  
void create(vector<vector<string>> files){
    /* creates replicate_# directories and "fake" .tiff text files */

    vector<string> directories;     /* holds the strings to replicate_#*/

    for (int i = 1; i <= 4; i++){
        string fname = files.at(0).at(i);
        directories.push_back(fname);

        // cout << "fname\" "<< fname << "\" len: " << fname.length() << endl;

        char fname_char[fname.length() + 1];
        strcpy(fname_char, fname.c_str());
        fname_char[fname.length()] = '\0';

        if (mkdir(fname_char, 0777) == -1)
            cerr << "Error :  " << strerror(errno) << endl;
        else cout << "Directory created";

    }

    // takes int and creates a file with it inside each replicant
    // the content of the files is n, 6, or 8 

    // cout << "directories: ";   
    // print_vector(directories);

    for (int dir = 0; dir < directories.size(); dir++){
        ofstream tif;
        tif.open;
    }

}

int main() {  

    ifstream f("06.11.2021_DG5248_GFP_OLLAS_MSP.csv");

    vector<vector<string>> csv;
    vector<string> directories;

    if(f.is_open()) {
        string line, val;

        // creating 2d array using vector
        while(getline(f, line)){
            int count = 0;
            vector<string> n;
            stringstream s (line);
            while(getline(s, val, ',')){
                count++;
                if (count == 5) {
                    n.push_back(val.substr(0, val.length()-1));
                } else {
                    n.push_back(val);
                }
            }
            csv.push_back(n);
            // cout << line << "\n";
        }
        f.close(); // file has been read, can be closed
    } else {
        cout << "file did not open" << endl;
    }

    for(int i = 0; i < csv.size(); i++){  /* prints out all values in csv file */
        print_vector(csv.at(i));
    }
    
    create(csv);

    return 0;
}