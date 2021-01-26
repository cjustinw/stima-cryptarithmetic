/*
    Nama        : Christopher Justine William
    NIM         : 13519006
    Kelas       : K-01
    Mata Kuliah : Strategi Algoritma
    Bahasa      : C
    Deskripsi   : Penyelesaian Cryptarithmetic dengan Algoritma Brute Force
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* 
    Untuk menjalankan program
    masukkan jumlah_string 
    masukkan jumlah kolom_string_terpanjang
    masukkan nama_file yang ingin dibaca
*/

#define jumlah_string 3
#define jumlah_kolom_string_terpanjang 5
#define nama_file "../test/1.txt"

/* Definisi Tipe Data */
typedef struct 
{
    char Alp;
    int Val;
    int Pos;
} Char;

typedef struct 
{
    Char Tab[10];
    int Neff;
} String;

typedef struct 
{
    String Tab[10];
    int Neff;
} List;


void inisialisasiPos(List* L)
/* Menginisialisasi posisi setiap character di list */
{
    int i, j;
    for(i = 0; i < L->Neff; i++){
        for(j = 0; j < L->Tab[i].Neff; j++){
            L->Tab[i].Tab[j].Pos = j;
        }
    }
}

void inisialisasiValue(List* L)
/* Menginisialisasi nilai setiap character di list */
{
    int i, j;
    for(i = 0; i < L->Neff; i++){
        for(j = 0; j < L->Tab[i].Neff; j++){
            L->Tab[i].Tab[j].Val = 0;
        }
    }
}

void printInput(List L)
/* Mencetak input ke layar */
{
    int i, j;
    for(i = 0; i < L.Neff; i++){
        if((i) == L.Neff-2){
            printf("+");     
        }
        else{
            printf(" ");
        }
        for(j = 0; j < L.Tab[i].Neff; j++){
            printf("%c", L.Tab[i].Tab[j].Alp); 
        }
        printf("\n");
        if(i == L.Neff-2){
            printf(" ");
            for(j = 0; j < L.Tab[i].Neff; j++){
                printf("-");
            }
            printf("\n");
        }
    }
}

void printOutput(List L)
/* Mencetak output ke layar */
{
    int i, j;
    for(i = 0; i < L.Neff; i++){
        if((i) == L.Neff-2){
            printf("+");     
        }
        else{
            printf(" ");
        }
        for(j = 0; j < L.Tab[i].Neff; j++){
            if(L.Tab[i].Tab[j].Alp != ' '){
                printf("%d", L.Tab[i].Tab[j].Val);     
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
        if(i == L.Neff-2){
            printf(" ");
            for(j = 0; j < L.Tab[i].Neff; j++){
                printf("-");
            }
            printf("\n");
        }
    }
}

void isiPos(String* S, int arr[])
/* Mengisi String S dengan nilai hasil permutasi yang disimpan di arr */
{
    int i;
    for(i = 0; i < S->Neff; i++){
        S->Tab[i].Val = arr[i];
    }
}

int isMember(String S, char c)
/* Mengecek apakah suatu char merupakan anggota String S */
{
    int i = 0;
    int member = 0;
    while(i < S.Neff && !member){
        if(S.Tab[i].Alp == c){
            member = 1;
        }
        i++;
    }
    return member;
}

void charList(List L, String* S)
/* Mengisi String S dengan char dari List L */
{
    int i, j;
    for(i = 0; i < L.Neff; i++){
        for(j = 0; j < L.Tab[i].Neff; j++){
            if(!isMember(*S, L.Tab[i].Tab[j].Alp) && (L.Tab[i].Tab[j].Alp != ' ')){
                S->Tab[S->Neff].Alp = L.Tab[i].Tab[j].Alp;
                S->Neff++;
            }
        }
    }
}

int search(String S, char c)
/* Mereturn nilai dari char c didalam String S */
{
    int i = 0;
    while(i < S.Neff && S.Tab[i].Alp != c){
        i++;
    }
    return S.Tab[i].Val;
}

void check(List* L, String* S, int* found)
/* Mengecek solusi dari sebuah hasil permutasi */
{
    int i, j;
    for(i = 0; i < L->Neff; i++){
        for(j = 0; j < L->Tab[i].Neff; j++){
            if(L->Tab[i].Tab[j].Alp != ' '){
                L->Tab[i].Tab[j].Val = search(*S, L->Tab[i].Tab[j].Alp);
            }
        }
    }
    
    if(L->Tab[L->Neff-1].Tab[0].Val == 0){
        return;
    }
    else{
        i = 0;
        int bool = 1;
        while((i < L->Neff-1)&&(bool)){
            j = 1;
            while((j < L->Tab[i].Neff)&&(bool)){
                if((L->Tab[i].Tab[j].Alp != ' ')&&(L->Tab[i].Tab[j-1].Alp == ' ')&&(L->Tab[i].Tab[j].Alp == 0)){
                    return;
                }
                else if(L->Tab[i].Tab[j].Alp == ' '){
                    j++;
                }
                else{
                    bool = 0;
                }
            }
            i++;
        }
    }
    int val = 0;
    for(j = L->Tab[0].Neff-1; j >= 0; j--){
        for(i = 0; i < L->Neff-1; i++){
            val += L->Tab[i].Tab[j].Val;
        }
        if(val == L->Tab[L->Neff-1].Tab[j].Val){
            val = 0;
        }
        else if(((val%10) == L->Tab[L->Neff-1].Tab[j].Val)&&(j != 0)){
            val = val/10;
        }
        else{
            return;
        }
    }
    *found = 1;
}

void swap(int arr[], int i, int j)
/* Menukarkan element */
{
    int tmp = arr[j];
    arr[j] = arr[i];
    arr[i] = tmp;
}

void reverse(int arr[], int i, int j)
/* Membalikan urutan element dalam suatu rentang nilai di dalam array */
{
    swap(arr,i,j);
    if((j-i) > 2){
        reverse(arr,i+1,j-1);
    }
}

void permutasi(int arr[], int n, int k, int* status)
/* Mencari permutasi nilai yang disimpan di dalam array*/
{
    int i = k; 
    int limit = k-1;
    while((arr[i] <= arr[limit])&&(i < n)){
        i++;
    }
    if(i < n){
        swap(arr, limit, i);
    }
    else{
        reverse(arr, k, n-1);
        int j = limit-1;
        while((arr[j] >= arr[j+1])&&(j >= 0)){
            j--;
        }
        if(j >= 0){
            i = n - 1;
            while((arr[j] >= arr[i])&&(i > j)){
                i--;
            }
            swap(arr, j, i);
            reverse(arr, j+1, n-1);
        }
        else{
            *status = 0;
            return;
        }
    }
}

void cryptArithmetic(String* S, List* L, int arr[], int n, int k)
/* Mencari dan menampilkan solusi dari persoalan */
{
    int status = 1, found = 0, count = 1;
    while(status){
        isiPos(S,arr);
        check(L,S,&found);
        if(found){
            printOutput(*L);
            printf("\nJumlah tes yang dilakukan : %d\n", count);
            found = 0;
        }
        if(n == k){
            k--;
        }
        permutasi(arr,n,k,&status);
        count++;
    }
}

int main()
{
    List L;
    L.Neff = jumlah_string;
    int i;
    for(i = 0; i < L.Neff; i++){
        L.Tab[i].Neff = jumlah_kolom_string_terpanjang;
    }

    /* Baca File*/
    char str1[100],str2[100];
    FILE *file = fopen(nama_file, "r");
    if (file == NULL)
    {
        printf("Error!");
        return 1;
    }
    
    while(fgets(str1, sizeof(str1), file)){
        strcat(str2,str1);
    }
    fclose(file);

    /* Memasukkan hasil baca file ke ADT */
    int j, k, count = 0;
    
    for(i = 0; i < L.Neff; i++){
        if(i == L.Neff-1){
            count+= L.Tab[i].Neff+2;
        }
        for(j = 0; j < L.Tab[i].Neff; j++){
            count++;
            L.Tab[i].Tab[j].Alp = str2[count];
        }
        count++;
    }

    /* Start Waktu */
    clock_t t;
    t = clock();
    
    /* Proses */
    printInput(L);
    printf("\n");

    inisialisasiPos(&L);
    inisialisasiValue(&L);
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    String S;
    S.Neff = 0;
    charList(L,&S);

    cryptArithmetic(&S,&L,arr, 10, S.Neff);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("Time : %.2f s\n\n", time_taken);

    return 0;
}