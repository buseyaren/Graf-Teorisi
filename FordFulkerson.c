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


//Bulunan çözümü yazdýrma
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}

void BFS(Graph* G, int vertex, int visited[], int distance[])
{
    visited[vertex] = 1;
    Node* komsular=NULL;
    int sayac = 0;
    while(sayac <= G->num_vertices)
    {
        //printf("Tepe : %d \n",vertex);
        Node* tmp = G->adj_list[vertex];
        while(tmp != NULL) //komsular bos degilse;
        {
            //printf("eklenen: %d \n",tmp->label);
            if(visited[tmp->label]==0 && listedevarmi(komsular,tmp->label)==0) //tmp degiskeni ziyaret edildi mi & komsuluk listesinde var mý
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
            printf("Komsular: %d -> \n",k->label);
            k =k->next ;
        }
         printf("\n");

        if(komsular != NULL) //komsu bulunmayýncaya dek;
        {
            Node* temp = komsular; //temp degiskeni olusturuldu
            while(temp->next != NULL) temp = temp->next;
            //printf("Son eleman: %d\n",temp->label);
            visited[temp->label] = 1;
            vertex=temp->label;
            if(komsular->label == temp->label)
                komsular=NULL;
            else
            {
                Node* son = komsular;
                while(komsular->next->label != temp->label)
                {
                	komsular=komsular->next;
				}
                        
                komsular->next = NULL;
                komsular=son;
            }

        }
        sayac ++;
    }
}

int fordFulkersonSolution(Graph* G, int s, int t){
	int u,v; //Ýki tepe deðiþkeni
	int resG[Vertex][Vertex]; 
	for (u = 0; u < Vertex; u++) {
		for (v = 0; v < Vertex; v++) {
			 resG[u][v] = G; 
		}
	}
	int root[Vertex]; // BFS algoritmasýna gönderilecek root deðiþkeni.
	int maksimumakis = 0;
	
	while (BFS(resG, s, t, root)) //yol !=NULL - Graph,visited,vertex, distance
    { 
        // Maksimum Akýþ Bulunmasý
        int yol = INT_MAX; // 2147483647
        for (v=t; v!=s ; v=root[v]) 
        { 
            u = root[Vertex]; 
            yol = min(yol, resG[u][v]); 
        } 
  
        //kenar ve kapasitelerin güncellenmesi
        for (v=t; v != s; v=root[v]) 
        { 
            u = root[v]; 
            resG[u][v] -= yol; //ters kapasiteli yol
            resG[v][u] += yol; //normal kapasiteye sahip yol
        } 
  
        // Hafýzada tutulan kapasitenin toplanmasý
        maksimumakis += yol; 
    } 
  
    return maksimumakis; 
	
        
}
//Ana menü
int main()
{
    int noV=9; //Köþe Sayýsý - (n-1)
    int src;
    int trg;
    Graph* G=CreateNullGraph(noV); //Köþe sayýsý kadar düðüm olan boþ graf oluþturma
    //Kenar ekleme
   	add_edge(G,0,1,1,16);
   	add_edge(G,0,3,1,13);
   	add_edge(G,1,3,1,13);
   	add_edge(G,3,1,1,2);
   	add_edge(G,1,2,1,12);
   	add_edge(G,2,3,1,9);
   	add_edge(G,3,4,1,14);
   	add_edge(G,4,2,1,7);
   	add_edge(G,2,5,1,20);
   	add_edge(G,4,5,1,4);
   	//AdjMatris(G);
	//fordFulkersonSolution(G,src,trg);
    return 0;
}
