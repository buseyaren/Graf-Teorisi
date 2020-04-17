#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<stdbool.h>
struct node
{
    int label;
    int weight;
    struct node* next;
};
typedef struct node Node;

struct graph
{
    int num_vertices;
    Node** adj_list;
};

typedef struct graph Graph;

Node* createNode(int v,int weight)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->label = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


Graph* CreateNullGraph(int vertices)
{

    Graph* G = malloc(sizeof(Graph));
    G->num_vertices = vertices;

    G->adj_list = malloc(vertices * sizeof(Node*));

    int i;
    for (i = 0; i < vertices; i++) {
        G->adj_list[i] = NULL;
    }
    return G;
}

void add_edge(Graph* G, int src, int dest,int directed, int weight)
{
    if(directed==0)
        weight=1;
    Node* newNode = createNode(dest,weight);
    newNode->next = G->adj_list[src];
    G->adj_list[src] = newNode;

    if(!directed)
    {
        Node* srcNode = createNode(src,weight);
        srcNode->next = G->adj_list[dest];
        G->adj_list[dest] = srcNode;
    }
}
void printGraph(Graph* G)
{
    int v;
    for (v = 0; v < G->num_vertices; v++)
    {
        Node* temp = G->adj_list[v];
        printf("%d = ", v);
        while (temp)
        {
            printf("%d -> ", temp->label);
            temp = temp->next;
        }
        printf("\n");
    }
}
void printDegrees(Graph* G)
{
    int v;
    for (v = 0; v < G->num_vertices; v++)
    {
        int d =0;
        Node* temp = G->adj_list[v];
        printf("degree of node %d = ", v);
        while (temp)
        {
            d++;
            temp = temp->next;
        }
        printf("%d\n",d);
    }
}
void DFS(Graph* G, int vertex, int visited[])
{
    if(visited[vertex] == 0)
    {
        //printf("%d -> ",vertex);
        visited[vertex] = 1;
        Node* tmp = G->adj_list[vertex];
        while(tmp != NULL)
        {
            DFS(G,tmp->label,visited);
            tmp = tmp->next;
        }
    }
}
int listedevarmi(Node* liste,int vertex )
{
    Node* tmp = liste;
    while(tmp != NULL)
    {
        if(tmp->label == vertex)
            return 1;
        tmp = tmp -> next;
    }
    return 0;
}

int ConnectedComponent(Graph* G)
{
    int visited[G->num_vertices];
    int i;
    int noc = 1;
    int visitCounter=0;
    for(i=0;i<G->num_vertices;i++)
        visited[i] = 0;
    DFS(G,0,visited);
    for(i=0;i<G->num_vertices;i++)
        if(visited[i] == 1)
            visitCounter++;
    while(visitCounter != G->num_vertices)
    {
        for(i=0;i<G->num_vertices;i++)
            if(visited[i] == 0)
            {
                DFS(G,i,visited);
                break;
            }


        visitCounter=0;
        for(i=0;i<G->num_vertices;i++)
        if(visited[i] == 1)
            visitCounter++;
        noc++;
    }
    printf("%d \n",noc);
    return noc;
}
int isNeighbor(Graph* G, int src, int dest)
{
    Node* tempList= G->adj_list[src];
    while(tempList != NULL)
    {
        if(tempList->label == dest)
            return tempList->weight;
        tempList=tempList->next;

    }
    return 0;
}
void AdjMatris(Graph* G)
{
    int i,j;
    FILE *fp = fopen("output.txt","w");
    for(i=0;i<G->num_vertices;i++)
    {
        for(j=0;j<G->num_vertices;j++)
        {
            fprintf(fp,"%d ",isNeighbor(G,i,j));
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
int FindMinNeigbor(Graph* G,int visited[],int *w)
{
    int i,minWeight=100000,minIndex;
    for(i=0;i<G->num_vertices;i++)
    {
        if(visited[i])
        {
            Node* tmp = G->adj_list[i];
            while(tmp)
            {
                if( !visited[tmp->label] && tmp->weight < minWeight)
                {
                    minWeight = tmp->weight;
                    minIndex=tmp->label;
                }
                tmp = tmp->next;
            }
        }
    }
    *w += minWeight;
    return minIndex;
}
int PrimsAlgorithm(Graph* G)
{
   int W = 0;
   int i=0;
   int vertNo = 0;
   int visited[G->num_vertices];
   for(i=0;i<G->num_vertices;i++)
        visited[i]=0;
   for(i=0;i<G->num_vertices-1;i++)
   {
       visited[vertNo] = 1;
       vertNo = FindMinNeigbor(G,visited,&W);
       printf("%d \n",W);
   }
   return W;
}
int findMinDistances(int distances[],int visited[],int m)
{
    int minimumDistance = INT_MAX, minIndis=-1;
    int i;
    for(i=0;i<m;i++)
    {
        if(visited[i] == 0 && distances[i] < minimumDistance)
        {
            minimumDistance = distances[i];
            minIndis = i;
        }
    }
    return minIndis;
}
void Dijkstra(Graph* G, int distances[], int parents[],int startV)
{
    int i,dugum = startV;
    int visited[G->num_vertices];
    for(i=0;i<G->num_vertices;i++)
    {
        distances[i]=INT_MAX; //INFINITY
        visited[i] = 0;
    }


    distances[dugum]=0;
    parents[dugum] = -1;
    visited[dugum] = 1;
    int numvisited=1;
    int cost = 0;
    while(numvisited<G->num_vertices)
    {
        Node* tmp = G->adj_list[dugum];
        while(tmp != NULL)
        {
            if (cost + tmp->weight < distances[tmp->label])
            {
                distances[tmp->label] = cost + tmp->weight;
                parents[tmp->label] = dugum;
            }
            tmp = tmp->next;
        }
        numvisited++;
        dugum = findMinDistances(distances,visited,G->num_vertices);
        cost = distances[dugum];
        visited[dugum] = 1;
    }

}


bool isSafe(int v, Graph* G, int path[], int pos)
{
    int i;
    if (!isNeighbor(G,path[pos - 1],v))
        return false;

    for ( i= 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}





bool HamiltonRec(Graph* G,int path[], int pos)
{
    //Tüm düðümler eklendiyse
    if (pos == G->num_vertices)
    {
        return true;
        if (isNeighbor(G,path[pos - 1],path[0]))
            return true;
        else
            return false;
    }
    int v;
    for ( v= 1; v < G->num_vertices; v++)
    {
        if (isSafe(v, G, path, pos))
        {
            path[pos] = v;
            if (HamiltonRec (G, path, pos + 1) == true)
                return true;
            path[pos] = -1;
        }
    }
    return false;
}
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}
bool HamiltonCycle(Graph* G)
{
    int i;
    int path[G->num_vertices];

    for (i= 0; i < G->num_vertices; i++)
        path[i] = -1;

    path[0] = 0;

    if (HamiltonRec(G, path, 1) == false )
    {
        printf("\nSolution does not exist");
        return false;
    }
    else
    {
        printSolution(path,G);
    }


    return true;
}

void BFS(Graph* G, int vertex, int visited[], int distance[])
{
    visited[vertex] = 1;
    Node* komsular=NULL;
    int sayac = 0;
    while(sayac <= G->num_vertices)
    {
        printf("v: %d \n",vertex);
        Node* tmp = G->adj_list[vertex];
        while(tmp != NULL)
        {
            //printf("eklenen: %d \n",tmp->label);
            if(visited[tmp->label]==0 && listedevarmi(komsular,tmp->label)==0)
            {
                //printf("eklenen: %d \n",tmp->label);
                Node* newNode = malloc(sizeof(Node));
                newNode->label = tmp->label;
                newNode->next = komsular;
                komsular =newNode;
                distance[tmp->label] = distance[vertex]+1;
            }
            tmp = tmp->next;
        }


        Node* k = komsular;
        while(k != NULL)
        {
            printf("%d -> ",k->label);
            k =k->next ;
        }
         printf("\n");


        if(komsular != NULL)
        {
            Node* temp = komsular;
            while(temp->next != NULL) temp = temp->next;
            visited[temp->label] = 1;
            vertex=temp->label;



            Node* son = komsular;
            while(son->next->label != temp->label)
                    son=son->next;
            son->next=NULL;

             if(komsular->label == temp->label)
                komsular=NULL;
        }
        sayac ++;
    }
}
int main()
{
    int noV=6;
    Graph* G=CreateNullGraph(noV);
    add_edge(G,0,1,0,0);
    add_edge(G,0,2,0,0);
    add_edge(G,1,2,0,0);
    add_edge(G,2,3,0,0);
    add_edge(G,3,4,0,0);
    add_edge(G,3,5,0,0);
    add_edge(G,4,5,0,0);

    int i;

    int visited[G->num_vertices];
    int distance[G->num_vertices];
    for(i=0;i<G->num_vertices;i++)
    {
        visited[i]=0;
        distance[i]=0;
    }
  	BFS(G,0,visited,distance);
    for(i=0;i<G->num_vertices;i++)
    {
        //printf("%d -> %d  \n",0,i);
    }
    AdjMatris(G);
    //HamiltonCycle(G);
    //printf("W(H) = %d",PrimsAlgorithm(G));

    return 0;
}
