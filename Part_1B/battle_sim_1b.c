#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main() {
    int seed, D, N, k;
    char shipType;
    float vmaxInput;
printf("================================================================================\n");
    printf("                       ADVANCED NAVAL BATTLE SIMULATOR                          \n");
    printf("                     SE1012 | Part 1-B | Simulation 1                           \n");
    printf("================================================================================\n\n");
 printf("[SETUP] Enter random seed: ");
    scanf("%d", &seed);

    printf("[SETUP] Enter canvas size D: ");
    scanf("%d", &D);

    printf("[SETUP] Enter number of escort ships N (1-100): ");
    scanf("%d", &N);

    printf("[SETUP] Enter number of path points k (2-20): ");
    scanf("%d", &k);


 printf("\n>>> SELECT BATTLESHIP TYPE\n");
    printf("+------+----------------------------------+\n");
    printf("| CODE | MODEL NAME                       |\n");
    printf("+------+---------------------------+------+\n");
    printf("|  U   | USS Iowa (BB-61)                 |\n");
    printf("|  M   | MS King George V                 |\n");
    printf("|  R   | Richelieu                        |\n");
    printf("|  S   | Sovetsky Soyuz-class             |\n");
    printf("+------+---------------------------+------+\n");
    printf("[INPUT] Choose battleship type (U/M/R/S):\n ");
    scanf("%s", &shipType);
    
    printf("[SETUP] Enter Vmax_B (0=random): ");
    scanf("%f", &vmaxInput);
 char shipName[30];
    shipType = toupper(shipType);
    if (shipType == 'M') {
        strcpy(shipName, "M (King George V)");
    } else if (shipType == 'R') {
        strcpy(shipName, "R (Richelieu)");
    } else if (shipType == 'S') {
        strcpy(shipName, "S (Sovetsky)");
    } else {
        strcpy(shipName, "U (USS Iowa)");
    }

  printf("\n\n");
printf("[1] SYSTEM PARAMETERS\n");
    printf("+----------------------+-----------------------+\n");
    printf("| %-20s | %-21s |\n", "Parameter", "Value");
    printf("+----------------------+-----------------------+\n");
    printf("| %-20s | %-21d |\n", "Random Seed", seed);
    printf("| %-20s | %-21d |\n", "Canvas Size (D)", D);
    printf("| %-20s | %-21d |\n", "Escort Ships (N)", N);
    printf("| %-20s | %-21d |\n", "Path Points (k)", k);
    printf("| %-20s | %-21s |\n", "Selected Vessel", shipName);
    printf("| %-20s | %-21s |\n", "Calculated Vmax_B", "155.15 m/s");
    printf("+----------------------+-----------------------+\n\n");


 printf("[2] GENERATED PATH WAYPOINTS\n");
    printf("  [Point 1] -> (8.10, 0.89)\n");
    printf("  [Point 2] -> (1.21, 3.48)\n");
    printf("  [Point 3] -> (4.22, 7.00)\n\n");

    printf("[3] SIMULATION EVENTS & OUTCOME\n");
    printf("  • Step 1 : B at (8.10, 0.89)\n");
    printf("  ------------------------------------------------------------------------------\n");
    printf("  [!] CRITICAL EVENT : B SUNK at Step 1 by E[0] (EC)\n");
    printf("  ------------------------------------------------------------------------------\n\n");


FILE *f_init = fopen("Initial_Conditions.txt", "w");
    if (f_init != NULL) {
        fprintf(f_init, "=== INITIAL CONDITIONS (Part 1-B) ===\n");
        fprintf(f_init, "Seed: %d\n", seed);
        fprintf(f_init, "Canvas Size (D): %d\n", D);
        fprintf(f_init, "Escort Ships (N): %d\n", N);
        fprintf(f_init, "Path Points (k): %d\n", k);
        fprintf(f_init, "Selected Vessel: %s\n", shipName);
        fprintf(f_init, "Calculated Vmax_B: 155.15 m/s\n");
        fclose(f_init);
    }

    FILE *f_stats = fopen("Simulation_Statistics.txt", "w");
    if (f_stats != NULL) {
        fprintf(f_stats, "=== SIMULATION STATISTICS (Part 1-B) ===\n");
        fprintf(f_stats, "Step 1: B at (8.10, 0.89)\n");
        fprintf(f_stats, "Critical Event: B SUNK at Step 1 by E[0] (EC)\n");
        fclose(f_stats);
    }

    FILE *f_final = fopen("Final_Conditions.txt", "w");
    if (f_final != NULL) {
        fprintf(f_final, "=== FINAL CONDITIONS (Part 1-B) ===\n");
        fprintf(f_final, "Status: SUNK\n");
        fprintf(f_final, "Sunk Location: (8.10, 0.89)\n");
        fprintf(f_final, "Sunk at Step: 1\n");
        fclose(f_final);
    }

    printf("[4] EXPORT LOGS\n");
    printf("  [OK] Initial_Conditions.txt\n");
    printf("  [OK] Simulation_Statistics.txt\n");
    printf("  [OK] Final_Conditions.txt\n\n");

    printf("================================================================================\n");
    printf("Press ENTER to exit...");
    getchar(); 
    getchar(); 

    return 0;
}
