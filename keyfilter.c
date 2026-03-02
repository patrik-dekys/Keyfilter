#include <stdio.h>
#include <string.h>

#define MAX_CITIES 1000 // Adjust as needed (maximum number of cities)
#define MAX_COMBINED_LENGTH 100000 // Combined string of cities with match [should be: MAX_CITIES * (MAX_LINE_LENGTH-1)]
#define MAX_LINE_LENGTH 101 // Maximum line length = maximum city name length

int main(int argc, char *argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc > 2) {
        fprintf(stderr, "Unexpected input!\nExample of input: ./keyfilter (letters/space) <adresy.txt\n");
        return 1;
    }

    // Store the destination variable from the command line
    char *destination;

    if (argc == 1) {
        destination = "";
    } else {
        destination = argv[1];
    }

    // Convert destination to uppercase
    for (int i = 0; destination[i]; i++) {
        if (destination[i] >= 'a' && destination[i] <= 'z') {
            destination[i] += 'A' - 'a';
        }
    }

    // Initialize an array to store city names
    char cities[MAX_CITIES][MAX_LINE_LENGTH];
    int cityCount = 0;

    char buffer[MAX_LINE_LENGTH];

    // Read city names from standard input and store them in the array
    while (cityCount < MAX_CITIES && fgets(buffer, sizeof(buffer), stdin)) {
        // Remove the newline character at the end of each city name
        buffer[strcspn(buffer, "\n")] = '\0';

        // Convert city name to uppercase
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                buffer[i] += 'A' - 'a';
            }
        }

        // Copy the city name to the cities array
        strncpy(cities[cityCount], buffer, sizeof(cities[0]) - 1);
        cityCount++;
    }

    // Initialize an array to store matching cities with destination
    char founded[MAX_CITIES][MAX_LINE_LENGTH];
    int foundedCount = 0;

    // Determine the length of the destination variable
    int destinationLength = (int)strlen(destination);

    // Find cities that match the destination based on its length
    for (int i = 0; i < cityCount; i++) {
        char original[MAX_LINE_LENGTH];
        strcpy(original, cities[i]);
        char substring[MAX_LINE_LENGTH];
        int startIndex = 0;

        // Extract a substring from the city name
        for (int j = 0; j < destinationLength; j++) {
            substring[j] = original[startIndex + j];
        }
        substring[destinationLength] = '\0';

        // If the substring matches the destination, store it in the founded array
        if (strcmp(substring, destination) == 0) {
            strncpy(founded[foundedCount], cities[i], sizeof(founded[0]) - 1);
            foundedCount++;
        }
    }

    // Create a combined string to store extracted characters (used for printing enabled characters)
    char combinedString[MAX_COMBINED_LENGTH] = "";

    // Extract characters from founded cities at the destination length position
    for (int i = 0; i < foundedCount; i++) {
        // Check if the founded city name is long enough to extract a character at destinationLength
        if ((int)strlen(founded[i]) > destinationLength) {
            char extractedChar = founded[i][destinationLength];
            // Append the extracted character to the combinedString
            combinedString[strlen(combinedString)] = extractedChar;
            combinedString[strlen(combinedString) + 1] = '\0'; // Null-terminate the string
        }
    }

    // Initialize an array to store allowed characters
    char allowed[MAX_CITIES][MAX_LINE_LENGTH];
    int allowedCount = 0;

    // Iterate through characters from ' ' to '~'
    for (int i = ' '; i <= '~'; i++) {
        char letter = (char)i; // Set the current letter

        // Check if the letter is in the combinedString
        int found = 0;
        for (int j = 0; j <= (int)strlen(combinedString); j++) {
            if (letter == combinedString[j]) {
                found = 1;
                break;
            }
        }

        // If the letter is found, store it in the allowed array and increment allowedCount
        if (found) {
            allowed[allowedCount][0] = letter;
            allowed[allowedCount][1] = '\0'; // Null-terminate the string
            allowedCount++;
        }
    }

    // Print the results
    if (foundedCount > 0) {
        if (foundedCount == 1) {
            printf("Found: %s\n", founded[0]);
        } else {
            printf("Enable: ");
            for (int i = 0; i < allowedCount; i++) {
                printf("%s", allowed[i]);
            }
            printf("\n");
        }
    } else {
        printf("Not found\n");
    }

    return 0;
}
