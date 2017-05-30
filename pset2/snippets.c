// code snippet to capitalize letters
char name[] = "milan";
for (int i = 0, j = strlen(name); i <j; i++)
name[i] = name[i] + ('A' - 'a');



// code snippet to get the right number of command-line arguments (from study.cs50.net)
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("too many command line arguments.");
        return 1;
    }
    // convert command line argument[1] string to integer
    int key = atoi(argv[1]);
}




