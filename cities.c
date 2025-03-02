#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

#define MAX_CITIES 11

typedef struct {
    float x;
    float y;
} City;

float distance(City a, City b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float calculate_path_length(City *cities, int *perm, int n) {
    float length = 0.0;
    for (int i = 0; i < n - 1; i++) {
        length += distance(cities[perm[i]], cities[perm[i + 1]]);
    }
    length += distance(cities[perm[n - 1]], cities[perm[0]]);  // Return to start
    return length;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *perm, int start, int n, City *cities, float *min_path, int *best_path) {
    if (start == n) {
        float path_length = calculate_path_length(cities, perm, n);
        if (path_length < *min_path) {
            *min_path = path_length;
            memcpy(best_path, perm, n * sizeof(int)); // Store best path
        }
        return;
    }
    for (int i = start; i < n; i++) {
        swap(&perm[start], &perm[i]);
        permute(perm, start + 1, n, cities, min_path, best_path);
        swap(&perm[start], &perm[i]);
    }
}

int main() {
    City cities[11];
    int n = 0;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1 && n < 11) {
        if (sscanf(line, "%f, %f", &cities[n].x, &cities[n].y) != 2) {
            fprintf(stderr, "Error reading coordinates.\n");
            free(line);
            return 1;
        }
        n++;
    }
    free(line);

    if (n < 2) {
        printf("0.00\n");
        return 0;
    }

    int perm[11];
    int best_path[11];  // Track shortest path
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }

    float min_path = FLT_MAX;
    permute(perm, 1, n, cities, &min_path, best_path);  // Fix start city

    printf("Shortest distance: %.2f\n", min_path);
    printf("Path: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_path[i]);
    }
    printf("%d\n", best_path[0]);  // Print return to start

    return 0;
}
