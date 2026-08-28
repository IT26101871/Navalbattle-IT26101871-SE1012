#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Escort
{
   int id;
   int x;
   int y;
   int type;
};

int main()
{
	int choice;
	int battleshipY;
	int battleshipX;
	int battlefieldSize;
        int numberOfShips;
        int i;
        
        struct Escort ships[20];
        srand(time(NULL));

	do
	{
	printf("\n-----------\n");
		printf(" NAVAL BATTLE SIMULATOR\n");
        printf("--------------\n");
	printf("1. Start Simulation\n");
	printf("2. View Instructions\n");
	printf("3. Simulation Statistics\n");
	printf("4. Exit\n");
	 
	printf("Enter your choice: ");
        scanf("%d", &choice);
         
        if(choice == 1){
	 printf("\n--- Start Simulation ---\n");
	   
	 printf("Enter Battleship size : ");
	 scanf("%d", &battlefieldSize);

	  printf("Enter Battleship X position : ");
         scanf("%d", &battleshipX);
	  
	  printf("Enter Battleship Y position : ");
         scanf("%d", &battleshipY);
         printf("Enter number of Escort Ships: ");
         scanf("%d", &numberOfShips);

        for(i=0; i<numberOfShips; i++)
{ 
ships[i].id = i+1;
ships[i].x = rand() % battlefieldSize;
ships[i].y = rand() % battlefieldSize;
ships[i].type = rand() % 5+1;
}



	  printf("\nBattlefield created.\n");
	  printf("Battlefield size:%dx %d\n",battlefieldSize,battlefieldSize );
	   printf("Battleship position:(%d,%d)\n",battleshipX, battleshipY);
	   printf("\n---Escort Ships---\n");
for(i=0; i<numberOfShips; i++)
{
       printf("E%d: Position(%d,%d) Type: E%d\n", 
           ships[i].id,
           ships[i].x,
           ships[i].y,
           ships[i].type);
 }
 }

		   else if (choice == 2)
		   {
	    printf("\n---Instructions---\n");
	    printf("The Battleship (B) attacks Escort Ships (E).\n");
            printf("The objective is to destroy as many Escort Ships as possible.\n");
            printf("Escort Ships are placed randomly on the battlefield.\n");
}

		    else if(choice == 3)
	    
		    {
	    printf("\n--- Simulation Statistics ---\n");
	    printf("No simulation results available yet.\n");
		    }
		    else if(choice == 4)
		    {
	    printf("\nExiting simulation...\n");
	}
		    else 
		    {
	     printf("\n invalid choice .please try again .\n");
	}
         
	}while(choice!=4);
			    return 0;
}
         
         	

