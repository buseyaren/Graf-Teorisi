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
    if(visited[vertex] == 0) //tepe ziyaret edilmediyse
    {
        printf("Tepe : %d-> \n",vertex); //tepeyi yazdýr.
        visited[vertex] = 1; //ziyaret edilen tepeyi 1 olarak deðiþtir.
        Node* tmp = G->adj_list[vertex];
		while(tmp != NULL){
			printf("Gecici degisken - komsu: %d \n",tmp->label);
			DFS(G,tmp->label,visited); //tmp deðiþkeninin etiketi Rekürsif olarak gönderildi.
			//printf("Cozum baslatiliyor: \n");
			tmp = tmp->next;
		}       
		//Grafýn komþuluk listesindeki tepeleri tmp deðiþkenine atanýyor.
      
    }
    
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

void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> \n", path[i]);
    printf("%d -> ", path[0]);
}

int main()
{
    int noV=6; //(n-1) - 7 tepe için 6 vertices
    Graph* G=CreateNullGraph(noV); //Boþ graf oluþumu
    //Graftaki kenarlar oluþturuluyor
    add_edge(G,0,1,0,0);
    add_edge(G,0,2,0,0);
    add_edge(G,1,2,0,0);
    add_edge(G,2,3,0,0);
    add_edge(G,3,4,0,0);
    add_edge(G,3,5,0,0);
    add_edge(G,4,5,0,0);
   	int i;

    int visited[G->num_vertices]; //ziyaret edilenler[Grafýn_köseleri]

	for(i=0;i<G->num_vertices;i++) //tepeler ziyaret edildikçe ziyaret_edilen küme=0
	{
		visited[i]=0; //false
		
	    	
	}
    DFS(G,0,visited);
    

  
    return 0;
}
