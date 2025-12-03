#include <stdio.h>

int main (){
    FILE *file;
    file = fopen("jepin.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;  

    }
 
    return 0;

} 