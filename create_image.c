/*
 * Fichier : create_image.c
 * Description : Creation d'un fichier ppm a partir d'une image sous la forme
 *               d'un tableau uint32_t *
 */
#include "create_image.h"

void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename)
{
    FILE *image = NULL;
    /* TODO: test de l'existence du fichier. */
    image = fopen(filename, "r");
    if (image) { /* Si l'image existe déjà. */
        printf("Le fichier existe déjà\n", stderr);
        fclose(image);
        exit(1);
    } else {
        image = fopen(filename, "w");

        /* Ecriture de l'en-tête.*/
        write_header(pic, image, size_x, size_y);

        /* Ecriture en binaire de l'image. */
        write_picture(pic, image, size_x, size_y);

        /* Fermeture du fichier. */
        fclose(image);
    }
}

void write_header(uint32_t *pic, FILE *fichier, int32_t size_x, int32_t size_y)
{
    /* La taille de l'image a insérer. */
    char csize_x[5] = "";
    char csize_y[5] = "";
    sprintf(csize_x, "%d ", size_x);
    sprintf(csize_y, "%d\n", size_y);

    /* Ecriture de l'en-tête du fichier. */
    fputs("P6\n", fichier);
    fputs(csize_x, fichier);
    fputs(csize_y, fichier);
    fputs("255\n", fichier);
}

void write_picture(uint32_t *pic, FILE *fichier, int32_t size_x, int32_t size_y) {

    /* Le pointeur vers le fichier est supposé non NULL. */
    for (uint32_t i = 0, ind_max = size_x*size_y; i < ind_max; i++) {
        /* Il n'y a que 24 bits qui contiennent l'information des couleurs. */
        /* Les valeurs des trois composantes : R, V, B. */
        uint8_t R = 0, V = 0, B = 0;

        /* Format des couleurs : 0x00RRVVBB. */
        R = pic[i]>>16;
        V = pic[i]>>8;
        B = pic[i];

        /* Ecriture des couleurs dans le fichier (1 élément de 1 octet). */
        fwrite(&R, 1, 1, fichier);
        fwrite(&V, 1, 1, fichier);
        fwrite(&B, 1, 1, fichier);
    }
}

void test_image(void)
{
    uint32_t *tabp = calloc(500*500, 4);
    int32_t x = 500;
    char *name = "test.ppm";
    /* Creation d'une image unie. */
    for (uint32_t i = 0, ind_max = 500*500; i < ind_max; i++) {
        tabp[i] = 16711680; /* rouge. */
    }
    create_image_ppm(tabp, x, x, name);
}
