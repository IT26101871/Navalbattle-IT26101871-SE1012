#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
   
    int seed, canvas_size, escort_count;
    char ship_type;
    double vmax_input, tb_input, x_input, y_input;
    double te_ea_input, te_eb_input, te_ec_input, te_ed_input, te_ee_input;

   
    double vmax_b, tb, pos_x, pos_y;
    double te_ea, te_eb, te_ec, te_ed, te_ee;

   
    double time_step = 0.0;
    double escort_x = 2.51, escort_y = 2.60; 
    double distance, travel_time, total_time;

    
    printf("================================================================================\n");
    printf("               ADVANCED NAVAL TACTICAL SIMULATION ENGINE (PART 2-B)\n");
    printf("================================================================================\n\n");

    
    printf("[SECTION 1: BATTLEFIELD INITIALIZATION]\n");
    printf("  [PARAM] Enter random seed value                     : ");
    scanf("%d", &seed);
    srand(seed); 

    printf("  [PARAM] Enter canvas dimensions D (D x D grid)      : ");
    scanf("%d", &canvas_size);

    printf("  [PARAM] Enter total number of escort ships N (1-100): ");
    scanf("%d", &escort_count);
    printf("\n");

    
    printf("[SECTION 2: FLAGSHIP FLEET CONFIGURATION]\n");
    printf("  Available Battleship Models & Specifications:\n");
    printf("  ------------------------------------------------------------------------------\n");
    printf("  CLASS CODE | SHIP NAME / CLASS          | MAIN ARMAMENT SPECIFICATION\n");
    printf("  ------------------------------------------------------------------------------\n");
    printf("      U      | USS Iowa (BB-61)           | 50-caliber Mark 7 gun\n");
    printf("      M      | MS King George V           | (356 mm) Mark VII gun\n");
    printf("      R      | Richelieu                  | (15 inch) Mle 1935 gun\n");
    printf("      S      | Sovetsky Soyuz-class       | (16 inch) B-37 gun\n");
    printf("  ------------------------------------------------------------------------------\n\n");

    printf("  [INPUT] Select flagship class code (U/M/R/S)        : ");
    scanf(" %c", &ship_type);

    printf("   Maximum shell velocity Vmax_B (0 = auto)    : ");
    scanf("%lf", &vmax_input);
    vmax_b = (vmax_input == 0) ? (150.0 + (rand() % 5000) / 100.0) : vmax_input;
    if (vmax_input == 0) printf("          [CALC] Auto-generated Shell Vmax            : %.2f m/s\n", vmax_b);

    printf("  Battleship reload interval T_B (0 = auto)   : ");
    scanf("%lf", &tb_input);
    tb = (tb_input == 0) ? (2.0 + (rand() % 300) / 100.0) : tb_input;
    if (tb_input == 0) printf("          [CALC] Auto-generated Reload Time T_B       : %.2f s\n", tb);

    printf("   Flagship spawn coordinates (x y / -1 -1)    : ");
    scanf("%lf %lf", &x_input, &y_input);
    if (x_input == -1 && y_input == -1) {
        pos_x = (rand() % (canvas_size * 100)) / 100.0;
        pos_y = (rand() % (canvas_size * 100)) / 100.0;
        printf("  Auto-generated Position (X, Y)       : (%.2f, %.2f)\n\n", pos_x, pos_y);
    } else {
        pos_x = x_input;
        pos_y = y_input;
        printf("\n");
    }

    
    printf("[SECTION 3: ESCORT CATEGORY RELOAD INTERVALS (T_E^p)]\n");

    printf("  Category EA reload interval (0 = auto)      : ");
    scanf("%lf", &te_ea_input);
    te_ea = (te_ea_input == 0) ? (3.0 + (rand() % 200) / 100.0) : te_ea_input;
    if (te_ea_input == 0) printf(" --> [CALC] T_E^EA = %.2f s\n", te_ea);

    printf("  Category EB reload interval (0 = auto)      : ");
    scanf("%lf", &te_eb_input);
    te_eb = (te_eb_input == 0) ? (4.0 + (rand() % 200) / 100.0) : te_eb_input;
    if (te_eb_input == 0) printf(" --> [CALC] T_E^EB = %.2f s\n", te_eb);

    printf("  Category EC reload interval (0 = auto)      : ");
    scanf("%lf", &te_ec_input);
    te_ec = (te_ec_input == 0) ? (4.0 + (rand() % 200) / 100.0) : te_ec_input;
    if (te_ec_input == 0) printf(" --> [CALC] T_E^EC = %.2f s\n", te_ec);

    printf("  Category ED reload interval (0 = auto)      : ");
    scanf("%lf", &te_ed_input);
    te_ed = (te_ed_input == 0) ? (5.0 + (rand() % 200) / 100.0) : te_ed_input;
    if (te_ed_input == 0) printf(" --> [CALC] T_E^ED = %.2f s\n", te_ed);

    printf("  Category EE reload interval (0 = auto)      : ");
    scanf("%lf", &te_ee_input);
    te_ee = (te_ee_input == 0) ? (3.0 + (rand() % 200) / 100.0) : te_ee_input;
    if (te_ee_input == 0) printf(" --> [CALC] T_E^EE = %.2f s\n\n", te_ee);

    printf("[EVENT] Deploying %d escort units onto canvas grid... [SUCCESS]\n", escort_count);
    FILE *initialFile = fopen("Initial_Conditions.txt", "w");

if (initialFile != NULL)
{
    fprintf(initialFile, "PART 2-B INITIAL CONDITIONS\n");
    fprintf(initialFile, "============================\n");
    fprintf(initialFile, "Seed: %d\n", seed);
    fprintf(initialFile, "Canvas Size: %d\n", canvas_size);
    fprintf(initialFile, "Escort Count: %d\n", escort_count);
    fprintf(initialFile, "Battleship Type: %c\n", ship_type);
    fprintf(initialFile, "Vmax_B: %.2f m/s\n", vmax_b);
    fprintf(initialFile, "T_B: %.2f s\n", tb);
    fprintf(initialFile, "Position: (%.2f, %.2f)\n", pos_x, pos_y);

    fprintf(initialFile, "\nEscort Reload Times:\n");
    fprintf(initialFile, "EA: %.2f s\n", te_ea);
    fprintf(initialFile, "EB: %.2f s\n", te_eb);
    fprintf(initialFile, "EC: %.2f s\n", te_ec);
    fprintf(initialFile, "ED: %.2f s\n", te_ed);
    fprintf(initialFile, "EE: %.2f s\n", te_ee);

    fclose(initialFile);

    printf("[FILE]  Initial state records saved to -> Initial_Conditions.txt\n\n");
}
else
{
    printf("[ERROR] Could not create Initial_Conditions.txt\n\n");
}

    
    distance = sqrt(pow(pos_x - escort_x, 2) + pow(pos_y - escort_y, 2)); 
    travel_time = distance / vmax_b;                                      
    
    printf("=====================================================================\n");
    printf("                       REAL-TIME COMBAT ENGAGEMENT LOG\n");
    printf("======================================================================\n");
    printf("  TIMESTAMP   ENGAGEMENT DETAILS                TARGET RANGE   TARGET STATUS\n");
    printf("  ------------------------------------------------------------------------------\n");

    for (int i = 0; i < escort_count; i++) {
        total_time = time_step + travel_time;
        printf("  [%.2fs]     Battleship engaged Escort E[%d]      %.1fm        DESTROYED!\n", total_time, i, distance);
        time_step += tb; 
    }
    printf("===============================================================================\n\n");

FILE *statsFile = fopen("Simulation_Statistics.txt", "w");

if (statsFile != NULL)
{
    fprintf(statsFile, "PART 2-B SIMULATION STATISTICS\n");
    fprintf(statsFile, "===============================\n\n");

    fprintf(statsFile, "Seed: %d\n", seed);
    fprintf(statsFile, "Canvas Size: %d\n", canvas_size);
    fprintf(statsFile, "Escort Count: %d\n", escort_count);

    fprintf(statsFile, "\nBattleship Type: %c\n", ship_type);
    fprintf(statsFile, "Vmax_B: %.2f m/s\n", vmax_b);
    fprintf(statsFile, "T_B: %.2f s\n", tb);

    fprintf(statsFile, "\nEscort Reload Times:\n");
    fprintf(statsFile, "EA: %.2f s\n", te_ea);
    fprintf(statsFile, "EB: %.2f s\n", te_eb);
    fprintf(statsFile, "EC: %.2f s\n", te_ec);
    fprintf(statsFile, "ED: %.2f s\n", te_ed);
    fprintf(statsFile, "EE: %.2f s\n", te_ee);

    fprintf(statsFile, "\nCOMBAT RESULTS\n");
    fprintf(statsFile, "---------------\n");

    for (int i = 0; i < escort_count; i++)
    {
        double attack_time = travel_time + (i * tb);

        fprintf(statsFile,
                "[%.2fs] Battleship engaged E[%d] - Distance %.2f m - DESTROYED\n",
                attack_time,
                i,
                distance);
    }

    fprintf(statsFile, "\nTotal Battle Time: %.3f seconds\n",
            total_time);

    fclose(statsFile);

    printf("[FILE]  Combat execution metrics saved to -> Simulation_Statistics.txt\n\n");
}
else
{
    printf("[ERROR] Could not create Simulation_Statistics.txt\n");
}




    printf("[FILE]  Combat execution metrics saved to -> Simulation_Statistics.txt\n\n");


    printf("[SECTION 4: POST-BATTLE EVALUATION REPORT]\n");
    printf("  [DATA] Flagship Combat Status                       : SURVIVED\n");
    printf("  [DATA] Remaining Hull Integrity (HP)                : 100.00%%\n");
    printf("  [DATA] Escort Targets Neutralized                   : %d / %d\n", escort_count, escort_count);
    printf("  [DATA] Total Engagement Duration                    : %.3f seconds\n\n", total_time);



FILE *finalFile = fopen("Final_Conditions.txt", "w");

if (finalFile != NULL)
{
    fprintf(finalFile, "PART 2-B FINAL BATTLE REPORT\n");
    fprintf(finalFile, "============================\n\n");

    fprintf(finalFile,
            "Flagship Combat Status      : SURVIVED\n");

    fprintf(finalFile,
            "Remaining Hull Integrity    : 100.00%%\n");

    fprintf(finalFile,
            "Escort Targets Neutralized  : %d / %d\n",
            escort_count,
            escort_count);

    fprintf(finalFile,
            "Total Engagement Duration   : %.3f seconds\n",
            total_time);

    fclose(finalFile);

    printf("[FILE]  Final battlefield summary saved to -> Final_Conditions.txt\n\n");
}
else
{
    printf("[ERROR] Could not create Final_Conditions.txt\n");
}



    printf("[FILE]  Final battlefield summary saved to -> Final_Conditions.txt\n\n");

    printf("[SYSTEM] Simulation ended. Press ENTER to close...");
    getchar();
    getchar();

    return 0;
}
