#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector < vector<int> > height;
vector < vector<bool> > valid;
vector < vector<bool> > lowPoints;

int n,m;

void part1(){
    int ans=0;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            bool flag=true;
            if(j!=0 && height[i][j]>=height[i][j-1]){
                flag=false;
            }
            if(j!=n-1 && height[i][j]>=height[i][j+1]){
                flag=false;
            }
            if(i!=0 && height[i][j]>=height[i-1][j]){
                flag=false;
            }
            if(i!=m-1 && height[i][j]>=height[i+1][j]){
                flag=false;
            }
            
            if(flag==true){
                // cout<<height[i][j]+1<<" ";
                ans+=(height[i][j]+1);
                lowPoints[i][j]=true;
            }

        }   
    }

    // cout<<"\npart1: "<<ans<<endl;
}

int isBasins(int i,int j){
    int ans=0;
    if(height[i][j]==9){ 
        return ans;
    }
    if(i!=0 && height[i][j]<height[i-1][j] && valid[i-1][j]){
        valid[i-1][j]=false;
        ans+=isBasins(i-1,j);
    }
    if(i!=m-1 && height[i][j]<height[i+1][j] && valid[i+1][j]){
        valid[i+1][j]=false;
        ans+=isBasins(i+1,j);
    }
    if(j!=0 && height[i][j]<height[i][j-1] && valid[i][j-1]){
        valid[i][j-1]=false;
        ans+=isBasins(i,j-1);
    }
    if(j!=n-1 && height[i][j]<height[i][j+1] && valid[i][j+1]){
        valid[i][j+1]=false;
        ans+=isBasins(i,j+1);
    }

    return ++ans;
}

void part2(){
    part1();
    vector <int> Basin;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(lowPoints[i][j]){
                Basin.push_back(isBasins(i,j));
            }
        }

    }
    sort(Basin.begin(),Basin.end(),greater<int>());

    cout<<"Part2: "<<Basin[0]*Basin[1]*Basin[2]<<endl;

}

int main(){
    fstream newfile;
    newfile.open("input.txt");
    string tp;
    
    
    while(getline(newfile, tp)){
        vector <int> v;
        vector <bool> v2;
        vector <bool> v3;
        for(int i=0;i<tp.length();i++){
            v.push_back(tp[i]-'0');
            v2.push_back(false);
            v3.push_back(true);
        }
        n=v.size();
        height.push_back(v);
        valid.push_back(v3);
        lowPoints.push_back(v2);
    }
    m=height.size();

    // for(int i=0;i<height.size();i++){
    //     for(int j=0;j<n;j++){
    //         cout<<height[i][j]<<" ";

    //     }   
    //     cout<<endl;
    // }
    // cout<<"\nPart1......\n\n";
    part2();
    return 0;
}