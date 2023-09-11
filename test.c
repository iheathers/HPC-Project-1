#include <stdio.h>
#include <stdlib.h>

#define NUM_FISHES 10

typedef struct {
  double x, y;             // Coordinates of a fish
  double distanceTraveled; // Distance traveled by a fish in one step
  double weight;           // Weight of a fish
} Fish;

int fishes[10]

    // fishes[0]

    void
    simulationStep(Fish *fishes, int numFishes) {

  for (int i = 0; i < numFishes; i++) {
    printf("Fish %d: x = %.2f, y = %.2f, weight = %.2f\n", i, (fishes[i]).x,
           (fishes + i)->y, (fishes + i)->weight);
  }
};

int main() {

  Fish *fishes; // Declare a pointer to the structure Fish

  // Allocate memory for 1,000,000 fish structures
  fishes = (Fish *)malloc(NUM_FISHES * sizeof(Fish));

  printf("in main %p\n", fishes);

  simulationStep(fishes[], NUM_FISHES);

  return 0;
}
