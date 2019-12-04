#include <sys/types.h>
#include "plagiarismCatcher.h"
#include <dirent.h>
using namespace std;

const int tableSize = 10000;
hashNode* hashTable[tableSize];


int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL) {
	cout << "Error(" << errno << ") opening " << dir << endl;
    }
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main()
{
    for (int i=0;i<tableSize;i++){
        hashTable[i]=NULL;
    }


    string dir = string("C:\\Users\\guich\\Documents\\2019 Fall\\EE312 - Software Design & Implementation I\\cheaters\\sm_doc_set");
    vector<string> files = vector<string>();
	
    getdir(dir,files);
    files.erase (files.begin());
    files.erase (files.begin());

    for (unsigned int i = 0;i<files.size();i++) {
        cout << i << files[i] << endl;
    }



	////////////////////////////////////////////
	//now directory of file names is loaded into the vector "files[]"///////

	//////////////////////////////////////////////

//    vector <vector <string> > allChunks;
 //   vector <vector *> allChunks;
    for (int i=0;i<files.size();i++) {

        string filename = "./sm_doc_set/";        //this will have to be changed to (prob.) argv 1
        filename.append(files[i]);                //don't neglect considering "./" possible append
        char *nameArray = new char[filename.length() +1];//also index must move from 0 -> max files. b/c is vector, cool
        strcpy(nameArray, filename.c_str());        //nameArray = c type char array
        vector<string> words;
        ifstream inFile;
        inFile.open(nameArray);

        string s;                        //
        inFile >> s;                    //read first word from file into string s
        while (inFile) {                    //then load them all into a vector "words"
            words.push_back(s);
            inFile >> s;
        }

        for (int i = 0; i < words.size(); i++) {            //////confirm initial vector of individual words
            cout << words[i] << endl;
        }



/*
    vector <string> words;
    ifstream inFile;
    inFile.open("abf0704.txt");

    string s;						//
    inFile >> s;					//read first word from file into string s
    while (inFile) {                    //then load them all into a vector "words"
        words.push_back(s);
        inFile >> s;

        for (int i = 0; i < words.size(); i++) {            //////confirm initial vector of individual words
            cout << words[i] << endl;
        }
    }
*/

        vector<string> wordChunks;
        int vecSize = words.size() - 5;
        for (int i = 0; i < vecSize; i++) {
            wordChunks.push_back(words[0]);
            words.erase(words.begin());

            for (int j = 0; j < 5; j++) {
                wordChunks[i].append(words[j]);
            }
//            cout << wordChunks[i] << endl;     		 //////confirm n-word chunks
        }
//        cout << endl << endl;

        for (int i = 0; i < wordChunks.size(); i++) {
            for (int j = 0; j < wordChunks.at(i).size(); j++) {
                if ((wordChunks.at(i).at(j) >= 'A') && (wordChunks.at(i).at(j) <= 'Z')) {
                    (wordChunks.at(i).at(j)) += 0x20;
                } else if ((wordChunks.at(i).at(j) > 'z') || (wordChunks.at(i).at(j) < 'a')) {
                    wordChunks.at(i).erase(wordChunks.at(i).begin() + j);
                    j--;
                }
            }

//            cout << wordChunks[i] << endl;
            Hash(wordChunks.at(i), i);
        }


        return 0;
    }
}

int Hash(const string & key,int idx){
    int keyNum = 0;
    for (int i=0;i<key.size();i++) {
        unsigned long power = (unsigned long) key[i] * pow(7, i);
        keyNum = (keyNum + power) % tableSize;
    }
	hashNode* temp;
    temp->idx = idx;
	temp->next = hashTable[keyNum];
	hashTable[keyNum]= temp;

    return 1;		
}
/*
for (int i=0;i<allChunks.size();i++){
    cout << allChunks[i] << endl;
}

    vector<char*> chunkArray;
    for (int i=0;i<wordChunks.size();i++){
        char* temp = new char [wordChunks[i].length()+1];
       	strcpy(temp, wordChunks[i].c_str());
        chunkArray.push_back(temp);
	cout << chunkArray[i] << endl;
*/
    
	

      
 	 
   
