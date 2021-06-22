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
  
void create(vector<string> dirs, vector<vector<string>> files){
    /* creates replicate directories and "fake" .tiff text files */

    
    // Creating directories..
    for (int i = 0; i < dirs.size(); i++){
        string dir_string = dirs.at(i);
        cout << "dir_string\" "<< dir_string << "\" len: " << dir_string.length() << endl;

        char dir_char[dir_string.length() + 1];
        strcpy(dir_char, dir_string.c_str());
        dir_char[dir_string.length()] = '\0';



        if (mkdir(dir_char, 0777) == -1)
            cerr << "Error :  " << strerror(errno) << endl;
        else cout << "Directory created";
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
                n.push_back(val);
            }
            csv.push_back(n);
            // cout << line << "\n";
        }
        f.close(); // file has been read, can be closed
    } else {
        cout << "file did not open" << endl;
    }

    for(int i = 0; i < csv.size(); i++){  /* prints out all values in csv file */
        for (int j = 0; j < csv.at(i).size(); j++) {
             cout << csv.at(i).at(j) << "\t";
        }
        cout << endl;
    }
    
    // create(directories, csv);
    return 0;
}