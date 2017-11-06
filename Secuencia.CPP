//@XDEMOND
#include <conio.h>
#include <stdlib.h>

#define LinpPag 	100
#define N	10
#define so	2048
#define Memoria	10240 //=10kB
#define MarcoPag	64   //KBytes

struct MMT
{
	int numMarco,locIni, estadoTMM;
   MMT *sig;
}*iM=NULL, *fM=NULL, *nuevoM=NULL, *auxM=NULL;

struct Secuencia
{
	int num,pag;
   Secuencia *sig;
}*iS=NULL,*fS=NULL,*nuevoS=NULL,*auxS=NULL;

struct JT
{
	int tarea,locTMP;
   int secuenciaJT[10];
   JT *sig;
}*iJ=NULL, *fJ=NULL, *nuevoJ=NULL, *auxJ=NULL;

struct PMT
{
	int numPagina,locNumeroGuardo;
   PMT *sig;
}*iP[N], *fP[N], *nuevoP[N], *auxP[N];


void crearMMT()
{
	int i=0,Marcos;

   Marcos=15;
   cout<<"Marcos: "<<Marcos<<endl;

   do
   {
   	if(iM==NULL)
      {
      	iM = (MMT *)malloc(sizeof(MMT));
         iM->numMarco = i;
         iM->locIni = (i*MarcoPag);
         iM->estadoTMM = 0;

         iM->sig=NULL;
         fM = iM;
      }
      else
      {
      	nuevoM = (MMT *)malloc(sizeof(MMT));
         nuevoM->numMarco = i;
         nuevoM->locIni = (i*MarcoPag);
         nuevoM->estadoTMM = 0;

         fM->sig = nuevoM;
         fM = nuevoM;
      }
      i++;
   }while(i<Marcos);
}

void crearJT()
{
	int i=1, j;

   do
   {
   	if(iJ==NULL)
      {
      	iJ = (JT *)malloc(sizeof(JT));
         iJ->tarea = i;
         for(j=0;j<10;j++)
         {
         	if(j==0)
            	iJ->secuenciaJT[j]=0;
            else
         		iJ->secuenciaJT[j]=rand()%5;
         }
         iJ->sig=NULL;
         fJ = iJ;

      }
      else
      {
      	nuevoJ = (JT *)malloc(sizeof(JT));
         nuevoJ->tarea = i;
         for(j=0;j<10;j++)
         {
         	if(j==0)
            	nuevoJ->secuenciaJT[j]=0;
            else
         		nuevoJ->secuenciaJT[j]=rand()%5;
			}
         fJ->sig = nuevoJ;
         fJ = nuevoJ;
         fJ->sig=NULL;
      }
      i++;
   }while(i<=N);
}

void imprimeMMT()
{
   auxM = iM;

	cout<<" \t\t\t\t*****Tabla de Mapa de Memoria*****"<<endl;
   cout<<"\nNum.Marco\tLoc Ini\t\tEstado\n";
   while(auxM!=NULL)
   {
   	cout<<auxM->numMarco<<"\t\t"<<auxM->locIni<<"\t\t"<<auxM->estadoTMM<<endl;
      auxM = auxM->sig;
   }
}

void imprimeJT()
{
   auxJ = iJ;

	cout<<"\n \t\t\t\t*****Tabla de Tareas*****"<<endl;
   cout<<"\nTarea\tNoLineas\tlocPMT\tNumPaginas\n";
   while(auxJ!=NULL)
   {
   	cout<<"J"<<auxJ->tarea<<"\t\t"<<"Secuencia : ";
      for(int i=0; i<10;i++)
      {
      	cout<<auxJ->secuenciaJT[i]<<",";
      }
      cout<<"\n";
      auxJ = auxJ->sig;
   }
}

void imprimePMT()
{
	int i=1;
	auxJ = iJ;
   cout<<"\n  \t\t\t\t*****Tabla PMT*****"<<endl;

   do
   {
   	auxP[i] = iP[i];
   	cout<<"\nTabla J"<<i<<endl;
      cout<<"Pagina\tMarco\n";
      while(auxP[i]!=NULL)
      {
      	cout<<"P"<<auxP[i]->numPagina<<"\t"<<auxP[i]->locNumeroGuardo<<endl;
         auxP[i] = auxP[i]->sig;
      }
      i++;
      auxJ = auxJ->sig;
      //getch();
   }while(i<=N);
}

void asignaSO()
{
	auxM = iM;
   int totalM=0;

   cout<<"\Asigna el SO"<<endl;

	while(auxM!=NULL)
   {
   	if(auxM->estadoTMM!=1)
      {
      	totalM = totalM + auxM->locIni;
      	if(totalM > so)
         {
         	goto exit;
         }
         auxM->estadoTMM = 1;

      }
      auxM = auxM->sig;
   }
   exit:
}

void main ()
{
	clrscr();
   crearMMT();
   imprimeMMT();
   crearJT();
   imprimeJT();
  	getch();

}

