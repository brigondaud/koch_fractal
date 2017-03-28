/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include "koch_fonctions.h"
// TODO

void init_parameters(struct parameters *parameters, int argc, char *argv[])
{
    /* Initialisation des paramètres et mode interactif */
    if (argc >= 6) { /* Tous les paramètres avec ou sans all */

        /* segment_length et calcul image_size */
        segment_length = atoi(argv[1]);
        

        if (argc == 7) { /* all_images */

        }

    } else { /* Mode interactif */

    }
}

void show_koch_list(struct list *koch)
{
    // TODO
}

void show_parameters(const struct parameters *parameters)
{
    /* Affichage de controle des parametres */
    /* Composantes des couleurs */
        /* fg_color */
    uint8_t fr = parameters->fg_color>>16,
        fv = parameters->fg_color>>8,
        fb = parameters->fg_color;
    uint8_t br = parameters->bg_color>>16,
        bv = parameters->bg_color>>8,
        bb = parameters->bg_color;

    printf("-----------Parameters-----------\n");
    printf("Segment length: %u\n", parameters->segment_length);
    printf("Image Size: %u\n", parameters->image_size);
    printf("Iterations: %u\n", parameters->nb_iterations);
    printf("Foreground Color: %u(R), %u(V), %u(B)\n", fr, fv, fb);
    printf("Background Color: %u(R), %u(V), %u(B)\n", br, bv, bb);
    printf("All images: %u\n", parameters->all_images);
    printf("%s\n", parameters->outfile);
    printf("--------------------------------\n");
}
