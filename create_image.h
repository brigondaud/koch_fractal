#ifndef _CREATE_IMAGE_H_
#define _CREATE_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

extern void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename);

/* Ecirute de l'en tete du fichier PPM. */
extern void write_header(uint32_t *pic, FILE *fichier, int32_t size_x, int32_t size_y);

/* Ecriture en binaire de l'image. */
extern void write_picture(uint32_t *pic, FILE *fichier, int32_t size_x, int32_t size_y);

/* Fonction de test image. */
extern void test_image(void);
#endif
