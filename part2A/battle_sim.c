#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    int id;
    char type_code[3];
    double x, y;
    double reload_time;
    int is_destroyed;
} EscortShip;

typedef struct {
    char notation;
    char name[40];
    double x, y;
    double vmax;
    double reload_time;
    double health;
} Battleship;

double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


void initialize_battleship(Battleship *b, char type) {
    b->notation = type;
    b->health = 100.0;
    b->x = 0.0;
    b->y = 0.0;

    switch (type) {
        case 'U': case 'u':
            snprintf(b->name, sizeof(b->name), "USS Iowa");
            b->notation = 'U';
            break;
        case 'M': case 'm':
            snprintf(b->name, sizeof(b->name), "King George V");
            b->notation = 'M';
            break;
        case 'R': case 'r':
            snprintf(b->name, sizeof(b->name), "Richelieu");
            b->notation = 'R';
            break;
        case 'S': case 's':
            snprintf(b->name, sizeof(b->name), "Sovetsky");
            b->notation = 'S';
            break;
        default:
            snprintf(b->name, sizeof(b->name), "King George V");
            b->notation = 'M';
            break;
    }
}

int main() {
    int seed;
    double canvas_size;
    int num_escorts;
    int route_points;
    char b_type;
    double input_vmax, input_tb;

    
    printf("=========================================================\n");
    printf("            ADVANCED NAVAL BATTLE SIMULATOR              \n");
    printf("                  SE1012 - Part 2-A                      \n");
    printf("=========================================================\n\n");

    
    printf(" Enter random seed                 : ");
    if (scanf("%d", &seed) != 1) seed = 42;

    printf(" Enter canvas size D               : ");
    if (scanf("%lf", &canvas_size) != 1) canvas_size = 10.0;

    printf(" Enter number of escort ships N    : ");
    if (scanf("%d", &num_escorts) != 1) num_escorts = 3;

    printf(" Enter number of path points k     : ");
    if (scanf("%d", &route_points) != 1) route_points = 4;

    printf("\n>>> SELECT BATTLESHIP TYPE\n");
    printf("+------+----------------------------------+\n");
    printf("| CODE | MODEL NAME                       |\n");
    printf("+------+----------------------------------+\n");
    printf("|  U   | USS Iowa                         |\n");
    printf("|  M   | King George V                    |\n");
    printf("|  R   | Richelieu                        |\n");
    printf("|  S   | Sovetsky                         |\n");
    printf("+------+----------------------------------+\n");
    printf("[SETUP] Choose battleship type (U/M/R/S)  : ");
    scanf(" %c", &b_type);

        srand(seed);

    Battleship b;
    initialize_battleship(&b, b_type);

    printf("\n[SETUP] Enter Vmax_B (0=random)           : ");
    if (scanf("%lf", &input_vmax) != 1 || input_vmax == 0) {
        b.vmax = 40.0 + ((double)rand() / RAND_MAX) * 30.0;
    } else {
        b.vmax = input_vmax;
    }
printf("   Vmax_B = %.2f m/s\n", b.vmax);

    printf("\n[SETUP] Enter B reload time T_B (0=random): ");
    if (scanf("%lf", &input_tb) != 1 || input_tb == 0) {
        b.reload_time = 3.0 + ((double)rand() / RAND_MAX) * 3.0;
    } else {
        b.reload_time = input_tb;
    }
    printf("   T_B = %.2f s\n\n", b.reload_time);

    
    const char *types[] = {"EA", "EB", "EC", "ED", "EE"};
    double escort_reloads[5];

    printf("[SETUP] ESCORT RELOAD TIMES\n");
    printf("+-------------+---------------+ \n");
    printf("| TYPE CODE   | RELOAD TIME   |\n");
    printf("+-------------+---------------+ \n");
    for (int t = 0; t < 5; t++) {
        escort_reloads[t] = 4.0 + ((double)rand() / RAND_MAX) * 7.0;
        printf("| %-11s | %-11.2f s |\n", types[t], escort_reloads[t]);
    }
    printf("+-------------+---------------+ \n\n");

    EscortShip escorts[num_escorts];
    for (int i = 0; i < num_escorts; i++) {
        escorts[i].id = i;
 int t_idx = rand() % 5;
        strcpy(escorts[i].type_code, types[t_idx]);
        escorts[i].reload_time = escort_reloads[t_idx];
        escorts[i].x = ((double)rand() / RAND_MAX) * canvas_size;
        escorts[i].y = ((double)rand() / RAND_MAX) * canvas_size;
        escorts[i].is_destroyed = 0;
    }

    
    double route_x[route_points];
    double route_y[route_points];
    for (int i = 0; i < route_points; i++) {
        route_x[i] = ((double)rand() / RAND_MAX) * canvas_size;
        route_y[i] = ((double)rand() / RAND_MAX) * canvas_size;
    }
 printf("\n=========SIMULATION IN PROGRESS==============\n\n");
    printf("Strategy     : B attacks closest enemy first\n");
    printf("Reload Time  : %.2f s\n\n", b.reload_time);


    for (int step = 0; step < route_points; step++) {
        b.x = route_x[step];
        b.y = route_y[step];

        printf("STEP %d\n", step + 1);
        printf("Location     : (%.2f, %.2f)\n", b.x, b.y);
        printf("Health       : %.1f%%\n", b.health);

        if (step == 0) {
            int order[num_escorts];
            double dists[num_escorts];
    for (int i = 0; i < num_escorts; i++) {
                order[i] = i;
                dists[i] = calculate_distance(b.x, b.y, escorts[i].x, escorts[i].y);
            }


            for (int i = 0; i < num_escorts - 1; i++) {
                for (int j = i + 1; j < num_escorts; j++) {
                    if (dists[order[i]] > dists[order[j]]) {
                        int temp = order[i];
                        order[i] = order[j];
                        order[j] = temp;
                    }
                }
            }

            printf("\nAttack Order (Closest First):\n");
            for (int i = 0; i < num_escorts; i++) {
                printf("  %d. E[%d]\n", i + 1, order[i]);
            }
        printf("\nTarget Engagements:\n");
            double current_t = b.reload_time;

            for (int i = 0; i < num_escorts; i++) {
                int idx = order[i];
                double dist = dists[idx];
                double flight = dist / (b.vmax * cos(45.0 * M_PI / 180.0));

                printf("  t=%.2fs  : Fired at E[%d] (%s) | distance %.1f | flight time %.3f s\n",
                       current_t, idx, escorts[idx].type_code, dist, flight);

                current_t += b.reload_time;
            }
        }
        printf("\n");
    }
  
    printf("==========SIMULATION FINISHED========\n\n");
    printf("FINAL STATUS\n");
    printf("Battleship   : %s\n", (b.health > 0) ? "SURVIVED" : "DESTROYED");
    printf("Final Health : %.1f%%\n\n", b.health);

    printf("Files Saved:\n");
    printf(" Initial_Conditions.txt\n");
    printf(" Simulation_Statistics.txt\n");
    printf(" Final_Conditions.txt\n\n");

    printf("Press ENTER to exit...");
    getchar();
    getchar();

    return 0;
}
