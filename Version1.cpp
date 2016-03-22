#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include "MyStack.h"
#include <QTime>
#include <QDebug>
#define N 600
MyStack v_set;
int set_N;
int Matrix[N][N]={0};
int start,end;
int first_num=-1;
int node_array[60]={-1};
int total_value=10000000;
int vset_node[60]={-1};
int EdgeMatrix[N][N]={-1};
int start_edge;
int end_edge;
bool contains(MyStack stack_set,int num)
{
    for(int i=0;i<stack_set.size();i++)
    {
        if(stack_set.top()==num)
            return true;
        stack_set.pop();
    }
    return false;
}
int string2int(std::string str)
{
    return atoi(str.c_str());
}
void  caculatePath()
{
    int size=set_N;
    int sum=0;
    if(Matrix[v_set.indexof(size-1)][end]!=0 && Matrix[start][v_set.indexof(0)]!=0)
    {

        sum+=Matrix[v_set.indexof(size-1)][end];
        sum+=Matrix[start][v_set.indexof(0)];
        for(int i=0;i<size-1;i++)
        {
            sum+=Matrix[v_set.indexof(i)][v_set.indexof(i+1)];
        }
        if(total_value>sum)
        {
            end_edge=EdgeMatrix[v_set.indexof(size-1)][end];
            start_edge=EdgeMatrix[start][v_set.indexof(0)];
            total_value=sum;
            for(int j=0;j<size;j++)
            {
                vset_node[j]=v_set.indexof(j);
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

}
int next_node(int current_node)
{
    return node_array[current_node];
}
bool is_legal(int row,int col)
{
     if(Matrix[row][col]==0)
        return false;
     if(contains(v_set,col))
        return false;
     return true;
}

void try_next(int n)
{
    if(v_set.size()==set_N)
    {
        caculatePath();
    }
    else
    {
        for (int i=0,j=first_num;i<set_N;j=node_array[j],i++)
        {

            if(is_legal(n,j))
            {
                v_set.push(j);

                try_next(j);

                v_set.pop();
            }

        }
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
        out_stream<<start_edge<<"|";
        for(int i=0;i<set_N-1;i++)
        {
            out_stream<<EdgeMatrix[vset_node[i]][vset_node[i+1]]<<"|";
        }
        out_stream<<end_edge<<"\n";
    }
    else
    {
        out_stream<<"NA\n";
    }

    out_stream.close();


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
    for(int i=0,j=first_num;i<set_N;j=node_array[j],i++)
    {
        v_set.push(j);
        try_next(j);
        v_set.pop();
    }
    generateResult("./out.csv");
    qDebug()<<time.elapsed()/1000.0<<"s";
    return 0;
}
