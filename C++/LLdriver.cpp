/************************
 *    LL Driver File    *
 * Author: Ben Capeloto *
 *      4/26/2020       *
 ************************/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include "BST.hpp"
#include "LinkedList.hpp"
 
using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    ifstream dataFile;
    string data; 
    int hashSize = 40000;
    float LLinsert[400];
    float LLsearch[400];


    LinkedList list; //declared list


    if (argc != 2)//check if the right number of arguments have been passed through command line
	{
		cerr << "Not enough arguments!" << endl;
		return 1;
	}
    dataFile.open(argv[1]);//open the data set based on command line argument
    ofstream outInsertA ("LLinsertB.txt");
    ofstream outSearchA ("LLsearchB.txt");
    if (!dataFile.is_open())//check if it opened correctly
	{
		cerr << "Could not open " << argv[1] << " for reading!" << endl;
		return 2;
	}
    int testData[40000];
    for(int i = 0; i<40000;i++){
        getline(dataFile,data,',');
        int key;
        key = stoi(data);
        testData[i]=key;
    }


    /******************LL INSERT TEST***************/
    for(int i=0; i<400; i++){
        int sampleSize = 100;//initialize sample size
        int level = i*100;
        int duration[100];
        for(int j =0;j<sampleSize;j++){ //while data is being pulled from data set
            auto startInsert = high_resolution_clock::now();//start the clock
            list.LLinsert(testData[(i)+level]); 
            auto stopInsert = high_resolution_clock::now();//stop the clock
            auto durationInsert = duration_cast<microseconds>(stopInsert - startInsert);//record the duration
            duration[j]=durationInsert.count();
        }
        int sum;
        for(int k=0;k<99;k++) sum = sum+duration[k];
        LLinsert[i] = sum/100;
        //cout << "Average insert time taken by the "<<i<<"th"<< " Data set was " << LLinsert[i]<< " Nanoseconds." <<endl;
        outInsertA<<LLinsert[i]<<endl;
    }
    /**************END LL Insert Test****************/


    /***************LL Search Test***************/
    for(int i=0; i<400; i++){
        int sampleSize = 100;//initialize sample size
        int searchVar = 100;
        int n = rand()%searchVar*i+1;
        int durationS[100];
        for(int j = 0; j<sampleSize; j++){ //while data is being pulled from data set
            auto startSearch = high_resolution_clock::now();//start the clock
            //LL Search
            list.LLsearch(testData[n]);
            auto stopSearch = high_resolution_clock::now();//stop the clock
            auto durationSearch = duration_cast<microseconds>(stopSearch - startSearch);//record the duration
            durationS[j]=durationSearch.count();
        }
        int sumS;
        for(int k=0;k<99;k++) sumS=sumS+durationS[k];
        LLsearch[i] = sumS/100;
        //cout << "Average search time taken by the "<<i<<"th"<< " Data set was " << LLsearch[i]<< " Nanoseconds." <<endl;
        outSearchA<<LLsearch[i]<<endl;
    }
    /************End LL Search Test*******************/

    outInsertA.close();
    outSearchA.close();
    dataFile.close();
    return 0;

    
}