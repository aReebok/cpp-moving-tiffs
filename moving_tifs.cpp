#include <bits/stdc++.h>

#include <iostream>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <experimental/filesystem>

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

string add_zeros(string s){
    int len = s.length();
    for (int i = 0; i < (3 - (len % 3)) % 3 ; i++) 
        s = "0" + s;    
    return s;
}

string create_filename(string n){
    // where n is a number, i.e 1, 3, 5..
    string filename, prefix, suffix;
    
    suffix = to_string(stoi(n) + 1);

    prefix = add_zeros(n);
    suffix = add_zeros(suffix) + ".tif";
    filename = prefix + "-" + suffix;    
    
    // now to do the same with 
    return filename;
}
  
void create(vector<vector<string>> files){
    /* creates replicate_# directories and "fake" .tiff text files -
        for the sake of testing this code on smaller tif files.  */

    vector<string> directories;     /* holds the strings to replicate_#*/

    for (int i = 1; i <= 4; i++){
        string fname = files.at(0).at(i);
        directories.push_back(fname);

        // cout << "fname\" "<< fname << "\" len: " << fname.length() << endl;

        char fname_char[fname.length() + 1];
        strcpy(fname_char, fname.c_str());

        if (mkdir(fname_char, 0777) == -1)
            cerr << "Error :  " << strerror(errno) << endl;
        // else cout << "Directory created";

    }

    // takes int and creates a file with it inside each replicant
    // the content of the files is n, 6, or 8 

    // cout << "directories: ";   
    // print_vector(directories);

    for (int row = 1; row < files.size(); row++){
        string file_int = files.at(row).at(0); 
        for (int dir = 0; dir < directories.size(); dir++){
            string file_content = files.at(row).at(dir + 1);
            if (!file_content.empty()) {
                string filename = directories.at(dir) + "/";

                filename = filename + create_filename(file_int);

                ofstream tif;
                tif.open(filename);
                tif << file_content << "\n";
                tif.close();
            }
        }

    }
}

vector<vector<string>> file_to_vector(string file) {
    /* takes in a string pointing to a csv file 
        that is then put into a 2d vector and returned */
    ifstream f(file);
    vector<vector<string>> v;

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
            v.push_back(n);
            // cout << line << "\n";
        }
        f.close(); // file has been read, can be closed
    } else {
        cout << "file did not open" << endl;
    }

    return v;
}

void create_directory(string s){
    // cout << "dirname: " << s;
    char dir[s.length() + 1];
    strcpy(dir, s.c_str());

    if (mkdir(dir, 0777) == -1)
        cerr << "Error :  " << strerror(errno) << endl;
    // else cout << "Directory created\n";
}

void sort_files(vector<vector<string>> v){

    vector<string> directories;

    for (int i = 1; i <= 4; i++){
        string fname = v.at(0).at(i);
        directories.push_back(fname);

        create_directory(fname + "/N2");
        create_directory(fname + "/SYGL-1_OLLAS_DG5136");
        create_directory(fname + "/SYGL-1_OLLAS_DG5249");

    }

    for (int row = 1; row < v.size(); row++){
        string file_int = v.at(row).at(0); 
        for (int dir = 0; dir < directories.size(); dir++){
            string file_content = v.at(row).at(dir + 1);
            if (!file_content.empty()) {
                // then file exists:
                string filename = directories.at(dir) + "/";
                string prefix = filename; // holds on to replicate_#/
                string suffix = create_filename(file_int);
                filename = filename + suffix;

                char char_filename[filename.length()+1];
                    //    char fname_char[fname.length() + 1];
                strcpy(char_filename, filename.c_str());

                // change filename to move it. 
                string new_filename;

                if(!file_content.compare("n")) { 
                    // set folder name to replicate_#/N2/
                    new_filename = prefix + "N2/" + suffix; 
                    char char_new_filename[filename.length()+new_filename.length()];
                    strcpy(char_new_filename, new_filename.c_str());

                    if(rename(char_filename, char_new_filename) < 0){
                        cout << strerror(errno) << endl;
                    }
                } else if(!file_content.compare("6")) {
                    // set folder name to replicate_#/N2/
                    new_filename = prefix + "SYGL-1_OLLAS_DG5136/" + suffix;
                    char char_new_filename[filename.length()+new_filename.length()];
                    strcpy(char_new_filename, new_filename.c_str());

                    if(rename(char_filename, char_new_filename) < 0){
                    cout << strerror(errno) << endl;
                    }
                } else if (!file_content.compare("8")) {
                    // set folder name to replicate_#/N2/
                    new_filename = prefix + "SYGL-1_OLLAS_DG5249/" + suffix;
                    char char_new_filename[filename.length()+new_filename.length()];
                    strcpy(char_new_filename, new_filename.c_str());

                    if(rename(char_filename, char_new_filename) < 0){
                        cout << strerror(errno) << endl;
                    }
                } else {
                    // do nothing 
                }
            }
        }
    }

}

int main() {  
    // string num = "1";  // test code fo create_filename func.
    // cout << "filename: " << create_filename(num) << endl;

    vector<vector<string>> csv;
    csv = file_to_vector("06.11.2021_DG5248_GFP_OLLAS_MSP.csv");
    
    create(csv); /* creates fake directories and 
            correspoding files in them to organize*/

    sort_files(csv);
 

    return 0;
}