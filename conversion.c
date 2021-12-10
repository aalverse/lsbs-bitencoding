
#include "./header/conversion.h"

typedef struct Binary{
    int size;
    unsigned char * data;
}Binary;

void ln(int lines){
   for(int i  = 0; i < lines; i++){
        printf("\n");
   }
}

void print_args(int argc, char *argv[]) {
    ln(1);
    for(int i = 0; i < argc; i++){
        printf(CYN "%s" RESET, argv[i]);
        ln(1);
    }
}

int requestInt(){
    int number;
    printf(CYN);
    scanf("%d", &number);
    printf(RESET);
    return number;
}

void promptUserSeed(){
    printf("Please enter a seed for random number generation: ");
    srand(requestInt());
    ln(1);
}

int randomNumber(){
    return rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER;
}

void print_binary(Binary * bin){
    printf(GRN "Binary Array: ");
    for(int i = bin->size-1; i >= 0 ; i--){
        PRINTBIN(bin->data[i]);
        printf(" ");
    }
    printf(RESET);
}

void init_bytes(Binary * bin){
    int i;
    for(i = 0; i < bin->size; i++){
        bin->data[i] = randomNumber();
    }
}

int get_mask(int pos, unsigned char byte){
    return (byte & ( 1 << pos ));
}

int get_bit(int pos, unsigned char byte){
    return (byte & ( 1 << pos )) >> pos;
}

void setlsbs(unsigned char *p, unsigned char b0){
    // printf(CYN "\n\t%c : %d" RESET, *p, b0);
    if(b0==0 && get_bit(0, *p) == 1){
        *p -=1;
        return;
    }
    *p |= b0;
    // printf(RED "\n\t%c : %d" RESET, *p, b0);
}

unsigned char getlsbs(Binary * bin){
    unsigned char byte = '\x0';
    for(int i = 0; i < bin->size; i++){
        byte |= (bin->data[i] & ( 1 << 0 )) << i;
        // PRINTBIN(byte);
        
    }
    return byte;
}

void set_embedding(unsigned char byte, Binary * bin){
    int i;
    for(i = 0; i < bin->size; i++){
        setlsbs(&bin->data[i], get_bit(i, byte));
    }
}

int main(int argc, char *argv[]){
    unsigned char byte0;

    print_args(argc, argv);
    ln(1); 
    
    if(argc <= 1){
        promptUserSeed();
    }else{
        /* Seed initialization */
        srand(atoi(argv[1]));
    }

    /* initialize binary */
    Binary bin;
    bin.size = DEFAULT_BYTES_SIZE;
    bin.data = malloc(bin.size*(sizeof(unsigned char)));

    /* initialized byte0 with random number */
    byte0 = randomNumber();
    ln(1);
    printf(MAG "BYTE-0: "); 
    PRINTBIN(byte0);
    printf(" -> \'%c\' ", byte0);
    printf(RESET);
    ln(1);

    /* initialized character array with random numbers*/
    init_bytes(&bin);

    print_binary(&bin);
    ln(1);

    printf(RED"\nEmbedded Array\n");
    set_embedding(byte0, &bin);
    print_binary(&bin);

    printf(RED"\nCharacter: [%c]\nBinary[", getlsbs(&bin));
    PRINTBIN(getlsbs(&bin));
    printf("]\n");
    printf(RESET);
    free(bin.data);
}
