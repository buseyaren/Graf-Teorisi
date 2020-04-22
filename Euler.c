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

//Yol güvenilir mi
bool isSafe(int v, Graph* G, int path[], int pos)
{
    int i;
    if (!isNeighbor(G,path[pos - 1],v)) //yolun bir önceki düðümü eklemek istenen düðüm ile komsu mu
        return false;

    for ( i= 0; i < pos; i++) 
        if (path[i] == v)//daha önce yola eklendi mi
            return false; //yola eklenemez

    return true; //yola eklenebilir
}

//Bulunan çözümü yazdýrma
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}


void eulerYoluYazdýr(Graph* G){
	int tek=0;
	for(int i= 0; i <G->num_vertices ; i++){
	//tek derece
		if((sizeof(G->num_vertices[i]) %2 != 0){
			tek=i;
		}
	}
	baslangicTuruYazdir(tek);
}

void sonrakiTepeGecerliMi(int u,int v){
	//tek tepe noktasý mevcut ise;
	if(sizeof(G->num_vertices[u]) == 1)
	{
		return true;
	}
	//birden fazla tepe noktasý mevcut ise;
	else
	{
		//u-v köprü deðil ise
		//u'dan ulasýlabilen kose sayýsý
		visited=[false]*(G->num_vertices[v]);
			
		//kenar gezildikten sonra gezilen kenarýn silinmesi
		kenarSil(u,visited);
		visited=[false]*(G->num_vertices[v]);
			
		//kenarýn grafiðe yeniden eklenmesi
		add_edge(G,u,v,0,0);
		return false;
	}
}
void baslangicTuruYazdir(Graph* G, int u){
	int v;
	for(v=0;v < G->num_vertices; v++){
		if(sonrakiTepeGecerliMi(u,v))
		{
			printf("Gecerli tepeler: %d \t %d \n",u,v);
			//kenar gezildikten sonra gezilen kenarýn silinmesi
			kenarSil(u,visited);
			baslangicTuruYazdir(G,v);
		}			
	}
}


//ziyaret edilen kenar listeden kaldýrýlacak
void kenarSil(Graph* G, int k1, int k2){
	for (int i = 0; i < G->num_vertices; i++) {
		if (i == k2){
			G->num_vertices[i].pop(k2);
		}
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
    AdjMatris(G); //komsuluk matrisi dosyaya yazdýrýlýyor
	
	//printDegrees(G);
	//eulerYoluYazdýr(G);

    return 0;
}
