#include "../Utils/utils.h"

typedef enum globResult{
  GLOB_UNMATCHED  = 0,
  GLOB_MATCHED    = 1,
  GLOB_SYNTAX_ERROR=2,
}globResult;

typedef struct Glob Glob;
globResult  matchGlob (Glob* glob);
Glob*       createGlob(const char* pattern, const char* text);
void        globe     (const char* pattern, const char* text);

int main(void){
  globe("[]",     "]");
  globe("[][!]",  "[");
  globe("[][!]",  "!");
  globe("[][!]",  "]");
  globe("[A-Fa-f0-9]","A");
  globe("[A-Fa-f0-9]","B");
  globe("[A-Fa-f0-9]","C");
  globe("[A-Fa-f0-9]","a");
  globe("[A-Fa-f0-9]","b");
  globe("[A-Fa-f0-9]","c");
  globe("[A-Fa-f0-9]","1");
  globe("[A-Fa-f0-9]","2");
  globe("[A-Fa-f0-9]","3");
  globe("[A-Fa-f0-9]","-");
  globe("[!![]-]","!");
  globe("[!![]-]","[");
  globe("[!![]-]","]");
  globe("[!![]-]","-");
  globe("\\*","*");

  return 0;
}

struct Glob{
  const char* pattern;
  const char* text;
  int recl;
};

Glob* createGlob(const char* pattern, const char* text){
  Glob* glob  =  calloc(1, sizeof(Glob));
  MEMERR(glob);
  glob->pattern = pattern;
  glob->text  = text;
  glob->recl  = 0;

  return glob;
}

void globe(const char* pattern, const char* text){
  Glob* glob  = createGlob(pattern, text);
  globResult result = matchGlob(glob);
  switch (result) {
    case GLOB_MATCHED:{
      UINFO("%-10s --> %-10s  : MATCHED",  pattern , text);
    }break;
    case GLOB_UNMATCHED:{
      UINFO("%-10s --> %-10s  : FAILED",   pattern , text);
    }break;
    case GLOB_SYNTAX_ERROR:{
      UINFO("%-10s --> %-10s  : SYNTAX ERROR",   pattern , text);
    }
  }

  free(glob);
}

globResult matchGlob(Glob* glob){
  UDEBUG("RECL:  %d", glob->recl);
  ++glob->recl;
  const char* pattern = glob->pattern;
  const char* text    = glob->text;

  while(*pattern  != '\0' && *text  != '\0'){
    UDEBUG("%c  --> %c", *pattern, *text); 
    switch (*pattern) {


      case '?':{
        ++pattern;
        ++text;
      }break;


      case '*':{
        glob->pattern = pattern + 1;
        glob->text    = text;
        globResult result  = matchGlob(glob);
        if(result){
          return GLOB_MATCHED;
        }else{
          ++text;
        }
      }break;

//[][!]
      case '[':{
        ++pattern;//skipping first
        bool matched  = GLOB_UNMATCHED;
        bool negated  = false;

        UASSERT(*pattern != '\0',GLOB_SYNTAX_ERROR, "END OF LINE AFTER '['");
        //negate 
        if(*pattern == '!'){
          negated = true;
          ++pattern;
        }
        UASSERT(*pattern != '\0',GLOB_SYNTAX_ERROR, "END OF LINE AFTER '['");
        //first and prev char
        char prev = *pattern;
        matched |= prev == *text;
        pattern +=1;
        
        while(*pattern != ']' && *pattern != '\0'){
          switch (*pattern) {
            case '-'  :{
              ++pattern;
              switch(*pattern){
                case '\0':{
                  return GLOB_SYNTAX_ERROR;
                }break;
                case ']':{
                  matched |= '-' == *text;
                }break;
                default:{
                  matched |= prev <= *text && *text <= *pattern;
                  prev = *pattern;
                  ++pattern;
                }
              }
            }break;
            default   :{
              prev = *pattern;
              matched |= prev == *text;
              ++pattern;
            } 
          }
        }

        UASSERT(*pattern == ']',GLOB_SYNTAX_ERROR, "INCOMPLETE '['");
        if(negated) matched = !matched;
        if(!matched) return GLOB_UNMATCHED;

        ++pattern;
        ++text;
      }break;


      case '\\' :{
        ++pattern;
        UASSERT(*pattern != '\0', GLOB_SYNTAX_ERROR, "UNFINISHED '\\' AT END");
      }__attribute__ ((fallthrough));//GNU STATEMENT ATTRIBUTES
      //FALLTHROUGH
      default:{
        if(*pattern == * text){
          ++pattern;
          ++text;
        }else{
          --glob->recl;
          UWARN("'%c' not matched in delfault case", *pattern);
          return GLOB_UNMATCHED;
        }
      }

    }//while
  }

  if(*text  ==  '\0'){
    while(*pattern == '*') ++pattern;
    return *pattern == '\0';
  }

  return GLOB_UNMATCHED;
}

