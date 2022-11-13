#include <stdio.h>
#include <stdlib.h>

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
int main(int argc, char * argv[]) {
  if(argc != 3){
      printf("incorrect input\n");
      return 0;
  }
  FILE *input = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  if((input == NULL) || (out == NULL)){
      printf("incorrect file\n");
      return 0;
  }
  int len, test; 
  char *s = get_string(input, &len, &test); 
  if(test == 0){
      task(out, s, len);
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