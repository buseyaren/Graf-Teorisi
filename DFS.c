#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<stdbool.h>

//Düðüm Oluþturma (Etiket, Aðýrlýk, Next)
struct node
{
    int label;
    int weight;
    struct node* next;
};

//Düðümü yeniden adlandýrma
typedef struct node Node;

//Graf Yapýsý Oluþturma
struct graph
{
    int num_vertices; //Köþe Sayýsý
    Node** adj_list; //Komþuluk Listesi
};

//Grafý yeniden adlandýrma
typedef struct graph Graph;

//Yeni düðüm oluþturma
Node* createNode(int v,int weight)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->label = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//Boþ graf oluþturma
Graph* CreateNullGraph(int vertices)
{

    Graph* G = malloc(sizeof(Graph)); //dinamik bellekten Graf yapýsý kadar yer ayýrma
    G->num_vertices = vertices;

    G->adj_list = malloc(vertices * sizeof(Node*)); //Grafýn komþuluk matrisi = Düðümün boyutu * köþeler (Tepe) kadar bellekten yer ayýrma

    int i;
    for (i = 0; i < vertices; i++) { //tüm tepeleri gezecek for döngüsü
        G->adj_list[i] = NULL; //boþ graf olduðu için komþuluk matrisi Boþ
    }
    return G;
}

//Düðümlerin arasýndaki kenarlarýn oluþturulmasý
void add_edge(Graph* G, int src, int dest,int directed, int weight) //kaynaktan hedefe, yönlü-yönsüz ve aðýrlýklý düðümlere kenar ekleme
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

//Grafý ekrana yazdýrma
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

//Dereceleri yazdýrma
void printDegrees(Graph* G)
{
    int v;
    for (v = 0; v < G->num_vertices; v++)
    {
        int d =0;
        Node* temp = G->adj_list[v];
        printf("Dugumun derecesi %d = ", v);
        while (temp)
        {
            d++;
            temp = temp->next;
        }
        printf("%d\n",d);
    }
}

//DFS dolaþýmýný hesaplayan fonksiyon
void DFS(Graph* G, int vertex, int visited[]) //Graf, tepe, ziyaret_edilen[] 
{
    if(visited[vertex] == 0) //ziyaret_edilen dizisi boþsa -- ziyaret edilen tepe yok ise
    {
        //printf("%d -> ",vertex);
        visited[vertex] = 1; //ziyaret edilen tepe var
        Node* tmp = G->adj_list[vertex]; //ziyaret edilen tepeyi komþuluk matrisine ekleme
        while(tmp != NULL)
        {
            DFS(G,tmp->label,visited); //temp'e atanan tepenin etiketi ve aðýrlýðý ile DFS fonksiyonuna gönder - RECURSIVE
            tmp = tmp->next; //bir sonraki tepeye geç
        }
    }
}

//Baðlý bileþen sayýsý
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

//Komþu olup olmadýðýný kontrol eden fonksiyon
int isNeighbor(Graph* G, int src, int dest) //Graf, kaynak, hedef
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

//Komþuluk matrisini yazdýrma
void AdjMatris(Graph* G)
{
    int i,j;
    FILE *fp = fopen("output.txt","w"); //output.txt dosyasý "yazma" modunda açýlýr
    for(i=0;i<G->num_vertices;i++) //tüm köþeler bitene kadar gezilecek
    {
        for(j=0;j<G->num_vertices;j++)
        {
            fprintf(fp,"%d ",isNeighbor(G,i,j)); //dosyaya komþularýný yazdýrma
        }
        fprintf(fp,"\n");
    }
    fclose(fp); //dosyayý kapatma
}

//Yol güvenilir mi
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

//Bulunan çözümü yazdýrma
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}

//Ana menü
int main()
{
    int noV=5; //Tepe Sayýsý
    Graph* G=CreateNullGraph(noV); //Tepe sayýsý kadar düðüm olan boþ graf oluþturma
    //Kenar ekleme
    add_edge(G,0,4,0,0);
    add_edge(G,0,2,0,0);
    add_edge(G,4,2,0,0);
    add_edge(G,2,1,0,0);
    add_edge(G,2,3,0,0);
    add_edge(G,1,3,0,0);
    add_edge(G,0,3,0,0);

    //AdjMatris(G);
    return 0;
}

