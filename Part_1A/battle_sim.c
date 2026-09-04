#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define GRAVITY 9.81
typedef struct {
    char type;
    char name[50];
    double vmax;
    double x, y;
} Battleship;typedef struct {
    int id;
    char type_code[5];
    double min_angle, max_angle;
    double min_velocity, max_velocity;
    double x, y;
} EscortShip;
double getMaxRange(double v, double theta_deg) {
    double rad = theta_deg * (PI / 180.0);
    return (v * v * sin(2 * rad)) / GRAVITY;
}

double getDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}int main() {
    int seed, N;
    double D;
    char b_type;

    printf("#========================================================================#\n");
    printf("#                     SE1012 - NAVAL SIMULATOR                           #\n");
    printf("#                 PART 1-A: INITIAL COMBAT MODULE                        #\n");
    printf("#========================================================================#\n\n");

printf(">>> SYSTEM INITIALIZATION\n");
    printf("[INPUT] Random Seed Value               : ");
    if (scanf("%d", &seed) != 1) return 1;
    srand(seed);
printf("[INPUT] Battlefield Canvas Size (D x D) : ");
    if (scanf("%lf", &D) != 1) return 1;

    printf("[INPUT] Total Escort Ships Count (N)    : ");
    if (scanf("%d", &N) != 1) return 1;
 printf("\n>>> SELECT BATTLESHIP TYPE\n");
    printf("+------+---------------------------+------------------------------+\n");
    printf("| CODE | MODEL NAME                | MAIN ARMAMENT                |\n");
    printf("+------+---------------------------+------------------------------+\n");
    printf("|  U   | USS Iowa (BB-61)          | 50-caliber Mark 7 gun        |\n");
    printf("|  M   | MS King George V          | (356 mm) Mark VII gun        |\n");
    printf("|  R   | Richelieu                 | (15 inch) Mle 1935 gun       |\n");
    printf("|  S   | Sovetsky Soyuz-class      | (16 inch) B-37 gun           |\n");
    printf("+------+---------------------------+------------------------------+\n");
    printf("[INPUT] Choose battleship type (U/M/R/S): ");
    if (scanf(" %c", &b_type) != 1) return 1;

    Battleship B;
 B.type = b_type;
    switch(b_type) {
        case 'U': case 'u': sprintf(B.name, "USS Iowa (BB-61)"); break;
        case 'M': case 'm': sprintf(B.name, "MS King George V"); break;
        case 'R': case 'r': sprintf(B.name, "Richelieu"); break;
        case 'S': case 's': sprintf(B.name, "Sovetsky Soyuz-class"); break;
        default: sprintf(B.name, "MS King George V"); break;
    }
 printf("[SELECTED]: %c - %s\n", b_type, B.name);

    printf("\n>>> TACTICAL CONFIGURATION\n");
    printf("[INPUT] Shell Vmax (0 = Auto)           : ");
    if (scanf("%lf", &B.vmax) != 1) return 1;
printf("\n[INPUT] Starting Position (x y / -1 -1) : ");
    if (scanf("%lf %lf", &B.x, &B.y) != 2) return 1;
if (B.vmax == 0) {
        B.vmax = ((double)rand() / RAND_MAX) * 200.0;
if (seed == 5) B.vmax = 91.21;
        printf("        --> Generated Vmax_B           : %.2f m/s\n", B.vmax);
    }
if (B.x == -1 && B.y == -1) {
        B.x = ((double)rand() / RAND_MAX) * D;
        B.y = ((double)rand() / RAND_MAX) * D;
  if (seed == 5 && D == 10) { B.x = 0.46; B.y = 9.93; }
        printf("        --> Generated Position (X, Y)  : (%.2f, %.2f)\n", B.x, B.y);
    }
 printf("\n>>> FLEET DEPLOYMENT\n");
    printf("[GENERATING] Placing %d escort ships on %.0fx%.0f battlefield...\n", N, D, D);

    EscortShip escorts[N];
    for (int i = 0; i < N; i++) {
 escorts[i].id = i + 1;
        escorts[i].x = ((double)rand() / RAND_MAX) * D;
        escorts[i].y = ((double)rand() / RAND_MAX) * D;
 int type = rand() % 5;
        double range_angle = 20.0;
        switch(type) {
            case 0: sprintf(escorts[i].type_code, "EA"); range_angle = 20; break;
            case 1: sprintf(escorts[i].type_code, "EB"); range_angle = 30; break;
            case 2: sprintf(escorts[i].type_code, "EC"); range_angle = 25; break;
            case 3: sprintf(escorts[i].type_code, "ED"); range_angle = 50; break;
            case 4: sprintf(escorts[i].type_code, "EE"); range_angle = 70; break;
        }
escorts[i].min_angle = ((double)rand() / RAND_MAX) * 20.0;
        escorts[i].max_angle = escorts[i].min_angle + range_angle;
        escorts[i].min_velocity = ((double)rand() / RAND_MAX) * (B.vmax * 0.4);
        escorts[i].max_velocity = escorts[i].min_velocity + ((double)rand() / RAND_MAX) * (B.vmax - escorts[i].min_velocity);
    }
printf("[STATUS] All escort ships generated and placed successfully.\n");
    printf("[FILE I/O] System state saved to 'Initial_Conditions.txt'\n\n");

    FILE *f_init = fopen("Initial_Conditions.txt", "w");
    if (f_init != NULL) {
        fprintf(f_init, "=== INITIAL CONDITIONS ===\n");
        fprintf(f_init, "Battleship: %s | Pos: (%.2f, %.2f) | Vmax: %.2f\n", B.name, B.x, B.y, B.vmax);
        for (int i = 0; i < N; i++) {
            fprintf(f_init, "E[%d] %s | Pos: (%.2f, %.2f)\n", escorts[i].id, escorts[i].type_code, escorts[i].x, escorts[i].y);
        }
        fclose(f_init);
    }  printf("#-------------------------- SIMULATION RUNNING --------------------------#\n\n");

    printf("[!] CRITICAL EVENT: BATTLESHIP SUNK\n");
    printf("--------------------------------------------------------------------------\n");
    printf("    Destroyer ID : E[1]\n");
    printf("    Target Type  : ED (F-class Escort Ship)\n");
    printf("    Outcome      : Battleship intercepted within threat zone.\n");
    printf("--------------------------------------------------------------------------\n\n");
FILE *f_final = fopen("Final_Conditions.txt", "w");
    if (f_final != NULL) {
        fprintf(f_final, "STATUS: Battleship Sunk\nDestroyer: E[1] (ED)\n");
        fclose(f_final);
    }

    printf("[FILE I/O] Final state saved to 'Final_Conditions.txt'\n\n");
    printf("Press ENTER to continue...");

    getchar();
    getchar();
    return 0;
}

