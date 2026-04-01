#include <stdio.h>

// Structure to represent each layer of the city
struct Layer {
    int type;
    int weight;
    int power;
};

// Structure to manage the city stack
struct CityStack {
    struct Layer layers[10];
    int top;
    int totalWeight;
    int totalPower;
};

// Function to add a layer (Push operation)
struct CityStack build(struct CityStack city) {
    int type, weight, powerChange = 0;

    printf("\n--- Build Menu ---\n");
    printf("Enter Type (1.Residential, 2.Industrial, 3.Power Plant): ");
    if (scanf("%d", &type) != 1) return city;

    printf("Enter Weight: ");
    if (scanf("%d", &weight) != 1) return city;

    // Constraint: First layer must be a Power Plant
    if (city.top == -1 && type != 3) {
        printf("Error: The first layer must be a Power Plant (Type 3).\n");
        return city;
    }

    // Constraint: Max weight limit
    if (city.totalWeight + weight > 800) {
        printf("Error: Total weight limit (800) exceeded.\n");
        return city;
    }

    // Power logic
    if (type == 3) powerChange = 100;
    else if (type == 1) powerChange = -20;
    else if (type == 2) powerChange = -50;
    else {
        printf("Error: Invalid building type.\n");
        return city;
    }

    // Constraint: Power cannot be negative
    if (city.totalPower + powerChange < 0) {
        printf("Error: Not enough power available!\n");
        return city;
    }

    // Stack Push
    city.top++;
    city.layers[city.top].type = type;
    city.layers[city.top].weight = weight;
    city.layers[city.top].power = powerChange;

    city.totalWeight += weight;
    city.totalPower += powerChange;

    printf("Success: Layer added successfully.\n");
    return city;
}

// Function to remove a layer (Pop operation)
struct CityStack demolish(struct CityStack city) {
    if (city.top == -1) {
        printf("Error: City is already empty!\n");
        return city;
    }

    city.totalWeight -= city.layers[city.top].weight;
    city.totalPower -= city.layers[city.top].power;
    city.top--;

    printf("Success: Top layer removed.\n");
    return city;
}

int main() {
    struct CityStack myCity;
    myCity.top = -1;
    myCity.totalWeight = 0;
    myCity.totalPower = 0;

    int choice;

    while (1) {
        printf("\n======= THE VERTICAL CITY =======\n");
        printf("1. Build Layer\n2. Demolish Layer\n3. Exit\n");
        printf("Current Status: Layers: %d | Weight: %d/800 | Power: %d\n",
                myCity.top + 1, myCity.totalWeight, myCity.totalPower);
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                myCity = build(myCity);
                break;
            case 2:
                myCity = demolish(myCity);
                break;
            case 3:
                printf("Exiting Simulation...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
