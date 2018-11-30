#include <stdio.h>
//aaro mäkinen 

char mine_field[10][10];
int cleared = 0;
int mine_count = 0;

int end_game = 9;
int win_game = 10;
int undo = 11;
int empty = 12;			//values for the pointer in function play_game
int open = 13;
int print_m = 14;

void create_mines();
int play_game();					//function prototypes
int minefield(int cord_x, int cord_y, char action);

int main(void){				//mainfunction is used as menu for the game
	char i;
	char answer;
	int new_game = 0;
	char newg_input;
	do{
		printf("                     Minesweeper ultimate v1.69!\nInstructions(i)\nCredits(c)\nPlay the game(p)\nExit(e)\n");
		scanf("%c",&answer);
		while((i=getchar()) != '\n'){} //flushes stdin
		if(answer == 'i' || answer == 'c' || answer == 'p' || answer == 'e'){
			if(answer == 'i'){
				printf("Insert cordinates and don't hit mines. You can mark them with m and unmark with u. You win if you mark all the mines or open all the ones that are not mines.\n");
			}
			if(answer == 'c'){
				printf("The creator is the allmighty\n             Aaro 'zingha' Mäkinen!\n");
			}
			if(answer == 'p'){		//starts the game
				do{	
					do{
						printf("How many mines do you want?(1-99)\n");   //asks how many mines and checks that it's 1-99 because matrix is only 10x10
						scanf(" %d",&mine_count);
						
							
					}while((mine_count >99) || (mine_count <1));
					while((i=getchar()) != '\n'){}
					create_mines();	//initilizes the board where the bombs are
					new_game = play_game();
					printf("\nPlay again(p)\nExit to main menu(e)\n");	//submenu where player can have a new game fast or exit to main menu  
					scanf(" %c",&newg_input);
					while((i=getchar()) != '\n'){} //flushes stdin
					new_game = newg_input-112; //changes char to int
				}while (new_game == 0); 
			}
			if(answer == 'e'){
				printf("Goodbye m8!");
			}
			
		}
		else{
			printf("Wrong input m8!");
		}	
		
	}while(answer != 'e');
		
return 0;
}


int play_game(){
	int i,j,k;
	char board[11][11];
	int pointer = empty;		//used as a link between minefield function and play_game function
	int x,y;
	char action;
	char sure;
	int zeros = 1;
	int marks = 0;
	
	for (i=0;i<11;i++){
                        for(j=0;j<11;j++){		               //initilizes the playing board
                                board[j][i] = '?';
                        }
        }
        for(i=1;i<10;i++){
        	board[0][i+1] = i + '0';
                board[i+1][0] = i + '0';
       	}
	board[0][1] = 'o';
	board[1][0] = 'o';
	board[0][0] = ' ';
	do{
		
		

		for (i=0;i<11;i++){
			for(j=0;j<11;j++){
				printf("%c | ",board[j][i]);		//prints the board after every move
			}
		printf("\n");
		}
		
			printf("What is your next move? Actions available: o = open, m = mark, u = unmark (x-cordinate y-cordinate action)\n");	   //asks for the next move
			scanf(" %d %d %c",&x,&y,&action);
			while((i=getchar()) != '\n'){}	//cleares stdin
			
			if(x>=0 && x<=9 && y>=0 && y<=9 && (action == 'o' || action == 'm' || action == 'u')){   //check if input is correct
				pointer = open;
			}
			else{
			printf("Wrong input m8!");
			}
			x = x+1;		//changes the coordinates from userinterface to actual cell indexes
			y = y+1;
			
			if(action == 'm'){
				if(board[x][y] != '?'){
					
					printf("Can't do that m8!");   //checks that you mark only the ones that hasn't opened and also that you can only mark as much that is the minecount
					pointer = empty;
				}
				if(marks == mine_count){
					printf("max &d marks!",mine_count);
				}				
			}
			
			if(action == 'u'){
				if(board[x][y] != 'm'){
					printf("Can't do that m8!");	//checks that unmark is only used to marked cells
					pointer = empty;
				}
			}
			
			if(action == 'o' && board[x][y] == 'm'){
				printf("Are you sure? It's marked as bomb!! (y/n)");
				scanf(" %c",&sure);
				while((i=getchar()) != '\n'){}
				if(sure == 'y'){
					pointer = open;				//if the asked cell is marked this will ask the user if the intention was to actualy open it
				}
				else if(sure == 'n'){
					pointer = empty;
				}
				else{
					printf("Wrong input m8!");
				}
			}
				
		if(pointer == open){
			pointer = minefield(x,y,action);		//after all checking calls the minefield function to get value
			
			
		}
		if(pointer == print_m){
			board[x][y] = 'm';	//puts mark on playing board and adds marks value to know how many marks there is
			marks++;
		}
		if(pointer >= 1 && pointer <=8){
			board[x][y] = pointer + '0';	//puts minecount of the close by mines as value to the requested cell
		}
		if(pointer == undo){
			board[x][y] = '?';	//changes mark to ? and reduces marks value to know how many marks there is
			marks--;
		}
		if(pointer == 0){
			board[x][y] = '0';	//puts temporarily 0 to the board for checking
			pointer = empty;
		}

	
		//if the close by mines count was 0, the program changes them to space and checks the value for the close by cells and checks that they are not in the borders
		do{
			zeros = 0;
			for (y=1;y<11;y++){
                        	for(x=1;x<11;x++){
                                	if(board[x][y] == '0'){
						board[x][y] = ' ';
						
						zeros = 1;
						if(x != 1 && board[x-1][y]!= ' '){
							board[x-1][y] = (minefield(x-1,y,'o'))+ '0';
							if(y !=1 && board[x-1][y-1]!= ' '){
								
								board[x-1][y-1] = (minefield(x-1,y-1,'o')) + '0';;
							}
							if(y !=10 && board[x-1][y+1]!= ' '){
								board[x-1][y+1] = (minefield(x-1,y+1,'o'))+ '0';;
							}
						}
						if(x != 10 && board[x+1][y]!= ' '){
							board[x+1][y] = (minefield(x+1,y,'o')) + '0';;
							if(y!=1 && board[x+1][y-1]!= ' '){
								 board[x+1][y-1] = (minefield(x+1,y-1,'o')) + '0';;
							}
							if(y!=10 && board[x+1][y+1]!= ' '){
								 board[x+1][y+1] = (minefield(x+1,y+1,'o')) + '0';;
							}
						}
						if(y!=1 && board[x][y-1]!= ' '){
							board[x][y-1] = (minefield(x,y-1,'o')) + '0';;
						}
						if(y!=10 && board[x][y+1]!= ' '){
							 board[x][y+1] = (minefield(x,y+1,'o')) + '0';;
						}
					}
					
				}
			}
		}while (zeros == 1);	//does this until there is no more zeros
		
		k = 0;
		for(i=1;i<11;i++){
                        for(j=1;j<11;j++){		//checks if there are only cells unopened that contain mines if yes changes pointer to win game
                                if(board[i][j] == '?' && mine_field[i-1][j-1] != 'x'){
					k = 1;
				}
			}
		}
		if(k == 0){
			pointer = win_game;
		}
				
			
		 
	}while((pointer != end_game) && (pointer != win_game));  // game plays until pointer value is end_game or win_game 
	
	for(i=0;i<10;i++){
                        for(j=0;j<10;j++){
                                if(mine_field[i][j] == 'x'){	//puts the mines on the board as X
					board[i+1][j+1] = 'X';
				}
			}
	}
	for (i=0;i<11;i++){
                        for(j=0;j<11;j++){
                                printf("%c | ",board[j][i]); //prints the board with all the mines 
        		}
        printf("\n");
        }
	if(pointer == win_game){
		printf("		Congratulations! You won the game!\n");
	}
	if(pointer == end_game){
		printf("		You failed...\n");
	}
	
return 0;	//returns to the submenu in main function 
}
void create_mines(){
	int i,j,rand_x,rand_y;	
        for (i=0;i<10;i++){				//fills the minefield array with a
                for(j=0;j<10;j++){	
                        mine_field[j][i] = 'a';
                }
        }


        for(i=0;i<mine_count;i++){
                rand_x = rand() % 10; 
                rand_y = rand() % 10; //calls to get a random number and makes sure that the random numbers are 0-10
		
                if(mine_field[rand_x][rand_y] == 'x'){	//checks that there is not already put mine in those cordinates
                        i--;
                }
                else{
                        mine_field[rand_x][rand_y] = 'x';
                }
        }

}
int minefield(int cord_x, int cord_y, char action){
	int j,i;
	cord_x = cord_x -1;	//changes the array indexes because there is one less row and column than in interface board
	cord_y = cord_y -1;
	int count = 0;
	
	
	// checks if the coordinates are on the border of the matrix and accordingly gets the minecount of close by mines 
	if(cord_x != 0){
		if(mine_field[cord_x-1][cord_y] == 'x'){
		count++;
		}
		if(cord_y != 0){	
			if(mine_field[cord_x-1][cord_y-1] == 'x'){
                		count++;
			}
		}
		if(cord_y != 9){
			if(mine_field[cord_x-1][cord_y+1] == 'x'){
	                	count++;
			}
      	 	}
	}
	if(cord_x != 9){
		if(mine_field[cord_x+1][cord_y] == 'x'){
                	count++;
		}
		if(cord_y !=0){
			if(mine_field[cord_x+1][cord_y-1] == 'x'){
                		count++;
			}
        	}
		if(cord_y !=9){
			if(mine_field[cord_x+1][cord_y+1] == 'x'){
	                	count++;
			}
        	}
	}
	if(cord_y !=0){
		if(mine_field[cord_x][cord_y-1] == 'x'){
                	count++;
		}
        }
        if(cord_y != 9){	
		if(mine_field[cord_x][cord_y+1] == 'x'){
                	count++;
		}
        }

	
	// checks if the desired coordinate was a mine 
	if(action == 'o'){
		if(mine_field[cord_x][cord_y] == 'x'){
			return end_game;
		}
		else{
			return count;
		}	
        }
	// checks if all the mines are marked otherwise just returns value to print mark
	else if(action == 'm'){
		if(mine_field[cord_x][cord_y] == 'x'){
			cleared++;
				if(cleared == mine_count){
				return win_game;
			}
		}
		
	return print_m;
	}
	//checks that if user unmarks marked mine, the mines cleared are adjusted acordingly
	else if(action == 'u'){
		if(mine_field[cord_x][cord_y] == 'x'){
                        cleared--;
                }
	return undo;
	}
		
}


