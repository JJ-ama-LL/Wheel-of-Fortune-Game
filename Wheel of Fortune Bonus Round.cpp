#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

struct Puzzle {
	string category;
	char puzzle[80];
};


int readCategories(string categories[]) {
	ifstream fin;
	int num_categories=0;
	char c[20];
	string category;
	
	fin.open("Categories.txt");
	
	if(!fin.is_open()) {
		cout << "Error Opening Input File 'Categories'\nPlease Try Again\n";
		return 0;
	}
	
	while(!fin.eof()){
		fin.getline(c,20);
		
		category=c;
		if(category != "") {
			categories[num_categories]=category;
		
			num_categories++;
		}
	}
	fin.close();
	
	return num_categories;
}


int readPuzzles(Puzzle puzzles[]) {
	ifstream fin;
	char c[20];
	string category;
	int num_puzzles=0;
	
	fin.open("WOF-Puzzles.txt");
	
	if(!fin.is_open()) {
		cout << "Error Opening Input File 'WOF-Puzzles'\nPlease Try Again\n";
		return 0;
	}
	
	while(!fin.eof()) {
		fin.getline(c,20);
		
		category=c;
		if(category != "") {
			puzzles[num_puzzles].category=category;
			fin.getline(puzzles[num_puzzles].puzzle,80);
			
			num_puzzles++;
		}
	}
	fin.close();
	
	return num_puzzles;
}


int chooseCategory(string categories[],int num_categories) {
	int pos1,pos2,pos3,choice;
	
	pos1=rand()%num_categories;
	cout << "1. " << categories[pos1];
	
	pos2=rand()%num_categories;
	while(pos2==pos1){
		pos2=rand()%num_categories;
	}
	cout << "\n2. " << categories[pos2];
	
	pos3=rand()%num_categories;
	while(pos3==pos1 || pos3==pos2) {
		pos3=rand()%num_categories;
	}
	cout << "\n3. " << categories[pos3];
	
	cout << "\n\nYour Choice? ";
	cin >> choice;
	
	if(choice==1) 
		return pos1;
	else if(choice==2) 
		return pos2;
	else if(choice==3)
		return pos3;
}


void rstlne(char r[],char p[]) {
	int i=0;
	
	cout << "The Puzzle is Now: ";
	while(p[i] != '\0') {
		if(p[i]=='R'||p[i]=='S'||p[i]=='T'||p[i]=='L'||p[i]=='N'||p[i]=='E')
			r[i]=p[i];
			
		i++;
	}
	cout << r;
}


void revealLetter(char r[],char p[],char c) {
	int i=0;
	
	while(p[i]!='\0') {
		if(p[i]==c)
			r[i]=p[i];
		
		i++;
	}
}


bool checkWildcard() {
	int ans;
	
	cout << "\nDo you Have The Wildcard? (0-NO, 1-YES) ";
	cin >> ans;
	
	if(ans==1)
		return true;
	else if(ans==0)
		return false;
}


void toUpperCaseStr(char guess[]) {
	int i=0;
	
	while(guess[i] != '\0') {
		if(guess[i] <= 'z' && guess[i] >= 'a') {
			guess[i]=guess[i]-' ';
		}
		
		i++;
	}
}


void revealPrize() {
	int prize;
	
	prize=1+rand()%25;
	
	if(prize==1)
		cout << "\nIt is......THE JACKPOT OF $100,000.00\n\n";
	else if(prize==2 || prize==3)
		cout << "\nIt is......$45,000.00\n\n";
	else if(prize>=4 || prize<=6)
		cout << "\nIt is......$40,000.00\n\n";
	else if(prize>=7)
		cout << "\nIt is......A New Car\n\n";
}


void solvePuzzle(char r[],char p[]) {
	char c;
	char guess[80];
	int i,compare,tries=3;
	bool card=false,solved=false;
	
	cout << "\n\nRevealing R, S, T, L, N, E...\n\n";
	rstlne(r,p);
	
	cout << "\n\n\nPlease Enter Three Consonants and a Vowel: ";
	for(i=0;i<4;i++) {
		cin >> c;
		
		if(c>='a' && c<='z')
			c=c-' ';
			
		revealLetter(r,p,c);
	}
	
	card=checkWildcard();
	if(card) {
		cout << "\nSince you Have The Wildcard, Please Enter Another Consonant: ";
		cin >> c;
		
		if(c>='a' && c<='z')
			c=c-' ';
		
		revealLetter(r,p,c);
	}
	
	cout << "\nThe Puzzle is Now: " << r;
	
	cout << endl;
	cin.ignore(INT_MAX, '\n');
	while(tries!=0 && solved==false) {
		cout << "\n\nMake a Guess:\n";
		cin.getline(guess,80);
		tries--;
		toUpperCaseStr(guess);
		
		compare=strcmp(guess,p);
		
		if(compare==0) {
			solved=true;
		}
		else {
			cout << "\nSorry. " << guess << " is Not Correct.";
			cout << "\nYou Have " << tries;
			if(tries==1)
				cout << " Try Left.";
			else
				cout << " Tries Left.";
		}  
	}
	
	if(!solved) {
		cout << "\n\nI am Sorry. You will Not get a Prize.";
		cout << "\nThe Puzzle is " << p << ".\n\n";
	}
	else if(solved) {
		cout << "\nCongratulations! You Got it Out!";
		cout << "\nOK, Let's See Your Prize.";
		
		revealPrize();
	}
}


void blankOutPuzzle(char puzzle[]) {
	int i=0;
	char c,revealed[80];
	
	strcpy(revealed,puzzle);
	
	while(revealed[i] != '\0') {
		if(revealed[i] < 'A' || revealed[i] > 'Z')
			cout << revealed[i];
		else {
			cout << "#";
			revealed[i]='#';
		}
			
		i++;
	}
	
	solvePuzzle(revealed,puzzle);
}


void decryptPuzzle(char puzzle[]) {
	int i=0,j;
	
	while(puzzle[i] != '\0') {
		if(puzzle[i] >= 'A' && puzzle[i] <= 'Z') {
			for(j=0;j<5;j++) {
				puzzle[i]=puzzle[i]-1;
				
				if(puzzle[i] < 'A')
					puzzle[i]=puzzle[i]+('Z'-puzzle[i]);
			}
		}
		
		i++;
	} 
}


int choosePuzzle(string categories[],Puzzle puzzles[],int num_puzzles,int choice) {
	int puzzle;
	
	puzzle=rand()%num_puzzles;
	while(categories[choice] != puzzles[puzzle].category) {
		puzzle=rand()%num_puzzles;
	}
	
	return puzzle;
}


int main() {
	string categories[50];
	Puzzle puzzles[1500];
	int num_categories,num_puzzles,choice;
	int puzzle_choice;
	
	srand(time(NULL));
	
	num_categories=readCategories(categories);
	cout << "# of Categories Read from the File: " << num_categories;
	
	num_puzzles=readPuzzles(puzzles);
	cout << "\n\n# of Puzzles Read from the File: " << num_puzzles;
	
	cout << "\n\nPlease Choose from One of the Following Categories:\n\n";
	choice=chooseCategory(categories,num_categories);
	cout << "\nCategory Chosen for Bonus Round is: " << categories[choice];
	
	cout << "\n\n\nThe Puzzle to Start With is: ";
	puzzle_choice=choosePuzzle(categories,puzzles,num_puzzles,choice);
	decryptPuzzle(puzzles[puzzle_choice].puzzle);
	blankOutPuzzle(puzzles[puzzle_choice].puzzle);
	
	return 0;
}
