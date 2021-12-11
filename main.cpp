﻿#include "utils.hpp"

#include <cstdio>
#include <iostream>
using namespace std;

enum class Op_Type {
    Zip,
    Unzip,
    Help,
    Unsure
};

//#define TEST

#ifdef TEST
#include "test.hpp"
#endif

int main(int argc, const char* argv[]) {
#ifndef TEST
    Vector<string> input_files;
    string output_file;
    Op_Type opType = Op_Type::Unsure;
    int size = 8, branch = 2;
    if (argc == 1) {
        cout << get_help(string(argv[0]));
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            cout << "Huffman Zip: Unrecognized option or setting: \"" << argv[i] << '\"' << endl;
            return 1;
        }
        if (argv[i][1] == '-') {
            if (string(argv[i] + 2) == "size") {
                float tmp;
                auto res = sscanf(argv[++i], "%f", &tmp);
                size = int(tmp);
                if (res != 1 || tmp < 0 || float(size) != tmp || size % 4 != 0) {
                    cout << "Huffman Zip: Invalid size number: \"" << argv[i] << '\"' << endl;
                    return 1;
                }
            }
            else if (string(argv[i] + 2) == "branch") {
                float tmp;
                auto res = sscanf(argv[++i], "%f", &tmp);
                size = int(branch);
                if (res != 1 || tmp < 0 || float(size) != tmp) {
                    cout << "Huffman Zip: Invalid size number: \"" << argv[i] << '\"' << endl;
                    return 1;
                }
            }
            else {
                cout << "Huffman Zip: Unrecognized setting: \"" << argv[i] << '\"' << endl;
                return 1;
            }
        }
        else {
            if (string(argv[i] + 1) == "f") {
                if (i == argc - 1) {
                    cout << "Huffman Zip: You must specify at least one input file after \"-f\"." << endl;
                    return 1;
                }
                while (argv[++i][0] != '-')
                    input_files.push_back(string(argv[i]));
                --i;
            }
            else if (string(argv[i] + 1) == "o") {
                if (i == argc - 1) {
                    cout << "Huffman Zip: You must specify a input_files after \"-o\"." << endl;
                    return 1;
                }
                if (!output_file.empty()) {
                    cout << "Huffman Zip: You can only specify the name of output file once." << endl;
                    return 1;
                }
                output_file = string(argv[++i]);
            }
            else if (string(argv[i] + 1) == "c") {
                if (opType != Op_Type::Unsure) {
                    cout << "Huffman Zip: You can only specify one mode (-c, -x or -h) at a time." << endl;
                    return 1;
                }
                opType = Op_Type::Zip;
            }
            else if (string(argv[i] + 1) == "x") {
                if (opType != Op_Type::Unsure) {
                    cout << "Huffman Zip: You can only specify one mode (-c, -x or -h) at a time." << endl;
                    return 1;
                }
                opType = Op_Type::Unzip;
            }
            else if (string(argv[i] + 1) == "h") {
                if (opType != Op_Type::Unsure) {
                    cout << "Huffman Zip: You can only specify one mode (-c, -x or -h) at a time." << endl;
                    return 1;
                }
                opType = Op_Type::Help;
            }
            else {
                cout << "Huffman Zip: Unrecognized option: \"" << argv[i] << '\"' << endl;
                return 1;
            }
        }
    }
    if (opType == Op_Type::Help) cout << get_help(string(argv[0]));
    else if (opType == Op_Type::Zip) {
        if (input_files.empty()) {
            cout << "Huffman Zip: No input files specified." << endl;
            return 1;
        }
        Vector<Vector<int>> input_data;
        for (const auto& i : input_files)
            input_data.push_back(prepare_for_zip(i, size));
        for (const auto& i : input_data[0]) {
            cout << i << ' ';
        }
        cout << endl;
    }
    else if (opType == Op_Type::Unzip) {
        if (input_files.empty()) {
            cout << "Huffman Zip: No input file specified." << endl;
            return 1;
        }
        if (input_files.size() != 1) {
            cout << "Huffman Zip: You can only unzip one file at a time." << endl;
            return 1;
        }
    }
    else {
        cout << "Huffman Zip: No operation specified." << endl;
        return 1;
    }
#else
    TestPriorityQueue();
#endif
    return 0;
}