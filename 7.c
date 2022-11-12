#include <stdio.h>
#include <stdlib.h>

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
void change(FILE *out, char *s, int len){
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
int main(int argc, char * argv[]) {
  FILE *input = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  int len, test; 
  char *s = get_string(input, &len, &test); 
  if(test == 0){
      change(out, s, len);
      fprintf(out, "%s", s);
      free(s); 
      fclose(input);
      fclose(out);
      return 0; 
  }
  else{
      fprintf(out, "incorrect input");
      free(s); 
      fclose(input);
      fclose(out);
      return 0;
  } 
}