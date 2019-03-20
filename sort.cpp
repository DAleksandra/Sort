#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>


using namespace std;
int w=0;    //Wywolania rekurencyjne
const int PROCENT=0;   //Ile procent poczatku tablicy jest posortowane
const int LICZEBNOSC_ZBIORU = 1000000;  //Wielkosz tablicy do posortowania

/*----------------SORTOWANIE--------------------
------------------SZYBKIE-----------------------*/
void quicksort(int tab[], int lewy, int prawy)
{
    int i, j, piwot;
    i = lewy-1;
    j = prawy+1;
    piwot = tab[(lewy+prawy)/2]; //Piwot wybierany jako srodek tablicy

    while(i<=j)
    {
        while(piwot>tab[++i]);
        while(piwot<tab[--j]);
        if(i<=j)
        {
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
        else break;
    }

        if(lewy < j )
        {
            quicksort(tab, lewy, j);
        }
        if(i < prawy)
        {
            quicksort(tab, i, prawy);
        }
}
/*----------------SORTOWANIE--------------------
---------------PRZEZ SCALANIE-----------------------*/
void scalanie(int tab[], int lewy, int srodek, int prawy)
{

    int r1=srodek-lewy+1;
    int r2=prawy-srodek;
    int *pom1=new int[r1];
    int *pom2=new int[r2];
    int x, y, z;
    for(x=0; x<r1;x++) pom1[x]=tab[lewy+x];
    for(y=0; y<r2;y++) pom2[y]=tab[srodek+y+1];
    for(x=0, y=0, z=1; z<LICZEBNOSC_ZBIORU;z++)
    {
        if(x<r1&&y<r2)
        {
            if(pom1[x]<pom2[y])
            {
                tab[z]=pom1[x];
                x++;
            }
            else
            {
                tab[z]=pom2[y];
                y++;
            }
        }
        else if(x<r1)
        {
            tab[z]=pom1[x];
            x++;
        }
        else if(y<r2)
        {
            tab[z]=pom2[y];
            y++;
        }
        else break;
    }
    delete[] pom1;
    delete[] pom2;



}

void sortowanie_scalanie(int tab[], int lewy, int prawy)
{
    //Zostal jeden element = nie trzeba go sortowaæ = wyjœcie z rekurencji
    if(prawy<=lewy) return;

    //Wyznaczenie srodka
    int srodek = (prawy + lewy)/2;

    //Podzial na dwie tablice
    sortowanie_scalanie(tab, lewy, srodek);
    sortowanie_scalanie(tab, srodek+1, prawy);

    //Scalenie tablic juz posortowanych
    scalanie(tab, lewy, srodek, prawy);


}

/*----------------SORTOWANIE--------------------
-----------------INTROSPEKTYWNE----------------------*/
void NaprawKopiec(int tab[],int n, int i)

{
    int l=2*i, p=2*i+1, g=i;

    if(l<=n&&tab[l]>tab[i]) g=l;
    if(p<=n&&tab[p]>tab[g]) g=p;
    if(g!=i)
    {
        swap(tab[i], tab[g]);
        NaprawKopiec(tab,n,g);
    }

}

void StworzKopiec(int tab[], int n)

{
    for(int i=n/2-1;i>=0;i--)
        NaprawKopiec(tab,n,i);
}
void kopcowanie(int tab[])
{
    int r=LICZEBNOSC_ZBIORU;
    StworzKopiec(tab,r);

    for(int i=r;i>=0;i--)
    {
        swap(tab[i],tab[0]);
        r--;
        NaprawKopiec(tab,r,0);
    }

}


void sort_szybkie(int tab[], int lewy, int prawy, int w_max)
{
    if(w<w_max) //Sprawdzenie ile razy wywołała się rekurencyjnie funkcja sort_szybkie
                //Jesli przekracza w_max -> zakonczy wowalania sort_szybkie
{

    int i, j, piwot;
    i = lewy-1;
    j = prawy+1;
    piwot = tab[(lewy+prawy)/2];

        while(piwot>tab[++i]);
        while(piwot<tab[--j]);
        if(i<=j)
        {
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
        if(lewy < j )
        {
            w++;
            sort_szybkie(tab, lewy, j, w_max);
        }
        if(i < prawy)
        {
            w++;
            sort_szybkie(tab, i, prawy, w_max);
        }
}
}



void sortowanie_introspektywne(int tab[])
{
    int wysokosc= 2*log2(LICZEBNOSC_ZBIORU);    //Ustalenie maksymalnej ilosci wywolan rekurencyjnych sort_szybkie
    sort_szybkie(tab, 0, LICZEBNOSC_ZBIORU-1, wysokosc);
    kopcowanie(tab); //Po odpowiedniej ilości wywołan sort_szybkie -> sortowanie przez kopcowanie
}






int main()
{
    int *tab = new int[LICZEBNOSC_ZBIORU];
    int liczby=PROCENT*LICZEBNOSC_ZBIORU/100;
    clock_t start = clock();
    clock_t dodanie;


    srand((unsigned)time(NULL));
    for(int i=0; i<liczby;i++) {
        tab[i] =i;
    }

    for(int i = liczby; i < LICZEBNOSC_ZBIORU; i++) tab[i] = rand()  + liczby;

    //Wywolywanie wybranego algorytmu sortowania
    //quicksort(tab, 0, LICZEBNOSC_ZBIORU-1);
    //sortowanie_scalanie(tab, 0, LICZEBNOSC_ZBIORU-1);
    sortowanie_introspektywne(tab);
    dodanie=(clock()-start)/(CLOCKS_PER_SEC/1000);
    cout<<"Czas:  "<<dodanie<<endl;


    //wypisanie wyników
   // for(int i=0;i<LICZEBNOSC_ZBIORU;i++)
	//cout<<tab[i]<<" ";


	return 0;
}



