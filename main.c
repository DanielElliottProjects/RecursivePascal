#include <stdio.h>
#include <stdlib.h>
long *array;
int arrayLen;
//defined globally for ease of calling recursive funcs

int getCoeff(int row, int col){
    int targetLoc = row * arrayLen + col;
    array[0] = 1;
    // Base cases should return immediately
    if(col == 0 || col == row || row == 0 || row == 1){
        array[targetLoc] = 1;
        return array[targetLoc];
    }
    //if previously assigned we don't want to overwrite
    if(array[targetLoc] != 0){
        return array[targetLoc];
    }
    else{
        //C(n,k) = C(n -1,k) + C(n-1, k-1)
        array[targetLoc] = getCoeff(row - 1, col) + getCoeff(row - 1, col - 1);
        return array[targetLoc];
    }
}

int createRow(int row){
    //gets the values for the array by starting at last row, then will recursively work through the rest of the array
    for(int i = 0; i <= row; i++){
        getCoeff(row, i);
    }
    return 0;
}

int printArray(){
    int numberWidth = 4; // Adjust this based on how large your numbers might get
    
    // Print each row from 0 to desiredRow
    for(int currentRow = 0; currentRow < arrayLen; currentRow++){
        // Calculate spacing for centering the row
        int rowElements = currentRow + 1; // Number of elements in current row
        int totalRowWidth = arrayLen * numberWidth;
        int rowWidth = rowElements * numberWidth;
        int leadingSpaces = (totalRowWidth - rowWidth) / 2;
        
        // Print leading spaces for centering
        printf("%*s", leadingSpaces, "");
        
        // Print the numbers in the row
        for(int i = 0; i <= currentRow; i++){
            printf("%*ld ", numberWidth, array[currentRow * arrayLen + i]);
        }
        printf("\n");
    }
    return 0;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <number_of_rows>\n", argv[0]);
        return 1;
    }

    int desiredRow = atoi(argv[1]);
    if(desiredRow < 0){
        printf("Please enter a non-negative number.\n");
        return 1;
    }
    
    arrayLen = desiredRow + 1;
    array = malloc(arrayLen * arrayLen * sizeof(long));
    if(array == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    // Initialize array
    for(int row = 0; row < arrayLen; row++){
        for(int col = 0; col < arrayLen; col++){
            array[row * arrayLen + col] = 0;
        }
    }
    
    // Only need to create the desired row - recursion will fill in previous rows
    createRow(desiredRow);
    
    printArray();
    free(array);
    return 0;
}
