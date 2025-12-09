#include "../cub.h"

// sur str :"F_-_-23, 49, 612   " -> recoit "-_-23, 49, 612   "
// strtrim sur tous les espaces, puis split sur ,
// verifier que 3 chaines si oui trim chacune dentre elles des spaces
// verifier que chaque chaine is_number + 0-255
// si tj ok, enregistrer les 9 chiffres collés dans un int ? ou plutot une sous struct ?

void free_split (char **tab)
{
    int i = 0;
    while(tab[i])
    {
        if(tab[i])
            free(tab[i]);
        i++;
    }
    free(tab);
}

int parse_color(char *line, int *color)
{
    char    *trimmed;
    char    **parts;
    char    *comp;
    int     rgb[3];
    int     i;
    int     j;
    int     value;

    if (*color != -1)
        return (print_error("Error\nDuplicate color identifier\n"), 0);

    // 1) on enlève espaces / \n autour de la partie "23, 49, 612   "
    trimmed = ft_strtrim(line, " \t\n\v\f\r");
    if (!trimmed)
        return (print_error("Error\nMalloc failed\n"), 0);
    if (trimmed[0] == '\0')
    {
        free(trimmed);
        return (print_error("Error\nMissing color values\n"), 0);
    }

    // 2) split sur la virgule
    parts = ft_split(trimmed, ',');
    free(trimmed);
    if (!parts)
        return (print_error("Error\nMalloc failed\n"), 0);

    // 3) vérifier qu’on a exactement 3 morceaux
    i = 0;
    while (parts[i])
        i++;
    if (i != 3)
    {
        free_split(parts);
        return (print_error("Error\nInvalid color format\n"), 0);
    }

    // 4) pour chaque composante : trim, check digits, atoi, check 0–255
    i = 0;
    while (i < 3)
    {
        comp = ft_strtrim(parts[i], " \t\n\v\f\r");
        if (!comp)
        {
            free_split(parts);
            return (print_error("Error\nMalloc failed\n"), 0);
        }
        if (comp[0] == '\0')
        {
            free(comp);
            free_split(parts);
            return (print_error("Error\nInvalid color component\n"), 0);
        }

        // tous les chars doivent être des chiffres
        j = 0;
        while (comp[j])
        {
            if (!ft_isdigit((unsigned char)comp[j]))
            {
                free(comp);
                free_split(parts);
                return (print_error("Error\nColor component must be a number\n"), 0);
            }
            j++;
        }

        value = ft_atoi(comp);
        free(comp);
        if (value < 0 || value > 255)
        {
            free_split(parts);
            return (print_error("Error\nColor component out of range [0,255]\n"), 0);
        }
        rgb[i] = value;
        i++;
    }

    free_split(parts);

    // 5) pack R,G,B dans un int 0xRRGGBB
    *color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    return (1);
}
