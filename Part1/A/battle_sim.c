#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
#define GRAVITY 9.81
#define M_PI 3.14159265358979323846

struct Escort
{
   int id;
   double x;
   double y;
   int type;
   double V;
   double angle;
   int alive;

};
const char* getShipTypeName(int type) {
    switch (type) {
        case 1: return "EA (1936A-class Destroyer)";
        case 2: return "EB (Gabbiano-class Corvette)";
        case 3: return "EC (Type 39 Torpedo Boat)";
        case 4: return "ED (F-class Escort Ship)";
        case 5: return "EE (M-class Minesweeper)";
        default: return "Unknown Escort";
    }
}

  void runPart1A(); 
  void showInstructions();
  
  void runPart1A(){
   char battleshipType;
   double maxRange;
   int battlefieldSize;
   int  battleshipX, battleshipY, battleshipV;
   int numberOfShips, i;
   int hitsByB = 0;
   double maxbattleTime = 0;
   struct Escort ships[100];
   FILE *fpInit, *fpSim, *fpFinal;
   srand((unsigned int)time(NULL));
   
   printf("============ADVANCED NAVAL BATTLE SIMULATOR\n===============");
   printf("======WELCOME TO PART1A ===============");
   printf("\n--- START SIMULATION ---\n");
   printf("-BATTLESHIP SETUP-");
   printf("available battleships:\n");
   printf("U - USS Iowa (BB-61)\n");
   printf("M - MS King George V\n");
   printf("R - Richelieu\n");
   printf("S - Sovetsky Soyuz-class\n\n");

   printf("Enter Battleship type (U/M/R/S): ");
   scanf(" %c", &battleshipType); 
   printf("Enter battlefield size: ");
   scanf("%d", &battlefieldSize);
   printf("Enter Battleship X Y Velocity: "); 
   scanf("%d %d  %d", &battleshipX, &battleshipY, &battleshipV);
   printf("\nBattleship setup completed successfully!\n");
   printf("Enter number of Escort Ships: ");
   scanf("%d", &numberOfShips);
   
for(i=0; i<numberOfShips; i++){
   ships[i].id = i+1;
   ships[i].x = rand() % battlefieldSize;
   ships[i].y = rand() % battlefieldSize;
   ships[i].type = rand() % 5+1;
   ships[i].V = rand() % 10 + 1;
   ships[i].angle = rand() % 360; 
   ships[i].alive = 1;
}
   printf("\n%d Escort Ships generated successfully!\n", numberOfShips);

   fpInit = fopen("initial_condition.txt", "w");
if (fpInit) {
   fprintf(fpInit, "Battleship Type: %c\n", battleshipType);
   fprintf(fpInit, "Battlefield Size: %d\\n", battlefieldSize);
   fprintf(fpInit, "Battleship: X=%d Y=%d Type=%d V=%d\n", battleshipX
    , battleshipY, battleshipType, battleshipV);
   fprintf(fpInit, "Number of Escort Ships: %d\n", numberOfShips);
   
   for(i=0; i<numberOfShips; i++)
    fprintf(fpInit, "Escort %d [%s]: Pos=(%.2f, %.2f) Speed=%.2f Angle=%.2f\n", 
                    ships[i].id, getShipTypeName(ships[i].type), ships[i].x,
 ships[i].y, ships[i].V, ships[i].angle);
}
   fclose(fpInit);
   printf("Initial_Conditions.txt saved!\n");
 
  
  maxRange = ( battleshipV* battleshipV) / GRAVITY;

printf("=====================BATTLESHIP ATTACK\n===============");
printf("Battleship Maximum Attack Range: %.2f m\n\n", maxRange);
 fpSim = fopen("simulation_data.txt", "w");
    
    
for(i=0; i<numberOfShips; i++){
   
   double dx =     ships[i].x - battleshipX ;
   double dy =    ships[i].y - battleshipY;
   double distance = sqrt(dx*dx + dy*dy);
   printf("Escort Ship %d [%s]\n", ships[i].id, getShipTypeName(ships[i].type));
   printf("Distance from Battleship: %.2f m\n", distance);

    if(distance <= maxRange){
       ships[i].alive = 0;
  hitsByB++;


double sin2Theta = (distance * GRAVITY) / (battleshipV* battleshipV);
 if (sin2Theta > 1.0) sin2Theta = 1.0;
double firingAngleRad = 0.5 * asin(sin2Theta);
double firingAngleDeg = firingAngleRad * (180.0 / M_PI);
double timeToHit = (2.0 * battleshipV * sin(firingAngleRad)) / GRAVITY;
if (timeToHit > maxbattleTime )
 {
                maxbattleTime  = timeToHit;
}
            printf("Result: HIT - Escort Ship destroyed\n");
            printf("Firing Angle: %.2f degrees\n", firingAngleDeg);
            printf("Time to hit: %.2f seconds\n\n", timeToHit);
 
if (fpSim) {
                fprintf(fpSim, "Escort Index: %d, Distance: %.2f m, TimeToHit: %.2f s, Status: Hit\n",
                        ships[i].id, distance, timeToHit);
            }
        } else {
            printf("Result: MISSED - Out of range\n\n");
        }
    }

 
            
     
  
 printf("Total Escort Ships destroyed by Battleship: %d\n\n", hitsByB);

 printf("==========ESCORT SHIPS COUNTER-ATTACK\n==============");
    int bSunk = 0;
    int sunkByEIndex = -1;
  for (i = 0; i < numberOfShips; i++) {
 printf("Escort Ship %d [%s]\n", ships[i].id, getShipTypeName(ships[i].type));
        if (ships[i].alive == 0) 
      {
         printf("Status: Destroyed by Battleship\n");
         printf("Cannot attack.\n\n"); 

        } else {
            printf("Status: Active\n");
            printf("Attacking Battleship...\n\n");

            double dx = battleshipX - ships[i].x;
            double dy = battleshipY - ships[i].y;
            double distance = sqrt(dx * dx + dy * dy);
            double maxRangeE = (ships[i].V * ships[i].V) / GRAVITY;

            if (distance <= maxRangeE) {
                bSunk = 1;
                sunkByEIndex = ships[i].id;
                printf("Result: HIT! Battleship destroyed by Escort %d\n\n", ships[i].id);
                break;
            } else {
                printf("Result: MISSED - Battleship out of reach\n\n");
      }
    }
}
 if (fpSim)
   fclose(fpSim);
    printf("Simulation data saved to simulation_data.txt\n");
if (bSunk) {
        printf("================== BATTLESHIP SUNK! ===================\n");
        printf("Sunk by Escort Ship Index: %d\n", sunkByEIndex);

} else {
    printf("================== BATTLESHIP SURVIVED!\n===========");
    printf("Escort Ships destroyed by B: %d\n", hitsByB);
    printf("Battle End Time: %.2f seconds\n", maxbattleTime);
    printf("Battle ended successfully.\n\n");

    
}

fpFinal = fopen("Final_Condition.txt", "w");
if (fpFinal) {
 if (bSunk) {
    fprintf(fpFinal, "Battleship Status: SUNK\n");
   fprintf(fpFinal, "Sunk by Escort Ship Index: %d\n", sunkByEIndex);
} else {
   
   fprintf(fpFinal, "Battleship Status: SURVIVED\n");
   fprintf(fpFinal, "Battle Time: %.2f seconds\n", maxbattleTime);
   }     
fprintf(fpFinal, "Hits by B: %d\n", hitsByB);
 for(i=0; i<numberOfShips; i++) {
  fprintf(fpFinal, "Escort %d Status: %s\n", ships[i].id, ships[i].alive ?
 "Alive" : "Destroyed");
}

  fclose(fpFinal);
 printf("Final_Conditions.txt saved!\n");
   }
 printf("-- Simulation complete---\n");
}

void showInstructions(){
 printf("\n---Instruction---\n");
 printf("1. Select Start Part 1-A Simulation from the menu.\n");
 printf("2. Select Battleship Type (U, M, R, S).\n");
 printf("3. Enter Battleship X Y Position, and velocity\n");
 printf("4. Enter number of Escort ships\n");
 printf("5. View trajectory, firing angles, hit details, and saved results.\n"); 
}


void showStatistics() {
    printf("\n================ STATISTICS ================\n");
    printf("No prior simulation statistics found. Run a simulation first.\n");
}

int main(){

	int choice;
	int battleshipY;
	int battleshipX;
	int battlefieldSize;
        int numberOfShips;
        int i;
        
        do{ 
        printf("\n==============\n");
        printf("NAVAL BATTLE SIMULATOR---");
        printf("========================\n");
        printf("1.Start part 1-A simulation\n");
        printf("2.View instractions\n");
        printf("3.View simulation Statistics\n");
        printf("4.Exit\n");
        printf("enter  your choice: ");
        scanf("%d", &choice);
 
if(choice == 1)
    runPart1A();
else if(choice == 2)
   showInstructions();
else if(choice == 3)
   showStatistics();
else if(choice == 4)
  printf("exiting...thank you!\n");
else
  printf("invalid choice! Try again.\n");
}
while(choice!=4);
return 0;
}

