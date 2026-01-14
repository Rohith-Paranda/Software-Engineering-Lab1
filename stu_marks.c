#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Enum for grades
typedef enum { O, A_P, A, B_P, B, C, D, F } Grade;

//Structure to store student data
typedef struct {
    char roll[9];
    char name[50];
    int minor[5];
    int major[5];
    int sub_total[5];
    Grade sub_grade[5];
    int total;
    float percentage;
} Student;

//Function Prototypes
int roll_check(char roll[]);
int name_check(char name[]);
int marks_check(int minor[], int major[]);
Grade grade_calc(int marks);
const char* grade_to_string(Grade g);
void calculation(Student *s);
void output_display(Student s[], int n);

//MAIN
int main() 
{
    Student s[50];
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        printf("\nStudent %d Details\n", i + 1);
        do 
        {
            printf("Roll Number(25MCMIXX): ");
            scanf("%s", s[i].roll);
        } while (!roll_check(s[i].roll));
        getchar();
        do 
        {
            printf("Name: ");
            fgets(s[i].name, sizeof(s[i].name), stdin);
            s[i].name[strcspn(s[i].name, "\n")] = '\0';
        } while (!name_check(s[i].name));

        do 
        {
            for (int j = 0; j < 5; j++) 
            {
                printf("Subject %d Minor: ", j + 1);
                scanf("%d", &s[i].minor[j]);
                printf("Subject %d Major: ", j + 1);
                scanf("%d", &s[i].major[j]);
            }
        } while (!marks_check(s[i].minor, s[i].major));
        calculation(&s[i]);
    }
    output_display(s, n);
    return 0;
}

//CHECKS
int roll_check(char roll[]) {
    if (strlen(roll) != 8) return 0;

    if (!(roll[0]=='2' && roll[1]=='5' && roll[2]=='M' && roll[3]=='C' && roll[4]=='M' && roll[5]=='I' && roll[6]>='0' && roll[6]<='9' && roll[7]>='0' && roll[7]<='9'))
    {
        printf("ERROR: Enter valid Roll number format\n");
        return 0;
    }
    return 1;
}

int name_check(char name[]) 
{
    if (strlen(name) == 0) 
    {
        printf("ERROR: Name cannot be of length 0\n");
        return 0;
    }
    for (int i = 0; name[i]; i++) 
    {
        if (!((name[i]>='A' && name[i]<='Z') || (name[i]>='a' && name[i]<='z') || name[i]==' '))
        {
            printf("ERROR: Name should not contain numbers or special characters\n");
            return 0;
        }
    }
    return 1;
}

int marks_check(int minor[], int major[]) {

    for (int i = 0; i < 5; i++) 
    {
        if (minor[i] < 0 || minor[i] > 40 ||major[i] < 0 || major[i] > 60)
        {
            printf("ERROR: Marks out of bound, check and re-enter\n");
            return 0;
        }
    }
    return 1;
}

//GRADING
Grade grade_calc(int marks) {
    if (marks >= 90) return O;
    else if (marks >= 85) return A_P;
    else if (marks >= 75) return A;
    else if (marks >= 65) return B_P;
    else if (marks >= 60) return B;
    else if (marks >= 55) return C;
    else if (marks >= 50) return D;
    else return F;
}
const char* grade_to_string(Grade g) 
{
    switch (g) 
    {
        case O: return "O";
        case A_P: return "A+";
        case A: return "A";
        case B_P: return "B+";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        default: return "F";
    }
}
//CALCULATIONS
void calculation(Student *s) 
{
    s->total = 0;
    for (int i = 0; i < 5; i++) 
    {
        s->sub_total[i] = s->minor[i] + s->major[i];
        s->sub_grade[i] = grade_calc(s->sub_total[i]);
        s->total += s->sub_total[i];
    }
    s->percentage = s->total / 5.0;
}

//FINAL REPORT
void output_display(Student s[], int n) 
{
    FILE *fp = fopen("students.txt", "w");
    float avg = 0, high, low;

    printf("\nRoll\t\tName\tS1\tS2\tS3\tS4\tS5\tTotal\t%%\n");
    fprintf(fp, "Roll\t\tName\tS1\tS2\tS3\tS4\tS5\tTotal\t%%\n");

    high = low = s[0].percentage;
    for (int i = 0; i < n; i++) 
    {
        printf("%s\t%s\t", s[i].roll, s[i].name);
        fprintf(fp, "%s\t%s\t", s[i].roll, s[i].name);

        for (int j = 0; j < 5; j++) 
        {
            printf("%d(%s)\t", s[i].sub_total[j],
            grade_to_string(s[i].sub_grade[j]));
            fprintf(fp, "%d(%s)\t", s[i].sub_total[j],
            grade_to_string(s[i].sub_grade[j]));
        }

        printf("%d\t%.2f\n", s[i].total, s[i].percentage);
        fprintf(fp, "%d\t%.2f\n", s[i].total, s[i].percentage);
        if (s[i].percentage > high) 
        {
            high = s[i].percentage;
        }
        if (s[i].percentage < low)
        {
            low  = s[i].percentage;
        }
        avg += s[i].percentage;
    }
    avg= avg/n;
    printf("\nClass Average Percentage: %.2f\n", avg);
    printf("high Percentage: %.2f\n", high);
    printf("low Percentage: %.2f\n", low);

    fprintf(fp, "\nClass Average Percentage: %.2f\n", avg);
    fprintf(fp, "high Percentage: %.2f\n", high);
    fprintf(fp, "low Percentage: %.2f\n", low);
    fclose(fp);


}


