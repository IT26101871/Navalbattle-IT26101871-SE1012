#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct 
{
   int id;
   int x;
   int y;
   int type;
   int V;
   int angle;
   int alive;

}Escort;
typedef struct{
     int x;
     int y;
}PathPoint;
int calculateDistanceSq(int x1, int y1, int x2, int y2 )
{
     int dx = x1 - x2;
     int dy = y1 - y2;
     return (dx*dx + dy*dy);
}
 
  void runPart1A(){
 
   int battlefieldSize, battleshipX, battleshipY, battleshipVelocity
  , battleshipType;
  int numberOfEscorts, i;
   int hitsByBattleship = 0,battleTime = 0, isbattleshipSunk = 0
  , sunkByEscortId = -1;
   Escort escortShips[20];
   FILE *initialFile, *finalFile;
   
   srand((unsigned int)time(NULL));
printf("\n==============================\n");
printf("NAVAL BATTLE SIMULATOR - PART 1A\n");
printf("================================\n");
printf("Enter battlefield size: ");
scanf("%d", &battlefieldSize);
printf("Enter Battleship X Y Type V: "); 
scanf("%d %d %d %d", &battleshipX, &battleshipY, &battleshipType,
 &battleshipVelocity);
   printf("Enter number of Escort Ships: ");
   scanf("%d", &numberOfEscorts);

   
for(i=0; i<numberOfEscorts; i++){
  
escortShips[i].id = i+1;
escortShips[i].x = rand() % battlefieldSize;
escortShips[i].y = rand() % battlefieldSize;
escortShips[i].type = rand() % 5+1;
escortShips[i].V = rand() % 10 + 1;
escortShips[i].angle = rand() % 360; 
escortShips[i].alive = 1;
}

   initialFile = fopen("initial_condition.txt", "w");
   if(initialFile){
   fprintf(initialFile, "Battlefield Size: %d\\n", battlefieldSize);
   fprintf(initialFile, "Battleship: X=%d Y=%d Type=%d V=%d\n", battleshipX
 , battleshipY, battleshipType, battleshipVelocity);
   fprintf(initialFile, "Number of Escort Ships: %d\n", numberOfEscorts);
   
   for(i=0; i<numberOfEscorts; i++){
   fprintf(initialFile, "E%d: X=%d Y=%d Type=%d V=%d Angle=%d\n", escortShips[i].id
 , escortShips[i].x, escortShips[i].y,escortShips[i].type, escortShips[i].V, escortShips[i].angle);
}
   fclose(initialFile);
   printf("Initial_Conditions.txt saved!\n");
}   
   while(isbattleshipSunk == 0){
   battleTime++;
   int activeEscortsCount = 0;
   for(i=0; i<numberOfEscorts; i++){
     if(escortShips[i].alive){
     activeEscortsCount++;
       if (calculateDistanceSq(battleshipX, battleshipY, escortShips[i].x, escortShips[i].y) <= 9) {
           escortShips[i].alive = 0;
           hitsByBattleship++;
  
      }
   }
}
for(i=0; i<numberOfEscorts; i++){
   if(escortShips[i].alive){
if (calculateDistanceSq(battleshipX, battleshipY, escortShips[i].x, escortShips[i].y) <= 4) {
                    isbattleshipSunk = 1;
                    sunkByEscortId = escortShips[i].id;
     break;
    }
  }
}

if(activeEscortsCount == 0 || battleTime > 100)
     break;

}

finalFile = fopen("Final_Condition.txt", "w");
if( finalFile){
fprintf( finalFile, "Battle Time: %d seconds\n:", battleTime);
fprintf( finalFile, "Hits by B: %d\n", hitsByBattleship);
fprintf( finalFile, "B Sunk: %s\n", isbattleshipSunk ? "Yes":"No");


 if(sunkByEscortId!= -1)
 fprintf( finalFile, "Sunk By: E%d\n", sunkByEscortId); 
for(i=0; i<numberOfEscorts; i++){
    fprintf(finalFile,"E%d: Alive=%d\n",escortShips[i].id, escortShips[i].alive);

}
 fclose(finalFile);

printf("Final_Conditions.txt saved!\n");
}
 printf("\n--- SIMULATION 1A COMPLETE ---\n");
    if (isbattleshipSunk) {
        printf("Result: Battleship SUNK by Escort #%d\n", sunkByEscortId);
    } else {
        printf("Result: Battleship survived! Hits on Escorts: %d\n", hitsByBattleship);
    }
}


int processCombat1B(
    PathPoint battleshipPosition,
    Escort escortShips[],
    int numberOfEscorts,
    int isGunJammed,
    int *hitsThisTurn)
{

int sunkByEscortId = -1;
*hitsThisTurn = 0;
for (int i = 0; i < numberOfEscorts; i++) {
        if (escortShips[i].alive) {
            int distanceSq = calculateDistanceSq(battleshipPosition.x, battleshipPosition.y, escortShips[i].x,
 escortShips[i].y);
            if (!isGunJammed && distanceSq <= 9) {
                escortShips[i].alive = 0;
                (*hitsThisTurn)++;
            } else if (isGunJammed && distanceSq >= 2 && distanceSq <= 9) {
                escortShips[i].alive = 0;
                (*hitsThisTurn)++;
            }
        }
    }



for (int i = 0; i < numberOfEscorts; i++) {
        if (escortShips[i].alive) {
            int distanceSq = calculateDistanceSq(battleshipPosition.x, battleshipPosition.y, escortShips[i].x,
 escortShips[i].y);
            if (distanceSq <= 4) {
                sunkByEscortId = escortShips[i].id;
                break;
            }
        }
    }

return sunkByEscortId;
}


void runPart1B(){
 int battlefieldSize;
int battleshipX, battleshipY, battleshipType, battleshipVelocity;
int numberOfEscorts, pathPointsCount, gunJamIteration;

printf("\n=====================\n");
printf("NAVAL BATTLE SIMULATOR -PART 1B\n");
printf("Enter battlefield size : ");
scanf("%d", &battlefieldSize);
printf("Enter Battleship X Y Type V: ");
scanf("%d %d %d %d", &battleshipX, &battleshipY, 
&battleshipType, &battleshipVelocity);
printf("Enter number of Escort ships: ");
scanf("%d", &numberOfEscorts);
printf("Enter number of path points(k): ");
scanf("%d", &pathPointsCount);
printf("Enter  gun jam iteration: ");
scanf("%d", &gunJamIteration);

Escort *originalEscorts = (Escort *)malloc(numberOfEscorts * sizeof(Escort));
    Escort *escortsSimulation1 = (Escort *)malloc(numberOfEscorts * sizeof(Escort));
    Escort *escortsSimulation2 = (Escort *)malloc(numberOfEscorts * sizeof(Escort));
    PathPoint *battleshipPath = (PathPoint *)malloc(pathPointsCount * sizeof(PathPoint));


 for(int i=0; i<numberOfEscorts; i++){
originalEscorts[i].id = i+1;
originalEscorts[i].x = rand() % battlefieldSize;
originalEscorts[i].y = rand() % battlefieldSize;
originalEscorts[i].type = rand() % 5+1;
originalEscorts[i].V = rand() % 10+1;
originalEscorts[i].angle =  rand() % 360;
originalEscorts[i].alive = 1;
}
 for (int i = 0; i <pathPointsCount; i++){
     battleshipPath[i].x  = rand() % battlefieldSize;
        battleshipPath[i].y = rand() % battlefieldSize;
    }

FILE *initialFile1B = fopen("PART1B_Initial_conditions.txt", "w");
if(initialFile1B){
fprintf(initialFile1B, "Battlefield Size: %d\n", battlefieldSize);
        fprintf(initialFile1B, "Battleship Initial: X=%d Y=%d Type=%d V=%d\n", 
                battleshipX, battleshipY, battleshipType, battleshipVelocity);
        fprintf(initialFile1B, "Escorts Count: %d | Path Points (k): %d | Gun Jam Step (t): %d\n\n", 
                numberOfEscorts, pathPointsCount, gunJamIteration);

for(int i=0 ; i<numberOfEscorts; i++){
fprintf(initialFile1B, "E%d: Pos=(%d,%d) Type=%d V=%d Angle=%d\n", 
                    originalEscorts[i].id, originalEscorts[i].x, originalEscorts[i].y, 
                    originalEscorts[i].type, originalEscorts[i].V, originalEscorts[i].angle);
}
fclose(initialFile1B);
printf("\nPart1B_Initial_Conditions.txt saved!\n");}

printf("\n----------------------------------\n");
printf("SIMULATION 1_BATTLESHIP PATH\n");
printf("------------------------------\n");
FILE *simulation1File = fopen("Part1_Simulation1.txt", "w");
for(int iteration = 0; iteration < pathPointsCount; iteration++) {
        int hitsThisTurn = 0;
        int sunkByEscortId = processCombat1B(battleshipPath[iteration], escortsSimulation1, numberOfEscorts,
 0, &hitsThisTurn);

if (sunkByEscortId != -1) {
            printf("Iteration %d: B at (%d,%d), Hits=%d [SUNK by Escort #%d]\n", 
                   iteration + 1, battleshipPath[iteration].x, battleshipPath[iteration].y, hitsThisTurn, sunkByEscortId);
            if (simulation1File) {
                fprintf(simulation1File, "Iteration %d: B at (%d,%d), Hits=%d [SUNK by Escort #%d]\n", 
                        iteration + 1, battleshipPath[iteration].x, battleshipPath[iteration].y, hitsThisTurn, sunkByEscortId);
            }
            break;
        }
printf("Iteration %d: B at (%d,%d), Hits=%d\n", 
               iteration + 1, battleshipPath[iteration].x, battleshipPath[iteration].y, hitsThisTurn);
        if (simulation1File) {
            fprintf(simulation1File, "Iteration %d: B at (%d,%d), Hits=%d\n", 
                    iteration + 1, battleshipPath[iteration].x, battleshipPath[iteration].y, hitsThisTurn);
        }
    }
    if (simulation1File) fclose(simulation1File);
    printf("\nSimulation 1 results saved to Part1B_Simulation1.txt\n");
 
printf("\n=============================\n");
printf("SIMULATION 2- GUN JAM\n");
printf("=========================\n");



    srand((unsigned int)time(NULL));
}
void  showInstructions()
{
printf("\n---Instruction---\n");
printf("1. Enter battlefield size N for NxN grid\n");
 printf("2. Enter Battleship X Y Position, Type 1-5, Speed 1-10\n");
 printf("3. Enter number of Escort ships\n"); 
}

int main(){

	int choice;
	int battleshipY;
	int battleshipX;
	int battlefieldSize;
        int numberOfEscorts;
        int i;
           
        do{ 
        printf("\n----------\n");
        printf("NAVAL BATTLE SIMULATOR---");
        printf("-------\n");
        printf("1.Start simulation\n");
        printf("2.View instractions\n");
        printf("3. simulation statistics\n");
        printf("4.Exit\n");
        printf("enter  your choice: ");
        scanf("%d", &choice);
 
if(choice==1)
    runPart1A();
else if(choice == 2)
   showInstructions();
else if(choice==3)
  printf("run simulation first to see statistics\n");
else if(choice == 4)
  printf("exiting.. thank you!\n");
else
  printf("invalid choice! Try again.\n");
}
while(choice!=4);
return 0;
}

