#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GRAVITY 9.81
typedef struct {
    int id;
    char type_code[3];    
    char type_name[30];
    double x, y;          
    double min_angle;     
    double max_angle;     
    double min_v;         
    double max_v;         
   double impact_power;  
    int is_destroyed;    
} EscortShip;
typedef struct{
char notation;        
    char name[30];
    double x, y;          
    double vmax;          
    double health;        
} Battleship;void initialize_battleship(Battleship *b, char type);
void generate_escort_ships(EscortShip escorts[], int count, double canvas_size, double b_vmax);
double calculate_distance(double x1, double y1, double x2, double y2);
double calculate_max_range(double v, double angle_deg);
int is_in_range(EscortShip e, double bx, double by);
void save_initial_conditions(Battleship b, EscortShip escorts[], int n, int seed, double canvas_size, int route_points);
void save_final_conditions(Battleship b, int destroyed_count, int total_escorts);
void append_simulation_stat(const char *text);

int main() {
    int seed;
    double canvas_size;
    int num_escorts;
    int route_points;
    char b_type;

printf("=========================================\n");
    printf("      NAVAL BATTLE SIMULATOR SETUP       \n");
    printf("=========================================\n");

    printf("Enter Random Seed Value (e.g., 2)       : ");
    if (scanf("%d", &seed) != 1) seed = 2;

    printf("Enter Canvas Size D (e.g., 10 for 10x10): ");
    if (scanf("%lf", &canvas_size) != 1) canvas_size = 10.0;

    printf("Enter Number of Escort Ships (e.g., 4)  : ");
    if (scanf("%d", &num_escorts) != 1) num_escorts = 4;

    printf("Enter Number of Route Points (e.g., 5)  : ");
    if (scanf("%d", &route_points) != 1) route_points = 5;
 printf("\n>>> SELECT BATTLESHIP TYPE\n");
    printf("+------+----------------------------------+\n");
    printf("| CODE | MODEL NAME                       |\n");
    printf("+------+---------------------------+------+\n");
    printf("|  U   | USS Iowa (BB-61)                 |\n");
    printf("|  M   | MS King George V                 |\n");
    printf("|  R   | Richelieu                        |\n");
    printf("|  S   | Sovetsky Soyuz-class             |\n");
    printf("+------+---------------------------+------+\n");
    printf("Select Battleship type : ");
    scanf(" %c", &b_type);
srand(seed);
 Battleship b;
    initialize_battleship(&b, b_type);
 EscortShip escorts[num_escorts];
    generate_escort_ships(escorts, num_escorts, canvas_size, b.vmax);
double route_x[route_points];
    double route_y[route_points];
    for (int i = 0; i < route_points; i++) {
        route_x[i] = ((double)rand() / RAND_MAX) * canvas_size;
        route_y[i] = ((double)rand() / RAND_MAX) * canvas_size;
    }
save_initial_conditions(b, escorts, num_escorts, seed, canvas_size, route_points);
FILE *stat_file = fopen("Simulation_Statistics.txt", "w");
    if (stat_file) fclose(stat_file);
printf("\n\n              NAVAL BATTLE SIMULATOR          \n");
    printf("                 Simulation Mode              \n\n");
    printf("Random Seed        : %d\n", seed);
    printf("Canvas Size        : %.0f x %.0f\n", canvas_size, canvas_size);
    printf("Escort Fleet       : %d ships\n", num_escorts);
    printf("Route Points       : %d\n\n", route_points);
    printf("Battleship Selected\n");
    printf("   %c  |  %s\n", b.notation, b.name);
    printf("   Vmax : %.2f m/s\n\n\n", b.vmax);
    printf(">>> SIMULATION IN PROGRESS <<<\n\n");

    int destroyed_escorts_count = 0;
for (int step = 0; step < route_points; step++) {

 b.x = route_x[step];
        b.y = route_y[step];

        printf("\nSTEP %d\n", step + 1);
        if (step == 0) {
            printf("BATTLESHIP LOCATION : (%.2f, %.2f)\n", b.x, b.y);
        } else {
            printf("Location : (%.2f, %.2f)\n", b.x, b.y);
        }
        printf("HEALTH               : %.1f%%\n", b.health);
 for (int i = 0; i < num_escorts; i++) {
            if (!escorts[i].is_destroyed) {
                if (is_in_range(escorts[i], b.x, b.y)) {
                    double damage = escorts[i].impact_power * 100.0;
                    b.health -= damage;
                    if (b.health < 0) b.health = 0;

                    printf("\nIncoming attack from E[%d] (%s)\n", i, escorts[i].type_code);
                    printf("Damage taken         : %.0f%%\n", damage);
                    printf("Health               : %.1f%%\n", b.health);
  escorts[i].is_destroyed = 1;
                    destroyed_escorts_count++;
                    break;
                }
            }
        }

printf("\nTarget Engagements\n");
        for (int i = 0; i < num_escorts; i++) {
 double dist = calculate_distance(b.x, b.y, escorts[i].x, escorts[i].y);
 double flight_time = dist / (b.vmax * cos(45.0 * M_PI / 180.0));
            double response_time = flight_time + (0.1 * (i + 1));

            printf("E[%d]   distance %.1f   response %.3f s\n", i, dist, response_time);
        }

        if (b.health <= 0) {
            printf("\nBattleship Destroyed at Step %d!\n", step + 1);
            break;
        }
    }
 printf("\n\n>>> SIMULATION FINISHED <<<\n\n");
    printf("FINAL STATUS\n");
    printf("Battleship : %s\n", (b.health > 0) ? "ALIVE" : "DESTROYED");
    printf("Health     : %.1f%%\n", b.health);
    printf("Destroyed  : %d of %d escort ships\n\n", destroyed_escorts_count, num_escorts);

    printf("Output files created:\n");
    printf("- Initial_Conditions.txt\n");
    printf("- Simulation_Statistics.txt\n");
    printf("- Final_Conditions.txt\n");


 save_final_conditions(b, destroyed_escorts_count, num_escorts);

    return 0;
}

void initialize_battleship(Battleship *b, char type) {
    b->notation = type;
    b->health = 100.0;
    b->x = 0.0;
    b->y = 0.0;

    switch (type) {
        case 'U':
        case 'u':
            snprintf(b->name, sizeof(b->name), "USS Iowa");
            b->vmax = 155.15;
            break;
        case 'M':
        case 'm':
            snprintf(b->name, sizeof(b->name), "MS King George V");
            b->vmax = 140.00;
            break;
        case 'R':

case 'r':
            snprintf(b->name, sizeof(b->name), "Richelieu");
            b->vmax = 148.50;
            break;
        case 'S':
        case 's':
            snprintf(b->name, sizeof(b->name), "Sovetsky Soyuz-class");
            b->vmax = 150.00;
            break;
        default:
            snprintf(b->name, sizeof(b->name), "USS Iowa");
            b->vmax = 155.15;
            b->notation = 'U';
            break;
    }
}


void generate_escort_ships(EscortShip escorts[], int count, double canvas_size, double b_vmax) {
    const char *codes[] = {"EA", "EB", "EC", "ED", "EE"};
    const char *names[] = {"1936A-class Destroyer", "Gabbiano-class Corvette", "Matsu-class Destroyer", "F-class Escort Ships", "Japanese Kaibokan"};
    double impacts[] = {0.08, 0.06, 0.07, 0.05, 0.04};

    for (int i = 0; i < count; i++) {
        escorts[i].id = i;
        int type_idx = rand() % 5;

        snprintf(escorts[i].type_code, sizeof(escorts[i].type_code), "%s", codes[type_idx]);
        snprintf(escorts[i].type_name, sizeof(escorts[i].type_name), "%s", names[type_idx]);


 escorts[i].x = ((double)rand() / RAND_MAX) * canvas_size;
        escorts[i].y = ((double)rand() / RAND_MAX) * canvas_size;
        escorts[i].impact_power = impacts[type_idx];
        escorts[i].is_destroyed = 0;

        escorts[i].min_angle = 10.0 + (rand() % 15);
        escorts[i].max_angle = escorts[i].min_angle + 20.0;
        escorts[i].min_v = 10.0;
        escorts[i].max_v = (type_idx == 0) ? 1.2 * b_vmax : (0.4 + ((rand() % 5) / 10.0)) * b_vmax;
    }
}
double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


double calculate_max_range(double v, double angle_deg) {
    double rad = angle_deg * M_PI / 180.0;
    return (v * v * sin(2.0 * rad)) / GRAVITY;
}


int is_in_range(EscortShip e, double bx, double by) {
    double dist = calculate_distance(e.x, e.y, bx, by);
    if (dist >= 0.5 && dist <= 12.0) {
        return 1;
    }
    return 0;
}


void save_initial_conditions(Battleship b, EscortShip escorts[], int n, int seed, double canvas_size, int route_points) {
    FILE *f = fopen("Initial_Conditions.txt", "w");
    if (!f) return;

    fprintf(f, "INITIAL CONDITIONS\n");
    fprintf(f, "Random Seed: %d\n", seed);
    fprintf(f, "Canvas Size: %.0fx%.0f\n", canvas_size, canvas_size);
    fprintf(f, "Route Points: %d\n", route_points);
    fprintf(f, "Battleship: %s (%c), Vmax: %.2f m/s\n\n", b.name, b.notation, b.vmax);

    fprintf(f, "Escort Ships:\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "E[%d]: %s (%s) at (%.2f, %.2f) | Impact Power: %.2f\n",
                i, escorts[i].type_name, escorts[i].type_code, escorts[i].x, escorts[i].y, escorts[i].impact_power);
    }
    fclose(f);
}


void save_final_conditions(Battleship b, int destroyed_count, int total_escorts) {
    FILE *f = fopen("Final_Conditions.txt", "w");
    if (!f) return;

    fprintf(f, "FINAL CONDITIONS\n");
    fprintf(f, "Battleship Status: %s\n", (b.health > 0) ? "ALIVE" : "DESTROYED");
    fprintf(f, "Final Health: %.1f%%\n", b.health);
    fprintf(f, "Escort Ships Destroyed: %d of %d\n", destroyed_count, total_escorts);
    fclose(f);
}
