
#include <queue>
#include <errno.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cmath>

using namespace std;


struct hashNode
{
    int idx;
    hashNode *next;
};

int Hash(const string &key, int i);
