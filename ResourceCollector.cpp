#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//Define a structure for representing coordinates
struct Coordinate{
    int x,y;
    Coordinate(int _x,int _y):x(_x),y(_y){}
};

// Function to check if a coordinate is valid on the grid
bool isValid(int x,int y,int n,int m) {
    return x>=0 && y>=0 && x<n && y<m;
}

int resourcesCollected=0;

// Function to perform BFS to find the shortest path to a resource
int bfs(vector<vector<int>>& grid,Coordinate start,Coordinate dest,int n,int m){
    vector<vector<bool>> visited(n,vector<bool>(m,false));
    queue<pair<Coordinate,int>> q; //Pair:{start coordinate,distance}
    q.push({start,0}); //Start node and its distance
    visited[start.x][start.y]=true;

//Define possible moves (up,down,left,right)
    int dx[]={0,0,-1,1}; //(Up,Down)
    int dy[]={-1,1,0,0}; //(Left,Right)

    while(!q.empty()){
        Coordinate curr=q.front().first;
        int dist=q.front().second;
        q.pop();

    //Check if destination is reached
        if(curr.x==dest.x && curr.y==dest.y)
            return dist;
    
    // Check if the current cell contains a resource
        if (grid[curr.x][curr.y] == 1)
            resourcesCollected++;

    //Explore neighboring cells
        for(int i=0;i<4;i++){
            int newX=curr.x+dx[i];
            int newY=curr.y+dy[i];
            if (isValid(newX,newY,n,m) && grid[newX][newY]==0 && !visited[newX][newY]) {
                q.push({Coordinate(newX,newY),dist+1});
                visited[newX][newY]=true;
            }
        }
    }
    //If destination is unreachable
    return -1;
}

// Main function
int main(){
    int n=5; // Grid size (n x n)
    int m=5;
    vector<vector<int>>grid(n,vector<int>(m,0)); //Initialize grid with zeros

    //Set resources on the grid (1 indicates available resource)
    grid[1][1]=1;
    grid[3][3]=1;

    //Define start and destination coordinates
    Coordinate start(0, 0);
    Coordinate dest(4, 4);

    //Call BFS to find shortest path from start to destination
    int shortestPath=bfs(grid,start,dest,n,m);
    if (shortestPath!=-1)
        cout<<"Shortest path to the resource is:"<<" "<<shortestPath<<" "<<"units"<<"\n";
    else
        cout<<"Resource is not reachable"<<"\n";

    return 0;
}