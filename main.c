#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 30

int main()
{
  char name[SIZE],surname[SIZE],group[SIZE];
  double x1, x2, y, delta, bin, **A; // оголошуємо змінні
  int step,N;

  FILE* input=fopen("txt.txt", "r"); // читання текстового документа
  FILE* output=fopen("txt-out.txt", "w");
  FILE* binary=fopen("binary.txt", "w+b");
  fscanf(input,"%lf %lf %d %lf", &x1, &x2, &step, &delta);

  fgets(name,SIZE, input); // читання строки з іменем
  fgets(surname,SIZE, input); // читання строки з прізвищем
  fgets(group,SIZE, input); //читання строки з №групи

    if (step==0)
    {
        step=((x2-x1)/delta)+1;
    }
    else if (delta==0)
    {
        delta=(x2-x1)/(step-1);
    }
    fclose(input);
    fprintf(output,"\n   N      X          F(X)           "); // вивід в текстовий документ таблиці

    fwrite(&step, sizeof(int), 1, binary);

    for(int i=0; i<step; i++)

    {
     y= ((x1+125),3)-45*x1-18;  // обчислення функції
     fprintf(output, "\n\t|%d| %.2lf\t|%.2lf\t|",i,x1,y);
     fwrite(&x1, sizeof(double), 1, binary);
     fwrite(&y, sizeof(double), 1, binary);
     x1+=delta;
    }

    fprintf(output,"\n%s %s %s", group, name, surname); // вивід в текстовий документ номер групи, ім'я та прізвище
    fclose(output);
    fclose(binary); // закриття документа

    binary = fopen("binary.txt", "r+b"); // відкриття бінарного документа
    printf("  N        X        F(x)    \n\n");
    fread(&N, sizeof(int), 1, binary);

    A=(double**)malloc(3*sizeof(double*));
    for(int i=0; i<3; i++)
    {
        A[i]=(double*)malloc(N*sizeof(double)); // перетворення інформації в бінарний код
    }
  for(int i=0; i<N; i++)
   {
    printf("\n|%d|", i);
    for(int j=1; j<3; j++)
   {
     fread(&bin, sizeof(double), 1, binary);
     A[j][i] = bin;
     printf("\t|%.2lf\t| ", A[j][i]); // вивід на екран
    }
 }
  fclose(input);
  fclose(output);
  fclose(binary); // закриття документів
}
