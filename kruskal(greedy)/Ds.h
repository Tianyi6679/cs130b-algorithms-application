//
//  Ds.h
//  130b_PA2
//
//  Created by MaTianyi on 5/3/17.
//  Copyright (c) 2017 MaTianyi. All rights reserved.
//

#ifndef _30b_PA2_Ds_h
#define _30b_PA2_Ds_h
#include <vector>
#include <algorithm>
#include <vector>
class DisjSets
{
public:
    DisjSets(int numElements)
    {
        for (int i=0; i<numElements; ++i)
            s.push_back(-1);
    }
    int find(int x);
    void unionSets(int root1, int root2);
    int numSets();
private:
    std::vector<int> s;
};

void DisjSets::unionSets(int root1, int root2)
{
    if (s[root2]<s[root1])
        s[root1]=root2;
    else
    {
        if(s[root1]==s[root2])
            --s[root1];
        s[root2]=root1;
    }
}

int DisjSets::numSets()
{
    int count=0;
    for (int i=0; i<s.size(); i++)
        if (s[i]<0) count++;
    return count;
}
int DisjSets::find(int x)
{
    if (s[x]<0)
        return x;
    else
        return s[x]=find(s[x]);
}


#endif
