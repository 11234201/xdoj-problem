// main.cpp文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <sstream>

using namespace std;


int main()
{
    double q1,q2,q3,q4;
    string line;
    scanf("%lf,%lf,%lf,%lf",&q1,&q2,&q3,&q4);
//    getline(cin,line,',');
//    stringstream ss1(line);
//    ss1>>q1;
//    getline(cin,line,',');
//    stringstream ss2(line);
//    ss2>>q2;
//    getline(cin,line,',');
//    stringstream ss3(line);
//    ss3>>q3;
//    getline(cin,line,'\n');
//    stringstream ss4(line);
//    ss4>>q3;
    double R[3][3]={0};
    R[0][0]=pow(q1,2)+ pow(q2,2)- pow(q3,2)- pow(q4,2);
    R[0][1]=2*(q2*q3-q1*q4);
    R[0][2]=2*(q2*q4+q1*q3);
    R[1][0]=2*(q2*q3+q1*q4);
    R[1][1]=pow(q1,2)- pow(q2,2)+ pow(q3,2)- pow(q4,2);
    R[1][2]=2*(q2*q4-q1*q2);
    R[2][0]=2*(q2*q4-q1*q3);
    R[2][1]=2*(q3*q4+q1*q2);
    R[2][2]=pow(q1,2)- pow(q2,2)- pow(q3,2)+ pow(q4,2);

    for(auto &Ri:R){
        printf("%0.6lf %0.6lf %0.6lf\n",Ri[0],Ri[1],Ri[2]);
    }
    return 0;
}