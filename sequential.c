// AUTHOR: PRITAM STUDENT NUMBER: 23771397
// RASPREET

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LAKE_X_MIN -100.0 // Minimum x coordinate of the lake
#define LAKE_X_MAX 100.0  // Maximum x coordinate of the lake
#define LAKE_Y_MIN -100.0 // Minimum y coordinate of the lake
#define LAKE_Y_MAX 100.0  // Maximum y coordinate of the lake

#define MIN_SWIM_DISTANCE -0.1 // Minimum distance a fish can swim in one step
#define MAX_SWIM_DISTANCE 0.1  // Maximum distance a fish can swim in one step

#define NUM_FISHES 10
#define NUM_SIMULATION_STEPS 10 // Number of simulation steps

#define MAX_FISH_WEIGHT 2.0 // Maximum weight of a fish
#define MIN_FISH_WEIGHT 1.0 // Minimum weight of a fish

// FIXME: FISHES WEIGHT ARE COMING NEGATIVE. TIME TO DEBUG
// WRITE THE FUNCTION SIGNATURE ABOVE AND IMPLEMENT IT BELOW

void calculateBarycenter(Fish fishes[], int numFishes);

double square(double num) { return num * num; }

// Define fish structure and use it as alias
typedef struct {
  double x, y; // Coordinates of a fish
  double distanceTraveled;
  double weight; // Weight of a fish
} Fish;

bool isFishOutsideLake(Fish *fish) {
  return (fish->x < LAKE_X_MIN || fish->x > LAKE_X_MAX ||
          fish->y < LAKE_Y_MIN || fish->y > LAKE_Y_MAX);
}

double getRandomNumberInRange(double minValue, double maxValue) {
  // Generate a random double between 0 and 1
  double randomDouble = ((double)rand() / RAND_MAX);

  // Scale and shift the random double to the specified range
  double randomNumber = randomDouble * (maxValue - minValue) + minValue;

  return randomNumber;
}

double getRandomCoordinateInRange(double minValue, double maxValue) {
  return getRandomNumberInRange(minValue, maxValue);
}

double calculateDistanceFromOrigin(double x, double y) {
  return sqrt(square(x) + square(y));
}

// Function to calculate the objective function
double calculateObjectiveFunction(Fish fishes[], int numFishes) {
  double sum = 0.0;

  for (int i = 0; i < numFishes; i++) {
    // sqrt(x^2 + y^2)
    sum += calculateDistanceFromOrigin(fishes[i].x, fishes[i].y);
  }
  return sum;
}

// Function to simulate fish swimming
void swim(Fish *fish) {
  if (!isFishOutsideLake(fish)) {
    fish->x += getRandomNumberInRange(MIN_SWIM_DISTANCE, MAX_SWIM_DISTANCE);
    fish->y += getRandomNumberInRange(MIN_SWIM_DISTANCE, MAX_SWIM_DISTANCE);
  }
}

void updateWeight(Fish *fish, double maxDistanceTraveledInFishSchool) {
  double weightChange =
      fish->distanceTraveled / maxDistanceTraveledInFishSchool;

  // CAP IT AT 0 OR 1?
  if (fish->weight + weightChange < MIN_FISH_WEIGHT) {
    fish->weight = MIN_FISH_WEIGHT; // Cap the weight at 1.0
    return;
  }

  if (fish->weight + weightChange > MAX_FISH_WEIGHT) {
    fish->weight = MAX_FISH_WEIGHT; // Cap the weight at 2.0
    return;
  }

  fish->weight += weightChange;
}

// Function to perform one simulation step
void simulationStep(Fish fishes[], int numFishes) {

  double maxDistanceTraveledInFishSchool = 0.0;

  for (int i = 0; i < numFishes; i++) {
    double prevDistance = calculateDistanceFromOrigin(fishes[i].x, fishes[i].y);

    swim(&fishes[i]);

    double nextDistance = calculateDistanceFromOrigin(fishes[i].x, fishes[i].y);

    fishes[i].distanceTraveled = nextDistance - prevDistance;

    if (fishes[i].distanceTraveled > maxDistanceTraveledInFishSchool) {
      maxDistanceTraveledInFishSchool = fishes[i].distanceTraveled;
    }

    printf("Fish %d: x = %.2f, y = %.2f, weight = %.2f\n", i, fishes[i].x,
           fishes[i].y, fishes[i].weight);
  }

  for (int i = 0; i < numFishes; i++) {

    updateWeight(&fishes[i], maxDistanceTraveledInFishSchool);
  }
}

void calculateBarycenter(Fish fishes[], int numFishes) {
  double weightSum = 0.0;
  double distanceSum = 0.0;

  for (int i = 0; i < numFishes; i++) {
    weightSum += fishes[i].weight *
                 calculateDistanceFromOrigin(fishes[i].x, fishes[i].y);
    distanceSum += calculateDistanceFromOrigin(fishes[i].x, fishes[i].y);
  }

  // Check if distanceSum is non-zero to prevent division by zero
  if (distanceSum < 0.0) {
    printf("Distance sum is zero. Cannot calculate barycenter.\n");

    return;
  }

  // MAYBE CALCULATE THE COORDINATE JUST FOR EXPERIMENT

  // YOU CAN ALSO PRINT MEMORY ADDRESS TO SEE IF IT'S CONTINUOUS/ ADD THAT IN
  // REPORT

  // &FISH[I]

  double barycenter = weightSum / distanceSum;

  printf("Barycenter: %.2f\n", barycenter);
}

// NOTE: CONSIDER BOUNDARY CONDITION WHERE FISH SHOULD NOT GO OUT OF BOUNDARY
// NOTE: CONSIDER WEIGHT AS IT CANNOT GO OVER 2W
// SWIM RANDOM NUMBER IS -0.1-0.1 HAS BEEN UPDATED IN THE NEW PROJECT
// INSTRUCTIONS

int main() {
  // Seed the random number generator with the current time
  srand(time(NULL));

  // Initialize fish. NOTE; WE HAVE TO USE HEAP INSTEAD OF STACK AS IN
  // INSTRUCTIONS SO HAVE TO CHANGE THIS A BIT Fish fishes[NUM_FISHES];

  Fish *fishes; // Declare a pointer to the structure Fish

  // Allocate memory for 1,000,000 fish structures
  fishes = (Fish *)malloc(NUM_FISHES * sizeof(Fish));

  if (fishes == NULL) {
    fprintf(stderr, "Memory allocation failed. Exiting...\n");
    return 1; // Return a non-zero exit code to indicate an error
  }

  // TODO: MAKE IT MORE BETTER MAYBE : get number of length of fished array
  // using sizeof

  for (int i = 0; i < NUM_FISHES; i++) {
    // THIS RANGE CAN BE SPECIFIED IN DEFINE AS A VARIABLE/
    // MAKE SURE IT IS RIGHT OR NOT AS THE WAY OF ACCESSING THE VARIABLE MIGHT
    // BE DIFFERENT
    fishes[i].x = getRandomCoordinateInRange(-100, 100);
    fishes[i].y = getRandomCoordinateInRange(-100, 100);
    fishes[i].distanceTraveled = 0.0;
    fishes[i].weight = 1.0; // You can set the initial weight here 'w'

    // MAKE SURE WHICH PROCESS IS RIGHT
    // fishes->x=1;
    // fishes->y=1;
    // (fishes+1)->x=2;
    // (fishes+1)->y=2;

    printf("Fish %d: x = %.2f, y = %.2f, weight = %.2f\n", i, fishes[i].x,
           fishes[i].y, fishes[i].weight);
  }

  // Run the simulation
  clock_t startTime = clock();
  for (int step = 0; step < NUM_SIMULATION_STEPS; step++) {

    simulationStep(fishes, NUM_FISHES);

    calculateBarycenter(fishes, NUM_FISHES);
  }
  clock_t endTime = clock();

  // Calculate and print elapsed time
  double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
  printf("Elapsed time: %.4f seconds\n", elapsedTime);

  // Don't forget to free the allocated memory when done
  free(fishes);

  return 0;
}
