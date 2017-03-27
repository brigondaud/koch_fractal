/*
 * Fichier : koch_fonctions.c
 * Description : Trace de fractales geometriques - flocon de koch - generation des points et rendu des lignes
 */

#include "koch_fonctions.h"
#include "create_image.h"

/* Calcul des coordonees des points du triangle pour une iteration*/
struct list *calcul_coordonnees(struct list *a, struct list *e)
{
    /* Les pointeurs vers les nouveaux points */
    struct list *b = malloc(sizeof(struct list));
    struct list *c = malloc(sizeof(struct list));
    struct list *d = malloc(sizeof(struct list));

    /* Calcul des coordonnees */
    b->x = a->x + (uint32_t) ((int32_t)e->x -(int32_t)a->x)/3;
    b->y = a->y + (uint32_t) ((int32_t)e->y -(int32_t)a->y)/3;

    d->x = a->x + (uint32_t) floor(((float)2*((int32_t)e->x -(int32_t)a->x))/3);
    d->y = a->y + (uint32_t) floor(((float)2*((int32_t)e->y -(int32_t)a->y))/3);

    c->x = (uint32_t)((float)((b->x + d->x))/2 - (float)(((int32_t)d->y - (int32_t)b->y))*(sqrt(3)/2));
    c->y = (uint32_t)((float)((b->y + d->y))/2 + (float)(((int32_t)d->x - (int32_t)b->x))*(sqrt(3)/2));

    b->next = c;
    c->next = d;
    d->next = NULL;

    return b;
}

void test_coordonnees(void) {
    struct list *point1 = malloc(sizeof(struct list));
    struct list *point2= malloc(sizeof(struct list));
    struct list *point = malloc(sizeof(struct list));
    point1->next = NULL;
    point2->next= NULL;
    /* Segment horizontal. */
    point1->x = 0;
    point1->y = 0;
    point2->x = 10;
    point2->y = 0;

    point = calcul_coordonnees(point1, point2);
    afficher(point);
    free(point1);
    free(point2);
    free(point);
}

/* Initialisation de la liste chainee koch correspondant au triangle
   de Koch initial */
void init_koch(struct list **koch, uint32_t size, uint32_t segment_length)
{
    /* Creation des trois points initiaux */
    struct list *a = malloc(sizeof(struct list));
    struct list *b = malloc(sizeof(struct list));
    struct list *c = malloc(sizeof(struct list));

    a->y = (uint32_t)((float)(segment_length/2))*sqrt(3)/2;
    a->x = (uint32_t)((int32_t)size - (int32_t)segment_length) / 2;

    b->x = a->x + segment_length/2;
    b->y = (uint32_t)((int32_t)size-(int32_t)(((float)(segment_length/2))*sqrt(3)/2));

    c->x = (uint32_t)((int32_t)size-((int32_t)size-(int)segment_length)/2);
    c->y = a->y;

    a->next = b;
    b->next = c;
    c->next = NULL;

    *koch = a;
}

void afficher(struct list *l)
{
    struct list *courante = malloc(sizeof(struct list));
    courante = l;
    while (courante != NULL) {
        printf("(%u, %u)\n", courante->x, courante->y);
        courante = courante->next;
    }
    free(courante);
}

void test_init(void)
{
    struct list *t = malloc(sizeof(struct list));
    init_koch(&t, 100, 10);
    afficher(t);
}

/* Initialisation de l'image avec la couleur de fond definie dans les
   parametres */
void init_picture(uint32_t **picture, uint32_t size, uint32_t bg_color)
{
    *picture = malloc(size*size*sizeof(uint32_t));
    for (uint32_t i = 0, SIZE = size*size; i < SIZE; i++) {
        (*picture)[i] = bg_color;
    }
}

/* Calcul de la fractale de Koch apres un nombre d'iterations donne ;
   generation de la liste chainee koch correspondante */
void generer_koch(struct list *koch, uint32_t nb_iterations)
{
    // TODO
}

/* Rendu image via algorithme bresehem - version generalisee
   simplifiee */
void render_image_bresenham(uint32_t *picture, struct list *koch, uint32_t size, uint32_t bg_color, uint32_t fg_color)
{
    struct list *premiere, *precedente, *courante;
    /* On suppose que la liste passée en paramètre est forcément initalisée
     * donc possède au moins trois points
     */
     premiere = koch;
     precedente = premiere;
     courante = precedente->next;
     while (courante) {
         ligne_bresenham(picture, fg_color, size, precedente, courante);
         precedente = courante;
         courante = courante->next;
     }
    /* Il reste à tracer la ligne de la dernière à la premièr cellule*/
    ligne_bresenham(picture, fg_color, size, precedente, premiere);
}

void ligne_bresenham(uint32_t *picture, uint32_t fg_color, uint32_t size, struct list *a, struct list *b)
{
    /* Trace une ligne entre a et b */
    uint32_t x0, x1, y0, y1;
    x0 = a->x;
    y0 = a->y;
    x1 = b->x;
    y1 = b->y;
    int32_t dx = abs((int32_t)x1 - (int32_t)x0);
    int32_t dy = abs((int32_t)y1 - (int32_t)y0);
    int32_t sx, sy, err, e2;
    if (x0 < x1) {
        sx = 1;
    } else {
        sx = -1;
    }
    if (y0 < y1) {
        sy = 1;
    } else {
        sy = -1;
    }
    /* TODO: ternaires !*/
    err = (int32_t)dx - (int32_t)dy;
    while (true) {
        picture[y0*size + x0] = fg_color;
        if (x0 == x1 && y0 == y1) { break; }
        e2 = 2*err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void test_diag(void)
{
    /* Rendu et creation d'une image contenant une diagonale. */
    uint32_t *pic = NULL;
    struct list *diag = malloc(sizeof(struct list));
    struct list *diag_fin = malloc(sizeof(struct list));
    uint32_t size = 500;
    /* Liste diagonale. */
    diag->x = 0;
    diag->y = 0;
    diag->next = diag_fin;
    diag_fin->x = size;
    diag_fin->y = size;
    diag_fin->next = NULL;
    /* Rouge sur blanc. */
    uint32_t bg_color = 0xFFFFFF, fg_color = 0xFF0000;
    init_picture(&pic, size, bg_color);
    render_image_bresenham(pic, diag, size, bg_color, fg_color);
    create_image_ppm(pic, size, size, "diag.ppm");
    free(pic);
}

void test_triangle_simple(void)
{
    /* Rendu et creation d'une image contenant un triangle */
    uint32_t *pic = NULL;
    struct list *triangle = malloc(sizeof(struct list));
    uint32_t size = 500;
    uint32_t segment = 100;
    /* Init triangle */
    init_koch(&triangle, size, segment);
    /* Blanc sur noir. */
    uint32_t bg_color = 0xFFFFFF, fg_color = 0xFF0000;
    init_picture(&pic, size, bg_color);
    render_image_bresenham(pic, triangle, size, bg_color, fg_color);
    create_image_ppm(pic, size, size, "triangle.ppm");
    free(pic);
}

/* Liberation de la memoire allouee a la liste chainee */
void free_koch(struct list *koch)
{
    // TODO
}
