#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include <errno.h>


int semester_fee=24000;
char user;//which user


struct details{
int bus_number;	
char route[200];
char busdriver[100];
long int drivercontact;
char seat[32][14];	
};


void login(void);
void bus(void);//installing new bus
void record(void);//displaying existing buses
void update_pass(void);// setting new password
void delete_record(void);//deleting a bus
void reservation(void);//reserving a seat number
void cancel(void);//cancel reservation
void exit(void);//exit system
void admin(void);//admin console
void student(void);//student console


int main(){
	
	
	system("COLOR F8");
	printf("\n\t\t\t-----WELCOME TO POINT MANAGEMENT SYSTEM-----");
	printf("\n\n\tPress 'A' for accessing admin options and 'S' for accessing student/passenger options : ");
	scanf(" %c", &user);
	system("cls");
	
	switch(user){
		case 'a':
		case 'A':
		login();
		system("cls");
		admin();
		break;
		
	
		case 's':
		case 'S':
        student();
		break;
  }
	
	
	return 0;
}

void admin(){
	int choice;
	do{	
		printf("\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n");
		printf("\n\t\t[1] Install new bus\n");
		printf("\n\t\t[2] View Bus Details\n");
		printf("\n\t\t[3] Delete Bus Record\n");
		printf("\n\t\t[4] Update password\n");
		printf("\n\t\t[5] Exit ");
		printf("\n\n\t\t");
		scanf("%d", &choice);
		system("cls");
		
		switch(choice){
			case 1: bus();
			break;
			case 2: record();
			break;
			case 3: delete_record();
			break;
			case 4: update_pass();
			break;
			case 5: exit();
			default: printf("Wrong option");
		}}while(choice!=5);
		
}

void student(){
	int choice;
			do{	
		printf("\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n");
		printf("\n\t\t[1] View Bus Details\n");
		printf("\n\t\t[2] Seat Reservation\n");
		printf("\n\t\t[3] Cancel Booking\n");
		printf("\n\t\t[4] Exit ");
		printf("\n\n\t\t");
		scanf("%d", &choice);
		system("cls");
		
	switch(choice){
		    case 1: record();
		    break;
		    case 2: reservation();
		    break;
		    case 3: cancel();
		    break;
			case 4: exit();
			break;
			default: printf("Wrong option");
				
		}}while(choice!=4);
}


int count=0;
void login(){
	system("cls");
		printf("\n\t\t\t-------LOGIN FORM-------");
	char array[3][20], pass[20], user[20], sign_name[20], sign_pass[20], ch, c;
	int result_name, result_pass, option;
	FILE*fptr;
	
printf("\n\n\t\t\tSelect a number:\n");
printf("\n\t\t\t 1. Register\n");
printf("\n\t\t\t 2. Sign in\n");
printf("\n\t\t\tYour choice: ");
scanf("%d", &option);

//REGISTRATION
if(option==1){
	//checking if a user exists
	fptr=fopen("Signin_details.txt", "r+");
		if(fptr!=NULL && (ch=getc(fptr))!=EOF){
			printf("\n\t\t\tA user already exists. Please sign in to the system with your username.\n");
			printf("\n\t\t\tPress any key to continue ... ");
            getch();
            fclose(fptr);
            login();
			}
	
else{
	fptr=fopen("Signin_details.txt", "w+");
	printf("\t\t\tUsername: ");
	fflush(stdin);
	gets(user);
	printf("\t\t\tPassword: ");
	fflush(stdin);
	//taking password in sterics
	
	int i=0;
	while(i<20)
	{
	    pass[i]=getch();
	    c=pass[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pass[i]='\0';
	
	printf("\n\t\t\t\tYou have successfully registered!");
	fprintf(fptr, "%s\n%s\n", user, pass);
	fclose(fptr);
	
	printf("\n\t\t\tPress any key to continue ... ");
    getch();
    
    bus();//calling bus function to input some bus data on the first registration
}
    
	
}

if(option==2){
	
	//SIGN-IN
	fptr=fopen("Signin_details.txt", "r+");
	if((ch=getc(fptr))==EOF) {printf("\n\t\t\tPlease register yourself first\n");
	printf("\n\t\t\tPress any key to continue...");
	getch();
	login();}
	else{
	printf("\n\t\t\tUsername: ");
	fflush(stdin);//refresh
	gets(sign_name);
	printf("\n\t\t\tPassword: ");
	fflush(stdin);
	
	int a=0;
	while(a<20)
	{
	    sign_pass[a]=getch();
	    c=sign_pass[a];
	    if(c==13) break;
	    else printf("*");
	    a++;
	}
	sign_pass[a]='\0';

int i=0;
rewind(fptr);
while(!feof(fptr)){
fgets(array[i], sizeof(array[i]), fptr);
i++;}
strcat(sign_name, "\n"); //fgets takes null character in string too
strcat(sign_pass, "\n");

	
	result_name=strcmp(array[0], sign_name);
	result_pass=strcmp(array[1], sign_pass);	
	
	
	if(result_pass!=0 || result_name!=0){
		    count++;
		    if(count==3){
		    	printf("\n\t\t\t3 wrong attempts on credentials.");
		    	exit(0);
			}
			printf("\n\t\t\tWrong attempts on credentials.");
			getch();
			login();
	}

else if(result_name==0 && result_pass==0) printf("\n\t\t\tWelcome user %s", array[0]);
	getch();}}
fclose(fptr);}

void update_pass(void){//updating PASSWORD
	
	system("cls");
	char array[3][20],sign_name[20], sign_pass[20],new_pass[20],username[20];
	int result_name, result_pass, option;
	FILE*fptr;
	
	fptr=fopen("Signin_details.txt", "r+");
	rewind(fptr); //sets pointer back to start of file
	
	printf("\n\t\t\tEnter Username: ");
	fflush(stdin);//refresh
	gets(sign_name);
	strcpy(username,sign_name);
	printf("\t\t\tEnter previous Password: ");
	fflush(stdin);
	gets(sign_pass);
	
	int i=0;
	rewind(fptr);
	while(!feof(fptr)){
	fgets(array[i], sizeof(array[i]), fptr);
	i++;}
	strcat(sign_name, "\n");
	strcat(sign_pass, "\n");
	
	result_name=strcmp(array[0], sign_name);
	result_pass=strcmp(array[1], sign_pass);	

	if(result_name==0 && result_pass==0) {
	
	fptr=fopen("Signin_details.txt", "w+");
		printf("\n\t\t\tEnter new password: ");
		fflush(stdin);
		gets(new_pass);

		printf("\n\t\t\tPassword updated!\n\n");
		fprintf(fptr, "%s\n%s\n", username, new_pass);
		fclose(fptr);
	}
	else{
		printf("\n\t\t\tWrong username or password");
		printf("\n\t\t\tPlease enter correct Information ");
		getch();
		update_pass();
	
	}
	fclose(fptr);
}


void bus(void){

system("cls");
FILE *bptr;
int no;
printf("Enter the number of points you want to add: ");
scanf("%d", &no);
struct details array[no];
int busno;
FILE* fptr[no];
FILE* ptr[no];
char buffer[11];
char bus[99999][6]; long int exist[99999];
char string3[11];

for(int i=0; i<no; i++){
printf("Enter the point number: ");
scanf("%d", &busno);
sprintf(string3, "%d_num.txt", busno);
ptr[i]=fopen(string3, "w+");
fprintf(ptr[i], "32");
fclose(ptr[i]);
bptr=fopen("buses.txt", "a+");

//Comparing the bus number first with the buses that the user already entered
for(int j=0; j<i; j++){
	if(busno==array[j].bus_number){
	while(busno==array[j].bus_number){
		printf("Point data already exists. Enter another point number: ");
		scanf("%d", &busno);
	}break;}
}

    //Comparing bus number now with the bus numbers already existing in file points.txt
    
    fseek(bptr, 0, SEEK_SET); //sets pointer to beginning of file buses
    int p=0, q=0;	
    while(!feof(bptr)){//reading character by character and storing in array bus
	bus[p][q]=fgetc(bptr);
	if(bus[p][q]==' '){
		bus[p][q]='\0';
		p++;
		q=0;
	}
	else q++;}
	
	
	int r=p;
	for(int s=0; s<r; s++){
	exist[s]=atoi(bus[s]);}//converting the numbers in string form to integer form 
	
	int count=0, s=0;
	for(; ;){
	for(s=0; s<r; s++){
	if(busno==exist[s]){
		count++;
		while(busno==exist[s]){
			printf("Point data already exists. Enter another point number: ");
			scanf("%d", &busno);
		}}}
		if(count==0){
			break;
		}
		else {
		s=0;
		count=0;}}
		fprintf(bptr, "%d ", busno);
        fclose(bptr);
        
	
	//entering data in the bus' .txt file
        array[i].bus_number=busno;
    	sprintf(buffer, "%d.txt", busno);
    	fptr[i]=fopen(buffer, "w+");
    	printf("Enter the point driver's name: ");
    	fflush(stdin);
    	gets(array[i].busdriver);
    	printf("Enter point driver's contact: ");
    	scanf("%ld", &array[i].drivercontact);
    	printf("Enter route of the point: ");
    	fflush(stdin);
    	gets(array[i].route);

fprintf(fptr[i],"Point number: %d\tSemester fee: %d\tPoint Driver's contact number: %ld\tPoint Driver: %s\tRoute: %s\n", busno, semester_fee, array[i].drivercontact, array[i].busdriver, array[i].route);



//Initialises seats to empty
for(int n=0; n<32;n++){
char s2[6]="Empty";
strcpy(array[i].seat[n], s2);}

int l=0;
for(int j=0; j<8; j++){
for(int k=0; k<4; k++){
fprintf(fptr[i], "%2d. %-25s", ++l, array[i].seat[l]);
}
fprintf(fptr[i], "\n");}

fclose(fptr[i]);}

printf("Press any key to continue ... ");
getch();
system("cls");


}

void record(){
	
	FILE*fptr;
	char buffer[11];
	char line[500];
	for(int i=1; i<=99999; i++){
		sprintf(buffer, "%d.txt", i);
		if((fptr= fopen(buffer, "r+"))!=NULL){
	        fgets(line, sizeof(line), fptr);
	        printf("%s\n\n", line);
	        fclose(fptr);
			}
}
getch();
system("cls");}

void delete_record(void){
	
	
	int number;
	char file1[15], file2[15], file3[15], file4[15], bus[99999][6], exist[99999];
	FILE* bptr; FILE*fptr; FILE*file[4];
	
	system("cls");
	record();
	printf("Enter the point number you want to delete records of: ");
	scanf("%d", &number);
	sprintf(file1, "%d.txt", number);
	sprintf(file2, "%d_booked.txt", number);
	sprintf(file3, "%d_names.txt", number);
	sprintf(file4, "%d_num.txt", number);
	
	file[0]=fopen(file1, "r+");
	if(file[0]!=NULL) fclose(file[0]);
	int status=remove(file1);
	if (status) printf("Warning: %s\n", strerror(errno));//shows what error occured
	file[1]=fopen(file2, "r+");
	if(file[1]!=NULL) fclose(file[1]);
	remove(file2);
	file[2]=fopen(file3, "r+");
	if(file[2]!=NULL) fclose(file[2]);
	remove(file3);
	file[3]=fopen(file4, "r+");
	if(file[3]!=NULL) fclose(file[3]);
	remove(file4);
	printf("Records successfully deleted!\n");
	
	bptr=fopen("buses.txt", "r+");
	fseek(bptr, 0, SEEK_SET); //sets pointer to beginning of file buses
    int p=0, q=0;	
    while(!feof(bptr)){
	bus[p][q]=fgetc(bptr);
	if(bus[p][q]==' '){
		bus[p][q]='\0';
		p++;
		q=0;
	}
	else q++;}
	fclose(bptr);
	
	int r=p;
	for(int i=0; i<r; i++){
	exist[i]=atoi(bus[i]);
	if(exist[i]!=number){
		fptr=fopen("temp_bus.txt", "a+");// storing bus numbers in new file and not storing the unwanted number, then renaming the temp file back to buses
		fprintf(fptr, "%d ", exist[i]);
		fclose(fptr);
	}}

	remove("buses.txt");
	rename("temp_bus.txt", "buses.txt");
	system("cls");
}

	

void reservation(){
		int seats[32];
	FILE*fptr; FILE* fptr2; FILE*temporary;
	FILE* ptr; FILE*ptr2;
	char line[200], line1[200], line2[3], buffer[11];;
	int num, no_seats;
	int seat_num;
	char new_name[20], file[13], file2[13];
	char number[32][3], name[32][20], string[3], string3[11];
	record();
	printf("Choose the point number you want to have a seat in: ");
	scanf("%d", &num);
	system("cls");
	
	sprintf(string3, "%d_num.txt", num);//puts the num in place of %d
	
	fptr2=fopen(string3, "r+");
	fgets(line2, 3, fptr2);
	no_seats=atoi(line2);//converts string to number
	fclose(fptr2);
	
	
	
	if(no_seats==0){
		printf("No seats available\n");
	}
	else if(no_seats==32){
	char temp[33][20]={"Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty","Empty" ,"Empty"};
	
	printf("Available seats: %d\n", no_seats);	
	fptr2=fopen(string3, "w+");
	no_seats-=1;
	fprintf(fptr2, "%d", no_seats);
	fclose(fptr2);
		
			sprintf(buffer, "%d.txt", num);
	        fptr= fopen(buffer, "r+");
	
	for(int i=1; i<=9; i++){ 
		fgets(line1, sizeof(line1), fptr);
		if(i>=2){
		printf("%s\n", line1);}}
		fclose(fptr);
	printf("Please enter the seat number you want: ");
	scanf("%d", &seat_num);
	
	if(seat_num>32){
		student();
	}
	
else{
	printf("Please enter your name: ");
	fflush(stdin);
	gets(new_name);
	
	sprintf(file, "%d_booked.txt", num);
	sprintf(file2, "%d_names.txt", num);
	ptr=fopen(file,"a+");
	ptr2=fopen(file2, "a+");
	if (ptr2 == NULL)
    {
        printf("Could not Access File.");}
		
	fprintf(ptr, "%d\n", seat_num);
	fprintf(ptr2, "%s\n", new_name);
fclose(ptr);
fclose(ptr2);

strcpy(temp[seat_num], new_name);

	fptr= fopen(buffer, "r+");
	rewind(fptr);
	temporary=fopen("temp.txt", "a+");
		fgets(line, 200, fptr);
		fprintf(temporary, "%s", line);
		
	int l=1;
	for(int j=0; j<8; j++){
	for(int k=0; k<4; k++){
fprintf(temporary, "%2d. %-25s\t", l, temp[l]);
l++;
}
fprintf(temporary, "\n");}
fclose(fptr);
fclose(temporary);
remove(buffer);
rename("temp.txt", buffer);

printf("\n\n\n\t\tSeat reserved! Please submit your fee of %d to the accounts office.", semester_fee);
	}}
	
	
	else {
	char temp[33][20]={'\0'};
    printf("Available seats: %d\n", no_seats);
	
	
	sprintf(buffer, "%d.txt", num);
	fptr= fopen(buffer, "r+");
	for(int i=1; i<=9; i++){ 
		fgets(line1, sizeof(line1), fptr);
		if(i>=2){
		printf("%s\n", line1);}}
		fclose(fptr);
	printf("Please enter the seat number you want: ");
	scanf("%d", &seat_num);
	
	if(seat_num>32){
		student();
	}
	
	else{
	printf("Please enter your name: ");
	fflush(stdin);
	gets(new_name);
	
	sprintf(file, "%d_booked.txt", num);
	sprintf(file2, "%d_names.txt", num);
	ptr=fopen(file,"a+");
	ptr2=fopen(file2, "a+");
	
	
int i=0, j=0;
while(!feof(ptr2)){
	name[i][j]=fgetc(ptr2);
	if(name[i][j]=='\n'){
		name[i][j]='\0';
		i++;
		j=0;
	}
	else j++;}

i=0, j=0;	
while(!feof(ptr)){
	number[i][j]=fgetc(ptr);
	if(number[i][j]=='\n'){
		number[i][j]='\0';
		i++;
		j=0;
	}
	else j++;}
	
	
	int m=i;
	
    
    
	for(int i=0; i<m; i++){
	seats[i]=atoi(number[i]);
}
		



	for(int i=0; i<m; i++){
	if(seat_num==seats[i]){
	while(seat_num==seats[i]){
		printf("Seat booked. Enter another seat number: \n");
		scanf("%d", &seat_num);
	}}}
	
	
	
	
	
	
	fprintf(ptr, "%d\n", seat_num);
	fprintf(ptr2, "%s\n", new_name);
fclose(ptr);
fclose(ptr2);
	
	//decrement a seat
	fptr2=fopen(string3, "w+");
	no_seats-=1;
	fprintf(fptr2, "%d", no_seats);
	fclose(fptr2);
	
	
	
	
	
	
	ptr=fopen(file,"r+");
	ptr2=fopen(file2, "r+");
	
	
i=0, j=0;
while(!feof(ptr2)){
	name[i][j]=fgetc(ptr2);
	if(name[i][j]=='\n'){
		name[i][j]='\0';
		i++;
		j=0;
	}
	else j++;}

i=0, j=0;	
while(!feof(ptr)){
	number[i][j]=fgetc(ptr);
	if(number[i][j]=='\n'){
		number[i][j]='\0';
		i++;
		j=0;
	}
	else j++;}
	 
	
	fclose(ptr);
	fclose(ptr2);
	
	 m=i;

    
    
	for(int i=0; i<m; i++){
	seats[i]=atoi(number[i]);}
	

	for(int n=1; n<=32; n++){
		for(int o=0; o<m; o++){
			if(n==seats[o]){
				strcpy(temp[n], name[o]);
				break;
			}
			else strcpy(temp[n], "Empty");}
	}
	fptr= fopen(buffer, "r+");
	temporary=fopen("temp.txt", "a+");
		fgets(line, 200, fptr);
		fprintf(temporary, "%s", line);
		
	int l=1;
	for(int j=0; j<8; j++){
	for(int k=0; k<4; k++){
fprintf(temporary, "%2d. %-25s\t", l, temp[l]);
l++;
}
fprintf(temporary, "\n");}
fclose(fptr);
fclose(temporary);
remove(buffer);
rename("temp.txt", buffer);
printf("\n\n\n\t\tSeat reserved! Please submit your fee of %d to the accounts office.", semester_fee);
}}
}

void cancel(){
	
	system("cls");
	char temp[33][20]={'\0'};
	int seats[32];
	FILE*bptr; FILE* fptr1; FILE* fptr2; FILE* fptr3; FILE*temporary;
	FILE* ptr; FILE*ptr2;
	char line[200], line1[200], line3[3], buffer[11];
	int seat_num, num, no_seats;
	char file[13], file2[13], file3[13];
	char number[32][3], name[32][20], string3[11];
	record();
	printf("Please enter your point number: ");
	scanf("%d", &num);
	system("cls");
	
	sprintf(buffer, "%d.txt", num);
	        bptr= fopen(buffer, "r+");
	for(int i=1; i<=9; i++){ 
		fgets(line1, sizeof(line1), bptr);
		if(i>=2){
		printf("%s\n", line1);}}
		fclose(bptr);
	printf("Please enter the seat number you had: ");
	scanf("%d", &seat_num);
	
	sprintf(file, "%d_booked.txt", num);
	sprintf(file2, "%d_names.txt", num);
	ptr=fopen(file,"r+");
	ptr2=fopen(file2, "r+");
	
	
int i=0, j=0;
while(!feof(ptr2)){
	name[i][j]=fgetc(ptr2);
	if(name[i][j]=='\n'){
		name[i][j]='\0';
		i++;
		j=0;
	}
	else j++;}

i=0, j=0;	
while(!feof(ptr)){
	number[i][j]=fgetc(ptr);
	if(number[i][j]=='\n'){
		number[i][j]='\0';
		i++;
		j=0;
	}
	else j++;}
	int m=i;
	for(int i=0; i<m; i++){
	seats[i]=atoi(number[i]);}
	
	fclose(ptr);
	fclose(ptr2);
	
	
	fptr1=fopen("temp_name.txt", "a+");
	fptr2=fopen("temp_booked.txt", "a+");
	
for(int n=1; n<=32; n++){
		for(int o=0; o<m; o++){
			if(n==seat_num){
				strcpy(temp[n], "Empty");
				break;
			}
			else if(n==seats[o]){
				strcpy(temp[n], name[o]);
				fprintf(fptr1, "%s\n", name[o]);
				fprintf(fptr2, "%d\n", seats[o]);
				break;
			}
			else strcpy(temp[n], "Empty");}
	}
	
	
	fclose(fptr1);
	fclose(fptr2);

	int status=remove(file);
	if (status) printf("Warning: %s\n", strerror(errno));
	 status=remove(file2);
	if (status) printf("Warning: %s\n", strerror(errno));
	
	rename("temp_name.txt", file2);
	rename("temp_booked.txt", file);
	
	bptr= fopen(buffer, "r+");
	temporary=fopen("temp.txt", "a+");
		fgets(line, 200, bptr);
		fprintf(temporary, "%s", line);
		
	int l=1;
	for(int j=0; j<8; j++){
	for(int k=0; k<4; k++){
fprintf(temporary, "%2d. %-25s\t", l, temp[l]);
l++;
}
fprintf(temporary, "\n");}
fclose(bptr);
fclose(temporary);
remove(buffer);
rename("temp.txt", buffer);

sprintf(file3, "%d_num.txt", num);
fptr3=fopen(file3, "r+");
fgets(line3, 3, fptr3);
	no_seats=atoi(line3);//converts string to number
	fclose(fptr3);

fptr3=fopen(file3, "w+");
no_seats+=1;
fprintf(fptr3, "%d", no_seats);
fclose(fptr3);


}

 
void exit(){
	system("cls");
	printf("\n\t\t\tThank you for using the Point registration system!");
	exit(0);
}
