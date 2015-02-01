/*
 * compare_files.cpp
 *
 *  Created on: 01.02.2015
 *      Author: michael
 */

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ios;
using std::ifstream;

#include <exception>
using std::exception;

#include <cstring>
#include <cstdlib>
using std::memcmp;

// TODO: wrap this function in a class or ASSERT for cxxtest

bool equalFiles(const char *filename1, const char * filename2)
{

	ifstream in1(filename1, ios::binary);
	ifstream in2(filename2, ios::binary);

    ifstream::pos_type size1, size2;

    size1 = in1.seekg(0, ifstream::end).tellg();
    in1.seekg(0, ifstream::beg);

    size2 = in2.seekg(0, ifstream::end).tellg();
    in2.seekg(0, ifstream::beg);

    if(size1 != size2)
        return false;

    static const size_t BLOCKSIZE = 4096;
    size_t remaining = size1;

    while(remaining)
    {
        char buffer1[BLOCKSIZE], buffer2[BLOCKSIZE];
        size_t size = std::min(BLOCKSIZE, remaining);

        in1.read(buffer1, size);
        in2.read(buffer2, size);

        if(0 != memcmp(buffer1, buffer2, size))
            return false;

        remaining -= size;
    }

    return true;
}



