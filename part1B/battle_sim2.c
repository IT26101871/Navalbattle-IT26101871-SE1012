#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define PI 3.14159265358979323846
int main() {
    int seed, D, N, k, t, thetaMin;
    char shipType;
    float vmaxInput, calculated_vmax;
printf("+-----------------------------------------------------------------+\n");
    printf("|             ADVANCED NAVAL BATTLE SIMULATION 2                |\n");
    printf("+-----------------------------------------------------------------+\n\n");
printf("[SETUP] Enter random seed: ");
    if (scanf("%d", &seed) != 1) return 1;
    srand(seed);
printf("[SETUP] Enter canvas size D: ");
    scanf("%d", &D);

    printf("[SETUP] Enter number of escort ships N (1-100): ");
    scanf("%d", &N);

    printf("[SETUP] Enter number of path points k (2-20): ");
    scanf("%d", &k);
 printf("[SETUP] Gun jams after iteration t (1 to %d): ", k - 1);
    scanf("%d", &t);

    printf("[SETUP] Enter jammed gun min angle thetaMin (1-29 deg): ");
    scanf("%d", &thetaMin);

    printf("\nBattleship types:\n");
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
    scanf(" %c", &shipType);
 printf("[SETUP] Enter Vmax_B (0=random): ");
    scanf("%f", &vmaxInput);

if (vmaxInput == 0) {
        calculated_vmax = 100.0f + ((float)rand() / RAND_MAX) * 60.0f; 
    } else {
        calculated_vmax = vmaxInput;
    }
char shipName[30];
    shipType = toupper(shipType);
    if (shipType == 'M') strcpy(shipName, "M (King George V)");
    else if (shipType == 'R') strcpy(shipName, "R (Richelieu)");
    else if (shipType == 'S') strcpy(shipName, "S (Sovetsky)");
    else strcpy(shipName, "U (USS Iowa)");

 float path_x[20], path_y[20];
    for (int i = 0; i < k; i++) {
        path_x[i] = ((float)rand() / RAND_MAX) * D;
        path_y[i] = ((float)rand() / RAND_MAX) * D;
    }
printf("\n[SIMULATION PARAMETERS]\n");
    printf("+--------------------------+------------------------------------+\n");
    printf("| %-24s | %-34s |\n", "Parameter Name", "User Input / Value");
    printf("+--------------------------+------------------------------------+\n");
    printf("| %-24s | %-34d |\n", "Random Seed", seed);
    printf("| %-24s | %-34d |\n", "Canvas Dimension (D)", D);
    printf("| %-24s | %-34d |\n", "Escort Fleet Size (N)", N);
    printf("| %-24s | %-34d |\n", "Total Waypoints (k)", k);
    printf("| %-24s | %-34d |\n", "Gun Jam Iteration (t)", t);
    printf("| %-24s | %-28d deg |\n", "Min Jam Angle (thetaMin)", thetaMin);
    printf("| %-24s | %-34s |\n", "Battleship Model Code", shipName);
    char vmaxStr[40];
    sprintf(vmaxStr, "%.2f m/s", calculated_vmax);
    printf("| %-24s | %-34s |\n", "Calculated Vmax_B", vmaxStr);
    printf("+--------------------------+------------------------------------+\n\n");

 FILE *f_init = fopen("Initial_Conditions.txt", "w");
    if (f_init != NULL) {
        fprintf(f_init, "Seed: %d\nCanvas Size (D): %d\nEscort Fleet Size (N): %d\n", seed, D, N);
        fprintf(f_init, "Total Waypoints (k): %d\nGun Jam Iteration (t): %d\n", k, t);
        fprintf(f_init, "Min Jam Angle (thetaMin): %d deg\nBattleship: %s\nCalculated Vmax_B: %.2f m/s\n", thetaMin, shipName, calculated_vmax);
        fprintf(f_init, "\n--- AUTO-GENERATED WAYPOINTS ---\n");
    }

    


    printf("[WAYPOINT ROUTE GENERATION]\n");
    for (int i = 0; i < k; i++) {
        printf("  # Waypoint %02d : (%.2f, %.2f)\n", i + 1, path_x[i], path_y[i]);
        if (f_init != NULL) {
            fprintf(f_init, "  Waypoint %02d : (%.2f, %.2f)\n", i + 1, path_x[i], path_y[i]);
        }
    }
   if (f_init != NULL) fclose(f_init);
    printf("\n");

printf("[EVENT LOGS & OUTCOME]\n");

int sunk_step = -1;
int killer_escort = -1;

    FILE *f_stats = fopen("Simulation_Statistics.txt", "w");
    FILE *f_final = fopen("Final_Conditions.txt", "w");

   if (f_final != NULL) {
    fprintf(f_final, "Status: ELIMINATED\n");
    fprintf(f_final, "Final Step: %d\n", sunk_step);
    fprintf(f_final, "Eliminated By: Escort E[%d] (EA)\n", killer_escort);
    fprintf(f_final, "Sunk Location: (%.2f, %.2f)\n",
            path_x[sunk_step - 1], path_y[sunk_step - 1]);
    fclose(f_final);
}

    if (f_final != NULL) {
    fprintf(f_final, "Status: ELIMINATED\n");
    fprintf(f_final, "Final Step: %d\n", sunk_step);
    fprintf(f_final, "Eliminated By: Escort E[%d] (EA)\n", killer_escort);
    fprintf(f_final, "Sunk Location: (%.2f, %.2f)\n",
            path_x[sunk_step - 1], path_y[sunk_step - 1]);
    fclose(f_final);
}
for (int step = 1; step <= k; step++) {
        float bx = path_x[step - 1];
        float by = path_y[step - 1];

        char weapon_status[20];
        if (step <= t) {
            strcpy(weapon_status, "OPERATIONAL");
        } else {
            sprintf(weapon_status, "JAMMED (>=%d deg)", thetaMin);
        
        printf("  - Step %02d : Position (%.2f, %.2f) | Weapon Status: %s\n", step, bx, by, weapon_status);
}
        if (f_stats != NULL) {
            fprintf(f_stats, "Step %02d : Position (%.2f, %.2f) | Weapon Status: %s\n", step, bx, by, weapon_status);
        }

for (int e = 0; e < N; e++) {
            float escort_x = ((float)rand() / RAND_MAX) * D;
            float escort_y = ((float)rand() / RAND_MAX) * D;
            float dist = sqrtf(powf(bx - escort_x, 2) + powf(by - escort_y, 2));

            
            if (dist < (D * 0.45f) && sunk_step == -1) {
                sunk_step = step;
                killer_escort = e;
                break;
            }
        }

        if (sunk_step != -1) break;
if (sunk_step == -1) {
        sunk_step = (rand() % k) + 1;
        killer_escort = rand() % N;
    }
printf("\n  [!] OUTCOME: Battleship B ELIMINATED at Step %d by Escort E[%d] (EA)\n\n", sunk_step, killer_escort);

    if (f_stats != NULL) {
        fprintf(f_stats, "Outcome: Battleship B ELIMINATED at Step %d by Escort E[%d] (EA)\n", sunk_step, killer_escort);
        fclose(f_stats);
    }

    if (f_final != NULL) {
        fprintf(f_final, "Status: ELIMINATED\n");
        fprintf(f_final, "Final Step: %d\n", sunk_step);
        fprintf(f_final, "Eliminated By: Escort E[%d] (EA)\n", killer_escort);
        fprintf(f_final, "Sunk Location: (%.2f, %.2f)\n", path_x[sunk_step - 1], path_y[sunk_step - 1]);
        fclose(f_final);
    }
printf("[EXPORT STATUS]\n");
    printf("  ->  Initial_Conditions.txt\n");
    printf("  ->  Simulation_Statistics.txt\n");
    printf("  ->  Final_Conditions.txt\n\n");

    printf("Press ENTER to exit...");
    getchar();
    getchar();

    return 0;
   }
}
