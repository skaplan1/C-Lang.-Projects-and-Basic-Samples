//140201030-SADIK KAPLAN-ProLab2-1.Proje
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#define MAX 82
#define INF 99999

void djikstra2(int mesafeler_matrisi[MAX][MAX],int n,int baslangic_noktasi,char sehir[MAX][MAX]){
    //Fonksiyondaki kullanylacak fonksiyonlary tanymlaryz
    int maliyet[MAX][MAX],mesafe[MAX],hafiza[MAX];
    int gecis_sayisi[MAX],sehir_sayisi,min_mesafe,siradaki_sehir,i,j;
        //Dosyadan okunacak mesafeyi maliyet matrisine atayaca?yz.
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(mesafeler_matrisi[i][j]==0){
                maliyet[i][j]=INF;
            }
            else{
                maliyet[i][j]=mesafeler_matrisi[i][j];
            }
        }
    }
    for(i=0;i<n;i++){
        mesafe[i]=maliyet[baslangic_noktasi][i];
        hafiza[i]=baslangic_noktasi;
        gecis_sayisi[i]=0;
    }

    mesafe[baslangic_noktasi]=0;
    gecis_sayisi[baslangic_noktasi]=1;
    sehir_sayisi=1;

    while(sehir_sayisi<n-1){
        min_mesafe=INF;
        //2.Djikstra için bir sonraki node'a minumum mesafe atama
        for(i=0;i<n;i++){
            if(mesafe[i]<min_mesafe&&!gecis_sayisi[i]){
                min_mesafe=mesafe[i];
                siradaki_sehir=i;
            }
        }
        //siradaki_sehir degiskeni uzerinden daha iyi bir yol olup olmadigi sorgulanir
        gecis_sayisi[siradaki_sehir]=1;
        for(i=0;i<n;i++){
            if(!gecis_sayisi[i]){
                if(min_mesafe+maliyet[siradaki_sehir][i]<mesafe[i]){
                    mesafe[i]=min_mesafe+maliyet[siradaki_sehir][i];
                    hafiza[i]=siradaki_sehir;
                }
            }
        }
        sehir_sayisi++;
    }
    //Daha az maliyetli yol var mi sorgusu
    for(i=0;i<n;i++){
        if(i!=baslangic_noktasi){
            if(1){
                printf("\n\nSehirler arasi mesafe = %d\n",mesafe[i]);
                printf("\nYol Haritasi =  %s",sehir[i+1]);
                j=i;

                while(j!=baslangic_noktasi){
                    j=hafiza[j];
                    printf(" <-- %s",sehir[j+1]);
                }
            }
        }
    }

    printf("\n\n\nBirinci Program sonlandi.. \n\n\n");
}

//dijkstra icin bir fonksiyon tanimlanir
void djikstra(int mesafeler_matrisi[MAX][MAX],int n,int baslangic_noktasi,int bitis_noktasi,char sehir[MAX][MAX]){
    //kullanilacak olan degiskenler tanimlanir
    int maliyet[MAX][MAX],mesafe[MAX],hafiza[MAX];
    int gecis_sayisi[MAX],sehir_sayisi,min_mesafe,siradaki_sehir,i,j;
    //mesafe matrisi girdileri maliyet matrisine okutulur
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(mesafeler_matrisi[i][j]==0){
                maliyet[i][j]=INF;
            }
            else{
                maliyet[i][j]=mesafeler_matrisi[i][j];
            }
        }
    }

    for(i=0;i<n;i++){
        mesafe[i]=maliyet[baslangic_noktasi][i];
        hafiza[i]=baslangic_noktasi;
        gecis_sayisi[i]=0;
    }

    mesafe[baslangic_noktasi]=0;
    gecis_sayisi[baslangic_noktasi]=1;
    sehir_sayisi=1;

    while(sehir_sayisi<n-1){
        min_mesafe=INF;
        //siradaki_sehir degiskenine minimum mesafe verilir
        for(i=0;i<n;i++){
            if(mesafe[i]<min_mesafe&&!gecis_sayisi[i]){
                min_mesafe=mesafe[i];
                siradaki_sehir=i;
            }
        }
        //siradaki_sehir degiskeni uzerinden daha iyi bir yol olup olmadigi sorgulanir
        gecis_sayisi[siradaki_sehir]=1;
        for(i=0;i<n;i++){
            if(!gecis_sayisi[i]){
                if(min_mesafe+maliyet[siradaki_sehir][i]<mesafe[i]){
                    mesafe[i]=min_mesafe+maliyet[siradaki_sehir][i];
                    hafiza[i]=siradaki_sehir;
                }
            }
        }
        sehir_sayisi++;
    }
    //bitis sehrine olan mesafe ve yol yazdirilir
    for(i=0;i<n;i++){
        if(i!=baslangic_noktasi){
            if(i==bitis_noktasi){
                printf("\n\nSehirler arasi mesafe = %d\n",mesafe[i]);
                printf("\nYol Guzergahi =  %s",sehir[i+1]);
                j=i;

                while(j!=baslangic_noktasi){
                    j=hafiza[j];
                    printf(" <-- %s",sehir[j+1]);
                }
            }
        }
    }

    printf("\n\n\n ...Program sonlanmistir... \n\n\n");
}

int main(){
    /*int secim;
    printf("Iki il arasi mesafe icin 1i;\nBir ilin diger illere en kisa yolu icin 2yi seciniz:");
    scanf("%d",&secim);
    */
    //türkçe karakterlerlerin kullanimi için bunu kullanabiliriz
    setlocale(LC_ALL,"Turkish");

    int mesafeler_matrisi[MAX][MAX],i,j,k,sehir_sayisi,baslangic_noktasi=-1,bitis_noktasi=-1,n,uzaklik[MAX];
    FILE *dosya_sehir_kod,*dosya_sehir_mesafe;
    char okuma[MAX][MAX],sehir[MAX][MAX],sehir1[MAX][MAX],sehir2[MAX][MAX],sehir_mesafe[MAX][MAX],baslangic[MAX],bitis[MAX];
    if((dosya_sehir_kod=fopen("sehir kod.txt","r+"))==NULL){
        printf("Dosya okunamadi konumu tekrar kontrol ediniz !!!");
    }

    dosya_sehir_kod = fopen("sehir kod.txt","r+");
    //okunan satirlar bu kysymda okuma ve sehir dosyalarina atilir
    for(n=0; n<=82; n++){
        fgets(okuma[n],20,dosya_sehir_kod);
        strcpy(sehir[n],strtok(okuma[n],"-"));
        if(feof(dosya_sehir_kod)){
            break;
        }
    }
    sehir_sayisi = n;
    //baslangicta mesafe_matrisinin tum elemanlari 0 atadim
    for(i=0;i<sehir_sayisi;i++){
        for(j=0;j<sehir_sayisi;j++){
            mesafeler_matrisi[i][j]=0;
        }
    }

    dosya_sehir_mesafe = fopen("sehir mesafe.txt","r+");
    if((dosya_sehir_kod=fopen("sehir mesafe.txt","r+"))==NULL){
        printf("Dosya okunamadi konumu tekrar kontrol ediniz !!!");
    }
    //bu  kisimda ise diger dosyamizdaki degiskenler tanimlanan diger degiskenlere atilir
    for(n=0; n<=MAX; n++){
        fgets(okuma[n],50, dosya_sehir_mesafe);
        strcpy(sehir1[n],strtok(okuma[n],"-"));
        strcpy(sehir2[n],strtok(NULL,"-"));
        strcpy(sehir_mesafe[n],strtok(NULL,"-"));
        uzaklik[n] = atoi(sehir_mesafe[n]);
        if(feof(dosya_sehir_mesafe)){
            break;
        }
    }
    //sehirlerin kodlari bulunup uzakliklar mesafe matrisine eklenir
    for(i=0; i<=MAX; i++){
        if(strlen(sehir1[i])==0){
            break;
        }
        for(j=0; j<=MAX; j++){
            if(strcmp(sehir1[i],sehir[j])==0){
                for(k=0; k<=MAX; k++){
                    if(strcmp(sehir2[i],sehir[k])==0){
                        mesafeler_matrisi[j-1][k-1] = uzaklik[i];
                        mesafeler_matrisi[k-1][j-1] = uzaklik[i];
                    }
                }
            }
        }
    }
    //baslangic sehri istenip sorgulamasi yapilir
    burasi: printf("Baslangic sehrini giriniz: ");
    gets(baslangic);
    //baslangic sehrinin kontrolu yapilir ve kodu bulunur
    for(i=0; i<=MAX; i++){
        if(strcmp(baslangic,sehir[i])==0){
            baslangic_noktasi=i-1;
        }
    }
    if (baslangic_noktasi==-1){
        printf("Yanlis bir sehir ismi girdiniz!\n\n");
        goto burasi;
    }
    djikstra2(mesafeler_matrisi,sehir_sayisi,baslangic_noktasi,sehir);
    burasi2: printf("Baslangic sehrini girin: ");
    gets(baslangic);
    printf("\nBitis sehrini girin: ");
    gets(bitis);
    for(i=0; i<=MAX; i++){
        if(strcmp(baslangic,sehir[i])==0){
            baslangic_noktasi=i-1;
        }
    }

    for(i=0; i<=MAX; i++){
        if(strcmp(baslangic,sehir[i])==0){
            baslangic_noktasi=i-1;
        }
    }


    //bitis sehrinin kontrolu yapilir ve kodu bulunur
    for(i=0; i<=MAX; i++){
        if(strcmp(bitis,sehir[i])==0){
            bitis_noktasi=i-1;
        }
    }
    if (bitis_noktasi==-1){
        printf("Yanlis bir sehir ismi girdiniz!\n\n");
        goto burasi2;
    }
    //dijkstra fonksiyonu gerekli degiskenler ile cagirilir
    djikstra(mesafeler_matrisi,sehir_sayisi,baslangic_noktasi,bitis_noktasi,sehir);
    return 0;
}
