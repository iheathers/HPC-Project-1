#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_FISHES 10            // Number of fish in the simulation
#define NUM_SIMULATION_STEPS 100 // Number of simulation steps
#define MAX_COORDINATE 100       // Maximum coordinate value
#define MIN_COORDINATE -100      // Minimum coordinate value

// Define fish structure
typedef struct
{
    double x, y;   // Coordinates
    double weight; // Weight
} Fish;

// Function to calculate the objective function
double calculateObjectiveFunction(Fish fishes[], int numFishes)
{
    double sum = 0.0;
    for (int i = 0; i < numFishes; i++)
    {
        double distance = sqrt(fishes[i].x * fishes[i].x + fishes[i].y * fishes[i].y);
        sum += distance;
    }
    return sum;
}

// Function to simulate fish swimming
void swim(Fish *fish)
{
    fish->x += ((double)rand() / (double)RAND_MAX) * 0.2 - 0.1;
    fish->y += ((double)rand() / (double)RAND_MAX) * 0.2 - 0.1;
}

// Function to perform one simulation step
void simulationStep(Fish fishes[], int numFishes)
{
    for (int i = 0; i < numFishes; i++)
    {
        swim(&fishes[i]);
    }
}

// Function to calculate the barycentre of the fish school
void calculateBarycentre(Fish fishes[], int numFishes, double *barycentre)
{
    double sumWeightedDistance = 0.0;
    double sumDistance = 0.0;

    for (int i = 0; i < numFishes; i++)
    {
        double distance = sqrt(fishes[i].x * fishes[i].x + fishes[i].y * fishes[i].y);
        sumWeightedDistance += distance * fishes[i].weight;
        sumDistance += distance;
    }

    // Calculate the barycentre
    *barycentre = sumWeightedDistance / sumDistance;
}

int main()
{
    srand(time(NULL));

    // Initialize fish
    Fish fishes[NUM_FISHES];
    for (int i = 0; i < NUM_FISHES; i++)
    {
        fishes[i].x = (rand() / (double)RAND_MAX * (MAX_COORDINATE - MIN_COORDINATE) + MIN_COORDINATE);
        fishes[i].y = (rand() / (double)RAND_MAX * (MAX_COORDINATE - MIN_COORDINATE) + MIN_COORDINATE);
        // Assign random weights between 0.5 and 1.5
        fishes[i].weight = 0.5 + ((double)rand() / (double)RAND_MAX);
    }

    // Run the simulation
    clock_t startTime = clock();
    for (int step = 0; step < NUM_SIMULATION_STEPS; step++)
    {
        simulationStep(fishes, NUM_FISHES);
        double objective = calculateObjectiveFunction(fishes, NUM_FISHES);

        // Calculate the barycentre
        double barycentre;
        calculateBarycentre(fishes, NUM_FISHES, &barycentre);

        // Print the barycentre
        printf("Barycentre: %.2f\n", barycentre);

        // Update fish weights based on the objective function

        //
        // TODO 2: PRITAM - WRITE A FUCNTION TO CALCULATE WEIGHT OF FISH AT EACH SNAPSHOT
        // ...
    }
    clock_t endTime = clock();

    // Calculate and print elapsed time
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.4f seconds\n", elapsedTime);

    return 0;
}
