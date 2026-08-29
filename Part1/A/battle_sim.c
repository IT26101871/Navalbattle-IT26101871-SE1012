#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Escort
{
   int id;
   int x;
   int y;
   int type;
   int V;
   int angle;
   int alive;

};
  void runPart1A(); 
  void showInstructions();
  
  void runPart1A(){
   int battlefieldSize, battleshipX, battleshipY, battleshipV, battleshipType;
   int numberOfShips, i;
   int hitsByB = 0,battleTime = 0, bSunk = 0, sunkBy = -1;
   struct Escort ships[20];
   FILE *fp1, *fp2;
   srand(time(NULL));
   
   printf("\n--- START SIMULATION ---\n");
   printf("Enter battlefield size: ");
   scanf("%d", &battlefieldSize);
   printf("Enter Battleship X Y Type V: "); 
   scanf("%d %d %d %d", &battleshipX, &battleshipY, &battleshipType, &battleshipV);
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

   fp1 = fopen("initial_condition.txt", "w");
   fprintf(fp1, "Battlefield Size: %d\\n", battlefieldSize);
   fprintf(fp1, "Battleship: X=%d Y=%d Type=%d V=%d\n", battleshipX
 , battleshipY, battleshipType, battleshipV);
   fprintf(fp1, "Number of Escort Ships: %d\n", numberOfShips);
   
   for(i=0; i<numberOfShips; i++)
   fprintf(fp1, "E%d: X=%d Y=%d Type=%d V=%d Angle=%d\n", ships[i].id
 , ships[i].x, ships[i].y,ships[i].type, ships[i].V, ships[i].angle);
   fclose(fp1);
   printf("Initial_Conditions.txt saved!\n");
   
   while(bSunk == 0){
   battleTime++;
   int aliveE = 0;
   for(i=0; i<numberOfShips; i++){
   if(ships[i].alive == 1){
   aliveE++;
   int dx = battleshipX - ships[i].x;
    int dy = battleshipY - ships[i].y; 
    int distSq = dx*dx + dy*dy;
    if(distSq <= 9)
    { ships[i].alive = 0;
     hitsByB++;
      }
   }
}
for(i=0; i<numberOfShips; i++){
   if(ships[i].alive == 1){
   aliveE++;
   int dx = battleshipX - ships[i].x;
    int dy = battleshipY - ships[i].y;
    int distSq = dx*dx + dy*dy;
    if(distSq <= 4){
     bSunk = 0;
     sunkBy = ships[i].id;
     break;
    }
  }
}

if(aliveE == 0)break;
if(battleTime > 100)break;
}

fp2 = fopen("Final_Condition.txt", "w");
fprintf(fp2, "Battle Time: %d seconds\n:", battleTime);
fprintf(fp2, "Hits by B: %d\n", hitsByB);

fprintf(fp2, "B Sunk: %s\n", bSunk ? "Yes" : "No");
 if(sunkBy!= -1)
 fprintf(fp2, "Sunk By: E%d\n", sunkBy); 
for(i=0; i<numberOfShips; i++) 
fprintf(fp2, "E%d: Alive=%d\n", ships[i].id, ships[i].alive);
 fclose(fp2);
 printf("Final_Conditions.txt saved!\n");

 
printf("-- Simulation complete---\n");
}
void showInstructions(){
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
        int numberOfShips;
        int i;
        
        do{ 
        printf("\n----------\n");
        printf("NAVAL BATTLE SIMULATOR---");
        printf("-------\n");
        printf("1.Start simulation\n");
        printf("2.View instractions\n");
        printf("3.simulation statistics\n");
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

