// // #include <objects.h>
// #include <stdio.h>
// #include <locale.h>
// #define SIZE 10

// matrix_field {
//         matrx[SIZE*2][SIZE];
// }

// typedef struct
// {
//     char field[SIZE][SIZE * 2];
// } tetramino_t;

// tetramino_t get_tetramino() {
//     tetramino_t tetramino1;
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE * 3; j ++) {
//         printf("%c%c%c", tetr.field[i][j], tetr.field[i
//                 printf("%c", tetr.field[i][j]);
//         }
//     return tetramino1;
// }

// void print_tetramino(tetramino_t tetr) {
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE * 3; j += 3) { // Шаг 3, чтобы пропустить три байта на каждый символ
//             printf("%c%c%c", tetr.field[i][j], tetr.field[i
//                         printf("%c", tetr.field[i][j]);
//                 }
//         printf("\n");
//         }
// }

// int main() {
//         setlocale(LC_CTYPE, "");
//         tetramino_t tetr = get_tetramino();
//         print_tetramino(tetr);
//         return 0;     
// }