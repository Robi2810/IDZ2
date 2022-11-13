#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char *get_string(FILE *input, int *len, int *test) {
    *len = 0; 
    *test = 0;
    int cp = 1; 
    char *s = (char*) malloc(sizeof(char)); 
    char c = fgetc(input);
    if(c > 127){
      (*test)++;
    }  
    while (c != EOF) {
        s[(*len)++] = c; 
        if (*len >= cp) {
            cp *= 2; 
            s = (char*) realloc(s, cp * sizeof(char)); 
        }

        c = fgetc(input);
	if(c > 127){
          (*test)++;
        }          
    }
    s[*len] = '\0'; 
    return s;
}
char *get_string2(int *len, int *test) {
    *len = 0; 
    *test = 0;
    int cp = 1; 
    char *s = (char*) malloc(sizeof(char)); 
    char c = getchar();
    if(c > 127){
      (*test)++;
    }  
    while (c != '\n') {
        s[(*len)++] = c; 
        if (*len >= cp) {
            cp *= 2; 
            s = (char*) realloc(s, cp * sizeof(char)); 
        }

        c = getchar();
	if(c > 127){
          (*test)++;
        }          
    }
    s[*len] = '\0'; 
    return s; 
}
void task(FILE *out, char *s, int len){
	
	    for(int i = 0; i < len;i++){
		if((s[i] == (66) || s[i] == (67) || s[i] == (68) || s[i] == (70) || s[i] == (71) || s[i] == (72) || s[i] == (74) || s[i] == (75) || s[i] == (76) || s[i] == (77) || s[i] == (78) || s[i] == (80) || s[i] == (82) || s[i] == (83) || s[i] == (84) || s[i] == (86) || s[i] == (87) || s[i] == (88) || s[i] == (90)) || (s[i] == (66+32) || s[i] == (67+32) || s[i] == (68+32) || s[i] == (70+32) || s[i] == (71+32) || s[i] == (72+32) || s[i] == (74+32) || s[i] == (75+32) || s[i] == (76+32) || s[i] == (77+32) || s[i] == (78+32) || s[i] == (80+32) || s[i] == (82+32) || s[i] == (83+32) || s[i] == (84+32) || s[i] == (86+32) || s[i] == (87+32) || s[i] == (88+32) || s[i] == (90+32))){ 
			fprintf(out, "%d", s[i]);
		}
		else{
		  	fprintf(out, "%c", s[i]);
		}
	    }

}
void task2(char *s, int len){
    for(int j = 0; j <= 100000;j++){
	    for(int i = 0; i < len;i++){
		if(j == 100000){
		  if((s[i] == (66) || s[i] == (67) || s[i] == (68) || s[i] == (70) || s[i] == (71) || s[i] == (72) || s[i] == (74) || s[i] == (75) || s[i] == (76) || s[i] == (77) || s[i] == (78) || s[i] == (80) || s[i] == (82) || s[i] == (83) || s[i] == (84) || s[i] == (86) || s[i] == (87) || s[i] == (88) || s[i] == (90)) || (s[i] == (66+32) || s[i] == (67+32) || s[i] == (68+32) || s[i] == (70+32) || s[i] == (71+32) || s[i] == (72+32) || s[i] == (74+32) || s[i] == (75+32) || s[i] == (76+32) || s[i] == (77+32) || s[i] == (78+32) || s[i] == (80+32) || s[i] == (82+32) || s[i] == (83+32) || s[i] == (84+32) || s[i] == (86+32) || s[i] == (87+32) || s[i] == (88+32) || s[i] == (90+32))){ 
			printf("%d", s[i]);
		  }
		  else{
		  	printf("%c", s[i]);
		  }
		}
	    }
	}
}
char *get_random_string(int *len){
  srand(time(NULL));
  *len = rand()%10000; 
  char *s = (char*) malloc(*len * sizeof(char));
  for(int i = 0; i < *len; i++){
    if(i % 2 == 0){
      s[i] = rand()%26 + 'A';
    }
    else{
      s[i] = rand()%26 + 'a';
    }
  }
  return s; 
}
int main(int argc, char *argv[]) {
  if(argc != 2){
        printf("incorrect input\n");
   	return 0;
  }
  clock_t start, end;
  int len, test;
  if(strcmp(argv[1], "-r") == 0){
    char *s = get_random_string(&len);
    printf("%s \n %d \n", s, len);
    start = clock();
    task2(s, len);
    end = clock();
    printf("\n%d\ntime: %.6lf\n", len, (double)(end-start)/(CLOCKS_PER_SEC));
    free(s);
  }
  else if(strcmp(argv[1], "-h") == 0){
    printf("-h help\n");
    printf("-r create random string\n");
    printf("-f use string from input.txt and save result in output.txt\n");
    printf("-s take string from terminal and print result in terminal\n");
  }
  else if(strcmp(argv[1], "-f") == 0){
    FILE *input = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    if((input == NULL) || (out == NULL)){
      printf("incorrect file\n");
      return 0;
    }
    int len; 
    char *s = get_string(input, &len, &test);
    start = clock(); 
    task(out, s, len);
    end = clock();
    printf("\ntime: %.6lf\n", (double)(end-start)/(CLOCKS_PER_SEC));
    free(s); 
    fclose(input);
    fclose(out);
  }
  else if((strcmp(argv[1], "-s") == 0)){
    char *s = get_string2(&len, &test); 
    start = clock();
    task2(s, len);
    end = clock();
    printf("\ntime: %.6lf\n", (double)(end-start)/(CLOCKS_PER_SEC));
    free(s);
  }
  return 0;
}