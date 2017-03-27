/*
 * Fichier : koch_fonctions.h
 * Description : Trace de fractales geometriques - fonctions de calcul du flocon de koch
 */

#ifndef _KOCH_FONCTIONS_H_
#define _KOCH_FONCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <stdbool.h>

/* Liste chainee pour stocker les points de la fractale de Koch */
struct list {
    uint32_t x;
    uint32_t y;
    struct list *next;
};

/* Parametres du programme de calcul du flocon de Koch */
struct parameters {
    /* longueur en pixels d'un segment du triangle initial */
    uint32_t segment_length;

    /* taille en pixels d'un cote du carre englobant l'image finale */
    uint32_t image_size;

    /* nombre d'iterations du calcul la fractale de Koch */
    uint32_t nb_iterations;

    /* couleur du trace de la fractale */
    uint32_t fg_color;

    /* couleur du fond */
    uint32_t bg_color;

    /* true s'il faut generer toutes les images intermediaires du
       calcul de la fractale de Koch */
    bool all_images;

    /* nom du fichier image resultat */
    char *outfile;
};

/* Initialisation de la liste chainee koch correspondant au triangle
   de Koch initial */
extern void init_koch(struct list **koch, uint32_t size, uint32_t segment_length);

/* Initialisation de l'image avec la couleur de fond definie dans les
   parametres */
extern void init_picture(uint32_t **picture, uint32_t size, uint32_t bg_color);

/* Calcul de la fractale de Koch apres un nombre d'iterations donne ;
   generation de la liste chainee koch correspondante */
extern void generer_koch(struct list *koch, uint32_t nb_iterations);

/* Rendu image via algorithme bresehem - version generalisee
   simplifiee */
extern void render_image_bresenham(uint32_t *picture, struct list *koch,
        uint32_t size, uint32_t bg_color, uint32_t fg_color);

/* Liberation de la memoire allouee a la liste chainee */
extern void free_koch(struct list *koch);

/* Debug */
extern void afficher(struct list *l);

/* Test triangle initial*/
extern void test_init(void);

/* Calcul des coordonees des points du triangle pour l'iteration
 * Prend en parametre deux pointeurs vers les extremites du segment
 * Retourne un pointeur vers une liste chaine du nouveau triangle
 */
extern struct list *calcul_coordonnees(struct list *point1, struct list *point2);

/* Test des calculs des coordonées. */
extern void test_coordonnees(void);

/* Tracer la ligne avec la méthode de bresenham*/
extern void ligne_bresenham(uint32_t *picture, uint32_t fg_color, uint32_t size, struct list *a, struct list *b);

/* Test céation d'une diagonale. */
extern void test_diag(void);

/* Test triangle simple */
extern void test_triangle_simple(void);

/* Test sur une iteration. */
extern void test_iteration_simple(void);

#endif
