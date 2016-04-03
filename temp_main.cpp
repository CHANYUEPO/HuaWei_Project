#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stack>
#include <stdio.h>
#include "MyStack.h"
#include <QTime>
#include <qdebug.h>
#include <set>
#define N 4
MyStack v_set;
std::set<int> nodeset;
int set_N;
int Matrix[N][N]={0};
int Dijkstra_Matrix[N][N]={0};
int TempMatrix[N][N]={0};
int start,end;
int first_num=-1;
int node_array[N]={-1};
int total_value=10000000;
int vset_node[N]={-1};
int EdgeMatrix[N][N]={-1};
int start_num;
int end_num;
bool inSet(int x)
{
    std::set<int>::iterator it=nodeset.find(x);
    if(it!=nodeset.end())
         return true;
    return false;
}

int string2int(std::string str)
{
    return atoi(str.c_str());
}

MyStack getPath(int *path,int v,int v0)
{
    MyStack s;
    while(v!=v0)
    {
        s.push(v);
        v=path[v];
    }
    s.push(v);
    return s;
}
void getNodes(MyStack stack1,MyStack stack2)
{
    int index=0;
    start_num=stack1.size();
    end_num=stack2.size();
    while(!stack1.empty())
    {
        vset_node[index++]=stack1.pop();
    }
    for(int i=1;i<set_N-1;i++)
    {
        vset_node[index++]=v_set.indexof(i);
    }
    while(!stack2.empty())
    {
        vset_node[index++]=stack2.pop();
    }
}
//void caculatePath()
//{
//    int size=set_N;
//    int sum=0;
//    int dist_array_1[600]={-1};
//    int path_array_1[600]={-1};
//    dijkstraPath(dist_array_1,path_array_1,start);

////    if(Matrix[v_set.indexof(size-1)][end]!=0 && Matrix[start][v_set.indexof(0)]!=0)
////    {

////        sum+=Matrix[v_set.indexof(size-1)][end];
////        sum+=Matrix[start][v_set.indexof(0)];

//        int dist1=dist_array_1[v_set.indexof(0)];


//        int dist_array_2[600]={-1};
//        int path_array_2[600]={-1};
//        dijkstraPath(dist_array_2,path_array_2,v_set.indexof(size-1));
//        int dist2=dist_array_2[end];

//        for(int i=0;i<size-1;i++)
//        {
//            sum+=Matrix[v_set.indexof(i)][v_set.indexof(i+1)];
//        }
//        sum+=dist1;
//        sum+=dist2;
//        if(total_value>sum)
//        {
//            total_value=sum;
//            MyStack stack1=getPath(path_array_1,v_set.indexof(0),start);
//            MyStack stack2=getPath(path_array_2,end,v_set.indexof(size-1));

//            getNodes(stack1,stack2);

////            end_edge=EdgeMatrix[v_set.indexof(size-1)][end];
////            start_edge=EdgeMatrix[start][v_set.indexof(0)];

////            for(int j=0;j<size;j++)
////            {
////                vset_node[j]=v_set.indexof(j);
////            }
//        }


//}
//void initDijkstraMatrix()
//{
//    for(int i=0;i<N;i++)
//    {
//        for(int j=0;j<N;j++)
//        {
//            if(inSet(i)&&inSet(j))
//            {
//                Dijkstra_Matrix[i][j]=0;
//                continue;
//            }
//            Dijkstra_Matrix[i][j]=Matrix[i][j];
//        }
//    }
//}
void init_setMatrix()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(inSet(j))
                TempMatrix[i][j]=0;
            else
            {
                TempMatrix[i][j]=Matrix[i][j];
            }
        }
    }
}
void dijkstraPath(int dist[],int path[],int v0)
{
    std::cerr<<"int payh"<<std::endl;
    int i,j,k;
    bool visited[N]={false};
    for(i=0;i<N;i++)
    {
       if(TempMatrix[v0][i]>0&&i!=v0)
        {
            dist[i]=TempMatrix[v0][i];
            path[i]=v0;
        }
        else
        {
            dist[i]=INT_MAX;
            path[i]=-1;
        }
        visited[i]=false;
        path[v0]=v0;
        dist[v0]=0;
    }
    visited[v0]=true;
    for(i=0;i<N;i++)
    {
        int min=INT_MAX;
        int u;
        for(j=0;j<N;j++)
        {
            if(visited[j]==false&&dist[j]<min)
            {
                min=dist[j];
                u=j;
            }
        }
        visited[u]=true;
        for(k=0;k<N;k++)
        {
            if(visited[k]==false&&TempMatrix[u][k]>0&&min+TempMatrix[u][k]<dist[k])
            {
               dist[k]=min+TempMatrix[u][k];
               path[k]=u;
            }
        }
    }
}
void init_Matrix(const char* demand_file_name,const char * topo_file_name)
{
    set_N=0;
    std::ifstream demand_file(demand_file_name);
    if(!demand_file.is_open())
    {
        std::cerr<<"cannot open file!"<<std::endl;
    }
    std::string start_value,end_value;
    std::getline(demand_file,start_value,',');
    std::getline(demand_file,end_value,',');
    start=string2int(start_value);
    end=string2int(end_value);
    int pre;
    std::string value;
    while (std::getline(demand_file,value,'|'))
    {
        int data=string2int(value);
        nodeset.insert(data);
        if(first_num==-1)
        {
            pre=data;
            first_num=pre;
        }
        else
        {
            node_array[pre]=data;
            pre=node_array[pre];
        }
        set_N++;
    }

    std::ifstream topo_stream(topo_file_name);
    if(!topo_stream.is_open())
    {
        std::cerr<<"cannot open file!"<<std::endl;
    }
    while(!topo_stream.eof())
    {
        std::getline(topo_stream,value,',');
        int edge_index=string2int(value);

        std::getline(topo_stream,value,',');
        int start_node=string2int(value);

        std::getline(topo_stream,value,',');
        int end_node=string2int(value);

        std::getline(topo_stream,value,'\n');
        int edge_value=string2int(value);

        if(start_node==end_node)
        {
            std::cerr<<"there is wrong in the topo file";
            exit(0);
        }
        if(Matrix[start_node][end_node]!=0 && Matrix[start_node][end_node]<edge_value)
            continue;
        Matrix[start_node][end_node]=edge_value;
        EdgeMatrix[start_node][end_node]=edge_index;

    }
    //initDijkstraMatrix();
    //init_setMatrix();
}
int next_node(int current_node)
{
    return node_array[current_node];
}

bool is_legal(int row,int col)
{
     if(Matrix[row][col]==0)
        return false;
     if(v_set.contains(col))
        return false;
     return true;
}

//void try_next(int n)
//{
//    if(v_set.size()==set_N)
//    {
//        caculatePath();
//    }
//    else
//    {
        
        
        
//        for (int i=0,j=first_num;i<set_N;j=node_array[j],i++)
//        {

//            if(is_legal(n,j))
//            {
//                v_set.push(j);

//                try_next(j);

//                v_set.pop();
//            }

//        }
//    }
//}
void try_next(NodeSet set)
{
    if(route.failed())
    {
        return;
    }
    if(route.ended())
    {
        if(route.pathvalue<CurrentMin_Path)
        {
         /**update current minPath
                    **/
        }
        return;
    }
    for(int i=0;i<set.size();i++)
    {
        int node_index=set.at(i);
        route.add(node_index);
        try_next(set-node_index);
        route.pop();
    }
    
}
void generateResult(const char* result_file)
{
    std::ofstream out_stream(result_file);
    if(!out_stream.is_open())
    {
        std::cerr<<"cannot open the out file";
        return;
    }
    if(vset_node[0]!=-1)
    {
        //out_stream<<start_edge<<"|";

        for (int i=0;i<set_N+start_num+end_num;i++)
        {
            out_stream<<EdgeMatrix[vset_node[i]][vset_node[i+1]]<<"|";
        }


        //out_stream<<end_edge<<"\n";
    }
    else
    {
        out_stream<<"NA\n";
    }

    out_stream.close();


}

void addNodeToTopo(int num)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(j==num)
                TempMatrix[i][j]=Matrix[i][j];
        }
    }
}
void try_oneNode()
{

    int dist_array[N]={-1};
    int path_array[N]={-1};
    dijkstraPath(dist_array,path_array,start_num);
    int d=first_num;
    addNodeToTopo(d);
    dijkstraPath(dist_array,path_array,start_num);
    d=node_array[d];
    addNodeToTopo(d);
    dijkstraPath(dist_array,path_array,start_num);
}

int main(int argc, char *argv[])
{
//    if(argc<3)
//    {
//        std::cerr<<"lack of arguments"<<std::endl;
//        return 0;
//    }
    QTime time;
    time.start();
    init_Matrix("./demand.csv","./topo.csv");
    try_next(start);

    
//    generateResult("./out.csv");
//    generateResult(argv[3]);
    qDebug()<<time.elapsed()/1000.0<<"s";
    return 0;
}
