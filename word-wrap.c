#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFSIZE 1000
#define INF 90000

void initializeMatrix(int **mat1, int row, int col){
    for( int i=0; i < row; i++ ){
        for( int j=0; j < col; j++ ){
             mat1[i][j] = 0;
        }
    }
}

void initializeArray(int *arr, int n){
    for( int i=0; i<n; i++ ){
        arr[i] = i;
        //printf("\n%d\n", arr[i]);
    }
}

int* allocateArray(int n){
    int *arr = 0;

    arr = (int*) malloc( n * sizeof(*arr) );

    if ( arr == 0 ){
        printf("an error occured!!");
    }

    initializeArray(arr,n);

    return arr;
}

int** allocateMatrix(int rows, int cols){
    int **mat = 0;

    mat = (int **)malloc(rows * sizeof(int*));

    if ( mat != 0 ){
        for(int i = 0; i < rows; i++){
            mat[i] = (int *)malloc(cols * sizeof(int));
        }
    } else {
        printf("an error occured!!");
    }

    initializeMatrix(mat,rows,cols);

    return mat;
}

void printArray(int *arr, int n, char *msg){
    printf("\n%s\n", msg);
    for( int i=0; i<n; i++ ){
        printf(" %5d ", arr[i]);
    }
}

void printMatrix(int **mat1, int row, int col, char *msg){

    printf("\n%s\n", msg);

    for( int i=0; i < row; i++ ){
        for( int j=0; j < col; j++ ){
            printf("%5d ", mat1[i][j]);
        }

        printf("\n");
    }
}

int getNumberOfWords(char buff[]){
    int i=0;
    int numberOfWords=0;

    while( buff[i] != '\0' ){
        if( buff[i] == ' ' ){
            numberOfWords++;
        }
        i++;
    }

    return numberOfWords + 1;
}

void setWordsLength(int* lengthArray, char buff[]){
    int n=0;
    int i=0;
    int len=0;

    while( buff[i] != '\0' ){

        if( buff[i] != ' ' ){
            len++;
        }else{
            // space character
            lengthArray[n] = len;
            n++;
            len = 0;
        }

        i++;
    }

    lengthArray[n] = len;

}

// olusacak olan her satirin uzunlugu hesaplýyor
// ve textteki karakterlerden o uzunluktakiler satirlara yaziyor
int* getLines(int *words,int n,char *text, int *length){
    // start from the last element
    int i=n;
    int satir[100]; // hold the lengths of the lines
    int satirSayisi=0; // number of lines
    int sum=0; // length sum of the words in a line

    printf("\n");
    while( 0 < i ){
        printf("%d. den %d. kelimeye\n", words[i], i);
        sum=0;
        for(int j=words[i]; j<=i; j++){
            sum += length[j-1] + 1; // plus space
        }
        sum--; // last space
        satir[satirSayisi] = sum;
        satirSayisi++;
        i = words[i] - 1;
    }


    for(int i=satirSayisi-1; i>=0; i--){
        printf("\n%d.satir uzunlugu : %d", i+1, satir[i]);
    }
    printf("\n");

    // satirin uzunluklari tersten olusturulmustu.
    int *linesLength = allocateArray(satirSayisi);
    int j=0;
    linesLength[j++] = satirSayisi+1; // dizinin uzunlugu ilk elemani olsun
    for(  int i=satirSayisi-1; i>=0; i--){
        linesLength[j] = satir[i];
        j++;
    }

    return linesLength;

}

void printText(int *linesLength, char *text){
    int charPointer=0;

    printf("\n");
    // satirin uzunluklari tersten olusturuldu.
    for(  int i=1; i<linesLength[0]; i++){
        for( int j=0; j<linesLength[i]; j++  ){
            printf("%c", text[charPointer]);
            charPointer++;
        }
        charPointer++;
        printf("\n");
    }
}

int getTotalCost(int *linesLength, int M){
    int totalCost=0;
    int space;

    for(  int i=1; i<linesLength[0]-1; i++){
        space = M - linesLength[i];
        totalCost += space*space*space;
    }

    return totalCost;

}


// length : has to be an array containing length value for each word
// n : size of the length array
// M : width of the line
int* wordWrap(int* length, int n, int M){
    n++;
    int **space=allocateMatrix(n,n);
    int **spaceCost=allocateMatrix(n,n);
    int cost[n];
    int *words = allocateArray(n);
    int i,j,len;


    // satira once tek kelime gelirse ne kadar bosluk olur
    // sonra kelime ekledikce kalan bosluktan yeni kelimenin uzunlugunu
    // ve aradaki bosluk karakteri icin 1 cikartiyoruz.
    for( i=1; i < n; i++ ){

        space[i][i] = M - length[i-1]; // one word on the line

        for ( j=i+1; j < n; j++ ){
            space[i][j] = space[i][j-1] - length[j-1] - 1; // new space after adding next word
        }
    }


    for ( i=1; i < n; i++ ){
        for ( j=i; j < n; j++ ){
            if (space[i][j] < 0)
                spaceCost[i][j] = INF;
            else if( j == (n-1) && space[i][j] >= 0 ) // last line
                spaceCost[i][j] = 0;
            else
                spaceCost[i][j] = space[i][j]*space[i][j]*space[i][j];
        }
    }

   // printMatrix(space, n, n, "Space Matrix : ");
   // printMatrix(spaceCost, n, n, "Space Cost Matrix : ");


    cost[0] = 0;
    for( j=1; j < n; j++ ){

        cost[j] = INF;

        for( i=1; i <= j; i++ ){
            if( cost[i-1] != INF && spaceCost[i][j] != INF && (cost[i-1] + spaceCost[i][j] < cost[j]) ){
                cost[j] = cost[i-1] + spaceCost[i][j];
                words[j] = i;
            }
        }
    }

    printArray(cost, n, "Cost Array : ");
    printArray(words, n, "Words Array :");

    return words;
}

int main(){
    FILE *fp;
    char buff[BUFFSIZE];
    int* wordsLengthArray;
    int *words; // satirlarin hangi kelimeden hangi kelimeye olacagini tutar
    int M = 23;
    int numberOfWords;

    fp = fopen("filtered_text.txt", "r");
    if( fp == NULL ) {
        printf("Couldnt read the filtered_text.txt...\n");
        return 1;
    }

    // get the text
    fgets(buff, BUFFSIZE, (FILE*)fp); // reads the whole line
    printf("Read text : \n \"%s\"\n", buff);

    // find the number of the words in the given text
    numberOfWords = getNumberOfWords(buff);
    printf("\nThe number of the words in the text : %d\n", numberOfWords);

    // create the array containing length value for each word as an element
    wordsLengthArray = allocateArray(getNumberOfWords(buff));
    setWordsLength(wordsLengthArray, buff);
    printArray(wordsLengthArray, numberOfWords, "Words Length Array : ");


    words = wordWrap(wordsLengthArray, numberOfWords, M);

    int *linesLength = getLines(words,numberOfWords, buff, wordsLengthArray);

    printText(linesLength, buff);

    printf("\nM : %d \n", M);
    printf("Total Cost : %d \n", getTotalCost(linesLength, M));


    fclose(fp);
    return 0;
}
