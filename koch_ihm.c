/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include "koch_fonctions.h"
// TODO

void init_parameters(struct parameters *parameters, int argc, char *argv[])
{
    /* Initialisation des paramètres et mode interactif */
    if (argc == 6 | argc == 7) { /* Tous les paramètres avec ou sans all */

        parameters->segment_length = atoi(argv[1]);
        /* Calcul de image_size */
        parameters->image_size = 5*(parameters->segment_length/3);

        parameters->nb_iterations = atoi(argv[2]);
        parameters->fg_color = strtol(argv[3], NULL, 16);
        parameters->bg_color = strtol(argv[4], NULL, 16);

        /* Nom du fichier de sorti */
        parameters->outfile = calloc(255, sizeof(char));
        sprintf(parameters->outfile, "%s", argv[5]);

        parameters->all_images = false;

        if (argc == 7 && argv[6][0] == 'a' && argv[6][1] == 'l' && argv[6][2] == 'l') { /* all_images */
            parameters->all_images = true;
        }

    } else { /* Mode interactif */

        /* TODO: vider le buffer d'entrée si entrée trop longue */
        char input[255];

        /* Segment length */
        printf("segment length: \n");
        fgets(input, 255, stdin);
        parameters->segment_length = atoi(input);

        /* Calcul de image_size */
        parameters->image_size = 5*(parameters->segment_length/3);

        /* Iterations */
        printf("Iterations: \n");
        fgets(input, 255, stdin);
        parameters->nb_iterations = atoi(input);

        /* Iterations */
        printf("Foreground color: \n");
        fgets(input, 255, stdin);
        parameters->fg_color = strtol(input, NULL, 16);

        /* Iterations */
        printf("Background color: \n");
        fgets(input, 255, stdin);
        parameters->bg_color = strtol(input, NULL, 16);

        /* Iterations */
        printf("Outfile: \n");
        parameters->outfile = calloc(255, sizeof(char));
        fgets(parameters->outfile, 255, stdin);

        /* Iterations */
        printf("All images ? (0/1) \n");
        fgets(input, 255, stdin);
        parameters->all_images = (bool) atoi(input);

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

    printf("\n-----------Parameters-----------\n");
    printf("Segment length: %u\n", parameters->segment_length);
    printf("Image Size: %u\n", parameters->image_size);
    printf("Iterations: %u\n", parameters->nb_iterations);
    printf("Foreground Color: %u(R), %u(V), %u(B)\n", fr, fv, fb);
    printf("Background Color: %u(R), %u(V), %u(B)\n", br, bv, bb);
    printf("All images: %u\n", parameters->all_images);
    printf("Outfile: %s\n", parameters->outfile);
    printf("--------------------------------\n");
}

void test_params(int argc, char *argv[])
{
    struct parameters *params = malloc(sizeof(struct parameters));
    init_parameters(params, argc, argv);
    show_parameters(params);
    free(params);
}
