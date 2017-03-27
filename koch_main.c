/*
 * Fichier : koch_main.c
 * Description : Trace de fractales geometriques - flocon de koch - programme principal
 */

#include <stdlib.h>
#include "koch_fonctions.h"
#include "koch_ihm.h"
#include "create_image.h"

int main(int argc, char **argv)
{
    // TODO
    /* Test de la fonction de calcul de coordonées. */
    // test_coordonnees();
    // test_init();
    // test_image();
    // test_diag();
    // test_triangle_simple();
    test_iteration_simple();


    return EXIT_SUCCESS;
}
