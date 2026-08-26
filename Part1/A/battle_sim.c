#include<stdio.h>
int main()
{
	int choice;
	int battleshipY;
	int battleshipX;
	int battlefieldSize;

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

	  printf("\nBattlefield created.\n");
	  printf("Battlefield size:%dx %d\n",battlefieldSize,battlefieldSize );
	   printf("Battleship position:(%d,%d)\n",battleshipX, battleshipY);
	}
		   else if (choice == 2)
		   {
	    printf("\n---Instructions---\n");
	    printf("The Battleship (B) attacks Escort Ships (E).\n"); printf("The objective is to destroy as many Escort Ships as possible.\n");
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
         
         	
