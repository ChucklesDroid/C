#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>  
#include <string.h> 
#define size 100 

int isEmpty(); 
int isFull(); 
void push(char); 
char pop(); 
void display(); 
int is_operator(char symbol); 
int precedence(char symbol); 
void InfixToPostfix(char infix_exp[], char postfix_exp[]); 
void InfixToPrefix(char infix_exp[], char prefix_exp[]); 
void evaluatePostfix(char *e); 
int top = -1; 
char infix[size]; 
char postfix[size]; 
char prefix[size]; 
char sStack[size]; 
void main() 
{ 
  int iChoice, res; 
  char cVal, cChoice; 
  do{ 
      printf("\n\t\t STACK MENU:"); 
      printf("\n\t1. Convert infix to postfix expression"); 
      printf("\n\t2. Convert infix to prefix expression"); 
      printf("\n\t3. Evaluate postfix expression"); 
      printf("\n\t4. EXIT"); 
      printf("\n Enter your choice(1-4): "); 
      scanf("%d", &iChoice); 
      switch(iChoice) 
      { 
        case 1: 
                    { 
                      printf("\n Enter Infix expression : "); 
                      fflush(stdin); 
                      gets(infix); 
                      InfixToPostfix(infix,postfix); 
                      printf("\n Postfix Expression: "); 
                      puts(postfix); 
                      break; 
                    } 
        case 2: 
                    { 
                      printf("\n Enter Infix expression : "); 
                      fflush(stdin); 
                      gets(infix); 
                      InfixToPrefix(infix,prefix); 
                      printf("\n Prefix Expression: "); 
                      puts(prefix); 
                      break; 
                    } 
        case 3:    { 
                      printf("\n Enter Postfix expression : "); 
                      fflush(stdin); 
                      gets(postfix); 
                      evaluatePostfix(postfix); 
                      printf("\n Postfix Evaluation: %d",pop()); 
                      break; 
                    }
        case 4:    exit(0); 
               break;
        default:   printf("\n Wrong Choice!!"); 
        } 
    printf("\n\n Do you wish to continue(y/n): "); 
    fflush(stdin); 
    scanf("%c", &cChoice); 
    }while (cChoice == 'y' || cChoice == 'Y'); 
} 

 

int isEmpty() 
{ 
   if(top==-1) 
      return 1; 
   else 
      return 0; 
} 

 

int isFull() 
{ 
   if(top==size-1) 
      return 1; 
   else 
      return 0; 
} 

 

void push(char cVal) 
{ 
   if(isFull()) 
      printf("\n Stack is full!!"); 
   else 
   { 
      top = top + 1; 
      sStack[top] = cVal; 
   } 
} 

 

char pop() 
{ 
   char cTemp; 
   if(isEmpty()) 
   { 
      cTemp = ' '; 
   } 
   else 
   { 
      cTemp = sStack[top]; 
      top = top - 1; 
   } 
   return cTemp; 
} 

 

int is_operator(char symbol) 
{ 
    if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-') 
    { 
        return 1; 
    } 
    else 
    { 
        return 0; 
    } 
} 

 

int precedence(char symbol) 
{ 
    if(symbol == '^') 
    { 
        return(3); 
    } 
    else if(symbol == '*' || symbol == '/') 
    { 
        return(2); 
    } 
    else if(symbol == '+' || symbol == '-') 
    { 
        return(1); 
    } 
    else 
    { 
        return(0); 
    } 
} 

void InfixToPostfix(char infix_exp[], char postfix_exp[]) 
{ 
    int i, j; 
    char item; 
    char x; 
    push('('); 
    strcat(infix_exp,")"); 
    i=0; 
    j=0; 
    item=infix_exp[i]; 
    while(item != '\0') 
    { 
        if(item == '(') 
        { 
            push(item); 
        } 
        else if( isdigit(item) || isalpha(item)) 
        { 
            postfix_exp[j] = item; 
           j++; 
        } 
        else if(is_operator(item) == 1) 
        { 
            x=pop(); 
            while(is_operator(x) == 1 && precedence(x)>= precedence(item)) 
            { 
                postfix_exp[j] = x; 
                j++; 
                x = pop(); 
            } 
            push(x); 
            push(item); 
        } 
        else if(item == ')') 
        { 
            x = pop(); 
            while(x != '(') 
            { 
                postfix_exp[j] = x; 
                j++; 
                x = pop(); 
            } 
        } 
        else 
        { 
            printf("\nInvalid infix Expression.\n"); 
            exit(1); 
        } 
        i++; 
        item = infix_exp[i]; 
    } 
    postfix_exp[j] = '\0'; 
} 

void InfixToPrefix(char infix_exp[], char prefix_exp[]) 
{ 
    int i, j, k, pos, len; 
    char item, x, rev[size]; 
    // Reverse the infix expression 
    pos=0; 
    len=strlen(infix_exp); 
    for(k=len-1;k>=0;k--) 
    { 
       rev[pos]=infix_exp[k]; 
       pos++; 
    } 
    rev[pos]='\0'; 
    strcpy(infix_exp,rev); 
    // Make Every “ ( ” as “ ) ” and every “ ) ” as “ ( ” 
    for(i=0; infix_exp[i]!='\0'; i++) 
    { 
       if(infix_exp[i] == ')') 
       infix_exp[i] = '('; 
       else if(infix_exp[i] == '(') 
       infix_exp[i] = ')'; 
    } 
   //Convert expression to postfix form. 
   push('('); 
   strcat(infix_exp,")"); 
   i=0; 
   j=0; 
   item=infix_exp[i]; 
   while(item != '\0') 
   { 
      if(item == '(') 
      { 
     push(item); 
      } 
     else if( isdigit(item) || isalpha(item)) 
      { 
     // Add operand symbol to postfix expression 
     prefix_exp[j] = item; 
     j++; 
      } 
      else if(is_operator(item) == 1) 
      { 
     // pop all higher precendence operator and add them to postfix expresion 
     x=pop(); 
     while(is_operator(x) == 1 && precedence(x)>= precedence(item)) 
     { 
       prefix_exp[j] = x; 
       j++; 
       x = pop(); 
     }
     // push the last pop oprerator symbol onto stack 
     push(x); 
     push(item); 
      } 
      // if current symbol is ')' then pop and keep popping until '(' encounterd 
      else if(item == ')') 
      { 
     x = pop(); 
     while(x != '(') 
     { 
        prefix_exp[j] = x; 
        j++; 
        x = pop(); 
     } 
      }
      else 
      { 
     printf("\nInvalid infix Expression.\n"); 
     break; 
      } 
      i++; 
      // Go to next symbol of infix expression 
      item = infix_exp[i]; 
    } 
    if(top > 0) 
    printf("\n Invalid infix Expression."); 
    prefix_exp[j] = '\0'; 
    // Reverse the prefix expression. 
    pos=0; 
    len=strlen(prefix_exp); 
    for(k=len-1;k>=0;k--) 
    { 
       rev[pos]=prefix_exp[k]; 
       pos++; 
    } 
    rev[pos]='\0'; 
    strcpy(prefix_exp,rev); 
} 

 

void evaluatePostfix(char *e) 
{ 
    int num, n1, n2, n3; 
    e = postfix; 
    while(*e != '\0') 
    { 
    if(isdigit(*e)) 
    {
        num = *e - 48; 
        push(num); 
    } 
    else 
    { 
        n1 = pop(); 
        n2 = pop(); 
        switch(*e) 
        { 
        case '+': 
        { 
        n3 = n1 + n2; 
        break; 
        }
        case '-': 
        { 
        n3 = n2 - n1; 
        break; 
        } 
        case '*': 
        { 
        n3 = n1 * n2; 
        break; 
        } 
        case '/': 
        { 
        n3 = n2 / n1; 
        break; 
        } 
        } 
        push(n3); 
    } 
    e++; 
    } 
} 