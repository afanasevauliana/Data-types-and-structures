#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include <cmath>
#include <limits>
using namespace std;
#pragma region функции-заглушки

void DFS(int st)
{
    int r;
    cout<<st+1<<" ";
    visited[st]=true;
    for (r=0; r<=n; r++)
    if ((graph[st][r]!=0) && (!visited[r]))
    DFS(r);
}

void BFS(bool *visited, int unit)
{
    int *queue=new int[n];
    int count, head;
    for (i=0; i<n; i++)
    queue[i]=0;
    count=0; head=0;
    queue[count++]=unit;
    visited[unit]=true;
    while (head<count)
    {
        unit=queue[head++];
        cout<<unit+1<<" ";
        for (i=0; i<n; i++)
        if (GM[unit][i] && !visited[i])
        {
            queue[count++]=i;
            visited[i]=true;
        }
    }
    delete []queue;
}


void Dijkstra(int GR[V][V], int st)
{
    int distance[V], count, index, i, u, m=st+1;
    bool visited[V];
    for (i=0; i<V; i++)
    {
        distance[i]=INT_MAX; visited[i]=false;
    }
    distance[st]=0;
    for (count=0; count<V-1; count++)
    {
        int min=INT_MAX;
        for (i=0; i<V; i++)
        if (!visited[i] && distance[i]<=min)
        {
            min=distance[i]; index=i;
        }
        u=index;
        visited[u]=true;
        for (i=0; i<V; i++)
            if (!visited[i] && GR[u][i] &&
            distance[u]!=INT_MAX &&
            distance[u]+GR[u][i]<distance[i])
            distance[i]=distance[u]+GR[u][i];
        }
        cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
        for (i=0; i<V; i++)
            if (distance[i]!=INT_MAX)
                cout<<m<<" > "<<i+1<<" = "<<distance[i]<<endl;
            else cout<<m<<" > "<<i+1<<" = "<< "маршрут недоступен"<<endl;
}



#pragma endregion

const int ITEMS_NUMBER = 3;


int main() {
    CMenuItem items[ITEMS_NUMBER] {
        CMenuItem{"Root of 25", DFS}, 
        CMenuItem{"Print house", BFS}, 
        CMenuItem{"getEmployee", Dijkstra}};
    CMenu menu("My console menu", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};

    return 0;
}