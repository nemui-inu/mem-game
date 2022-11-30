#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(const char **data, size_t length)
{
    while (length > 1) {
        size_t n = rand() % (length--);
        const char *t = data[n];

        data[n] = data[length];
        data[length] = t;
    }
}

int main(void)
{
    const char *names[] = {
        "Malfeasance", "Portruding", "Jostled",
        "Gaelet", "Morpheus", "Star"
    };

    size_t len = sizeof names / sizeof *names;

    srand((unsigned) time(NULL));

    while (1) {
        shuffle(names, len);

        for (size_t i = 0; i < len; i++)
            printf("%s\n", names[i]);

        if (EOF == getchar())
            break;
    }
}