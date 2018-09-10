#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gcrypt.h>
#include <unistd.h>

//global variables
/*struct user{
	cha username[6], name[10], surname[10],password[100];
}*/
//argc will be the number of strings pointed to by argv
int main(int argc, char *argv[]){
char *line_pointer=NULL;
char *line_pointer2=NULL;
char *temp_pass=NULL;
char *str;
size_t buffer_length=0;
size_t buffer_length2=0;
ssize_t each_line_pass_file, each_line_shadow_file;
char salt[]="$1$M9";
//char *h_passwords;
char crypt(const char temp_pass,const char *salt);
char val1[20],val2[20],val3[20],pass_extracted[100], user_details[100], password[100];
ssize_t getline();
int j=0;

//setting pointer of type file.
	//ptr=fopen("filename", "mode");
	//or FILE *ptr=fopen("filename", "mode");
	/*for(int i=0;i<argc;i++){
		printf(argv[i]);
		printf(" ");
	}
*/
//argv[1]=password file, argv[2]= shadow file
FILE *read_password_file=fopen(argv[1],"r");

FILE *write_temp_dictionary=fopen("temp_dictionary.txt","w");

while((each_line_pass_file=getline(&line_pointer, &buffer_length,read_password_file))!=-1){
	//scanf - read from standard input device
//sscanf - read from a string
	sscanf(line_pointer,"%s%s%s%s",val1,val2,val3,pass_extracted);
	fputs(pass_extracted, write_temp_dictionary);
	fputc('\n',write_temp_dictionary);
	fflush(stdin);

} //while loop closes 
//write_temp_dictionary is now complete.
fclose(read_password_file);
fclose(write_temp_dictionary);
//make hashed paswords file
FILE *read_temp_dictionary=fopen("temp_dictionary.txt","r");
FILE *hashed_passwords=fopen("hashed_passwords.txt","w");
FILE *retrieved_file=fopen("retrieved_passwords.txt","w");
while(fscanf(read_temp_dictionary, "%s",line_pointer)!=-1){
	
	temp_pass=crypt(line_pointer,salt);
	fputs(temp_pass, hashed_passwords);
	fputc('\n', hashed_passwords);

FILE *read_shadow_file=fopen(argv[2],"r");
	while((each_line_shadow_file=getline(&line_pointer2,&buffer_length2,read_shadow_file))!=-1 ){

		str=strtok(line_pointer2,":");
		while(str!=NULL&& j<2){
			if(j==0){
				sscanf(str, "%s",user_details);
				str=strtok(NULL, ":");
			}

		else if(j==1){
			sscanf(str, "%s", password);
			str=strtok(NULL, ":");
		}
			j++;

		}
		j=0;
		//now comparing the two lists we created.
		if(strcmp(temp_pass,password)==0){
			fputs(user_details,retrieved_file);
			fputc(':', retrieved_file);
			fputs(line_pointer,retrieved_file);
			fputc('\n',retrieved_file)
		}

	}

}
free(line_pointer);
free(line_pointer2);
fclose(read_temp_dictionary);
fclose(hashed_passwords);
fclose(retrieved_file);
fclose(read_shadow_file);
exit(EXIT_SUCCESS);
//freeingresources
//hashed and salted passwords stored in hashed_passwords.txt
}
