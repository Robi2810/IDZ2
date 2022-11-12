#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char *get_string(FILE *input, int *len, int *test) {
    *len = 0; 
    *test = 0;
    int capacity = 1; 
    char *s = (char*) malloc(sizeof(char)); 
    char c = fgetc(input);
    if(c > 127){
      (*test)++;
    }  
    while (c != EOF) {
        s[(*len)++] = c; 
        if (*len >= capacity) {
            capacity *= 2; 
            s = (char*) realloc(s, capacity * sizeof(char)); 
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
    int capacity = 1; 
    char *s = (char*) malloc(sizeof(char)); 
    char c = getchar();
    if(c > 127){
      (*test)++;
    }  
    while (c != '\n') {
        s[(*len)++] = c; 
        if (*len >= capacity) {
            capacity *= 2; 
            s = (char*) realloc(s, capacity * sizeof(char)); 
        }

        c = getchar();
	if(c > 127){
          (*test)++;
        }          
    }
    s[*len] = '\0'; 
    return s; 
}
void change(FILE *out, char *s, int len){
  for(int j = 0; j < 100000 - 1;j++){
    for(int i = 0; i < len;i++){
      if((s[i] >= 65) && (s[i] <= 90)){
        s[i] = s[i] + 32;
      }
      else if((s[i] >= 97) && (s[i] <= 122)){
        s[i] = s[i] - 32;
      }
      else if((s[i] == EOF)){
        break;
      }
      else{
        s[i] = s[i];
      }
    }
  }
}
void change2(char *s, int len){
  for(int j = 0; j < 100000 - 1;j++){
    for(int i = 0; i < len;i++){
      if((s[i] >= 65) && (s[i] <= 90)){
        s[i] = s[i] + 32;
      }
      else if((s[i] >= 97) && (s[i] <= 122)){
        s[i] = s[i] - 32;
      }
      else if((s[i] == '\0') || (s[i] == '\n')){
        break;
      }
      else{
        s[i] = s[i];
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
  clock_t start, end;
  int len, test;
  if(strcmp(argv[1], "-r") == 0){
    char *s = get_random_string(&len);
    printf("%s \n %d \n", s, len);
    start = clock();
    change2(s, len);
    end = clock();
    printf("%s\n", s);
    printf("time: %.4lf\n", (double)(end-start)/(CLOCKS_PER_SEC));
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
    int len; 
    char *s = get_string(input, &len, &test);
    start = clock(); 
    change(out, s, len);
    end = clock();
    fprintf(out, "%s\n", s); 
    printf("time: %.4lf\n", (double)(end-start)/(CLOCKS_PER_SEC));
    free(s); 
    fclose(input);
    fclose(out);
  }
  else if((strcmp(argv[1], "-s") == 0)){
    char *s = get_string2(&len, &test); 
    start = clock();
    change2(s, len);
    end = clock();
    printf("%s\n", s); 
    printf("time: %.4lf\n", (double)(end-start)/(CLOCKS_PER_SEC));
    free(s);
  }
  return 0;
}