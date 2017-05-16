//
//  main.cpp
//  divide and conquer
//
//  Created by MaTianyi on 4/17/17.
//  Copyright (c) 2017 MaTianyi. All rights reserved.
//

#include <iostream>
#include <cmath>

class point {
public:
    double x;
    double y;
    //point(){x=0; y=0;};
};
class pair{
public:
    pair(point a, point b, double m): p1(a), p2(b), min(m){}
    pair(){};
    point p1;
    point p2;
    double min;
    void operator = (const pair &other)
    {
        p1=other.p1;
        p2=other.p2;
        min=other.min;
    }
    
};
void merge_by_x(point p[], int s,int e){
    if (s>=e) return;
    else {
        merge_by_x(p, s, (e+s)/2);
        merge_by_x(p, (e+s)/2+1,e);
    }
    int i=s;
    int j=(e+s)/2+1;
    point* temp=new point[e-s+1];
    int size=0;
    while (size<e-s+1)
    {
        if (p[j].x<p[i].x){
            temp[size].x=p[j].x;
            temp[size].y=p[j].y;
            j++;
        }
        else {
            temp[size].x=p[i].x;
            temp[size].y=p[i].y;
            i++;
        }
        if (i>(e+s)/2)
        {
            for (int k=j; k<=e; k++) { size++; temp[size].x=p[k].x; temp[size].y=p[k].y;}
            
        }
        else if (j>e)
        {
            for (int k=i; k<=(e+s)/2; k++) { size++; temp[size].x=p[k].x; temp[size].y=p[k].y;}
            
        }
        size++;
    }
    for (int k=s; k<=e; k++)
    {
        p[k].x=temp[k-s].x;
        p[k].y=temp[k-s].y;
    }
}
void brutal_force(point* p,int n)
{
    if (n<2) {std::cout<<"No Possible Closest Pair"; return;}
    double x1=p[0].x,x2=p[1].x,y1=p[0].y,y2=p[1].y;
    int c=0;
    double min=sqrt(pow(p[0].x-p[1].x,2)+pow(p[0].y-p[1].y,2));
    for (int i=0; i<n; i++)
        for (int j=i+1; j<n; j++)
        {
            c++;
            if (sqrt(pow(p[i].x-p[j].x,2)+pow(p[i].y-p[j].y,2))<min)
            {
                min=sqrt(pow(p[i].x-p[j].x,2)+pow(p[i].y-p[j].y,2));
                x1=p[i].x;
                x2=p[j].x;
                y1=p[i].y;
                y2=p[j].y;
                
            }
        }
    std::cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<std::endl;
    std::cout<<c<<std::endl;
}

pair divide_and_conquer(point* px, point*py, int s, int e,int& c){
    pair d;
    point a,b;
    if (e<=s) return pair(a,b,100000);
    if (e-s+1==2)
    {
        d.min=sqrt(pow(py[s].x-py[e].x,2)+pow(py[s].y-py[e].y,2));
        d.p1.x=py[s].x;
        d.p1.y=py[s].y;
        d.p2.x=py[e].x;
        d.p2.y=py[e].y;
        return d;
    }
    pair d1=divide_and_conquer(px,py,s,(e+s)/2,c);
    pair d2=divide_and_conquer(px,py,(e+s)/2+1,e,c);
    if (d1.min<d2.min) d=d1; else d=d2;
    c++;
    int i=s;
    int j=(e+s)/2+1;
    point* temp=new point[e-s+1];
    int size=0;
    while (size<e-s+1)
    {
        if (py[j].y<py[i].y){
            temp[size].x=py[j].x;
            temp[size].y=py[j].y;
            j++;
        }
        else {
            temp[size].x=py[i].x;
            temp[size].y=py[i].y;
            i++;
        }
        if (i>(e+s)/2)
        {
            for (int k=j; k<=e; k++) { size++; temp[size].x=py[k].x; temp[size].y=py[k].y;}
            
        }
        else if (j>e)
        {
            for (int k=i; k<=(e+s)/2; k++) { size++; temp[size].x=py[k].x; temp[size].y=py[k].y;}
            
        }
        size++;
    }
    for (int k=s; k<=e; k++)
    {
        py[k].x=temp[k-s].x;
        py[k].y=temp[k-s].y;
    }
    point cand[e-s+1];
    int c_size=0;
    for (int i=s; i<=e; i++)
        if (py[i].x>=(px[(e+s)/2].x-d.min) && py[i].x<=(px[(e+s)/2].x+d.min))
        {
            cand[c_size].x=py[i].x;
            cand[c_size].y=py[i].y;
            c_size++;
        }
    //std::cout<<c_size<<std::endl;
    for (int i=0; i<c_size; i++)
    {
        for (int j=i-6; j<=i+6; j++)
            {
                if (j>=0 && j<c_size && j!=i && cand[i].x<=px[(e+s)/2].x && cand[i].x<=cand[j].x)
                {
                    c++;
                    if (sqrt(pow(cand[i].x-cand[j].x,2)+pow(cand[i].y-cand[j].y,2))<d.min)
                    {
                        d.min=sqrt(pow(cand[i].x-cand[j].x,2)+pow(cand[i].y-cand[j].y,2));
                        d.p1.x=cand[i].x;
                        d.p1.y=cand[i].y;
                        d.p2.x=cand[j].x;
                        d.p2.y=cand[j].y;
                    }
                }
            }
    }
    
    return d;
}
int main(int argc, const char * argv[]) {
    int n=0;
    std::cin>>n;
    int c=0;
    point* px=new point[n];
    point* py=new point[n];
    pair d;
    /*p.min=0;
    p.p1.x=1;
    p.p2.x=1;
    p.p1.y=0;
    p.p2.y=0;
    t=p;
    std::cout<<t.min<<t.p1.x<<t.p2.y;*/
    for (int i=0; i<n; i++){
        std::cin>>px[i].x>>px[i].y;
    }
    
    merge_by_x(px, 0, n-1);
    for (int i=0; i<n; i++)
    {
        py[i].x=px[i].x;
        py[i].y=px[i].y;
    }
    brutal_force(px,n);
    d=divide_and_conquer(px, py, 0, n-1,c);
    std::cout<<d.p1.x<<" "<<d.p1.y<<" "<<d.p2.x<<" "<<d.p2.y<<std::endl<<c<<std::endl;
    return 0;
}
