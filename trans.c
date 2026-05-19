#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure definition
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

// function prototypes
unsigned int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);
void searchRecord(FILE *fPtr);   // NEW FUNCTION

int main(int argc, char *argv[])
{
    FILE *cfPtr;
    unsigned int choice;

    if ((cfPtr = fopen("credit.dat", "rb+")) == NULL)
    {
        printf("%s: File could not be opened.\n", argv[0]);
        exit(0);
    }

    while ((choice = enterChoice()) != 6)   // changed to 6
    {
        switch (choice)
        {
        case 1:
            textFile(cfPtr);
            break;
        case 2:
            updateRecord(cfPtr);
            break;
        case 3:
            newRecord(cfPtr);
            break;
        case 4:
            deleteRecord(cfPtr);
            break;
        case 5:
            searchRecord(cfPtr);   // NEW CASE
            break;
        default:
            puts("Incorrect choice");
        }
    }

    fclose(cfPtr);
    return 0;
}

// create text file
void textFile(FILE *readPtr)
{
    FILE *writePtr;
    struct clientData client = {0, "", "", 0.0};

    if ((writePtr = fopen("accounts.txt", "w")) == NULL)
    {
        puts("File could not be opened.");
    }
    else
    {
        rewind(readPtr);

        fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
                "Acct", "Last Name", "First Name", "Balance");

        while (fread(&client, sizeof(struct clientData), 1, readPtr))
        {
            if (client.acctNum != 0)
            {
                fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n",
                        client.acctNum, client.lastName,
                        client.firstName, client.balance);
            }
        }

        fclose(writePtr);
    }
}

// update record
void updateRecord(FILE *fPtr)
{
    unsigned int account;
    double transaction;
    struct clientData client = {0, "", "", 0.0};

    printf("Enter account to update (1 - 100): ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
    }
    else
    {
        printf("%-6d%-16s%-11s%10.2f\n",
               client.acctNum, client.lastName,
               client.firstName, client.balance);

        printf("Enter amount (+ deposit / - withdraw): ");
        scanf("%lf", &transaction);

        client.balance += transaction;

        fseek(fPtr, -sizeof(struct clientData), SEEK_CUR);
        fwrite(&client, sizeof(struct clientData), 1, fPtr);

        printf("Updated Balance: %.2f\n", client.balance);
    }
}

// delete record
void deleteRecord(FILE *fPtr)
{
    struct clientData client;
    struct clientData blank = {0, "", "", 0.0};
    unsigned int account;

    printf("Enter account to delete (1 - 100): ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
    }
    else
    {
        fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
        fwrite(&blank, sizeof(struct clientData), 1, fPtr);
        printf("Account deleted successfully.\n");
    }
}

// add new record
void newRecord(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};
    unsigned int account;

    printf("Enter new account number (1 - 100): ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists.\n");
    }
    else
    {
        printf("Enter LastName FirstName Balance: ");
        scanf("%14s %9s %lf",
              client.lastName,
              client.firstName,
              &client.balance);

        client.acctNum = account;

        fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
        fwrite(&client, sizeof(struct clientData), 1, fPtr);

        printf("Account created successfully.\n");
    }
}

// NEW FEATURE: search record
void searchRecord(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};
    int choice;
    unsigned int account;
    char name[15];

    printf("\nSearch by:\n1. Account Number\n2. Last Name\nChoice: ");
    scanf("%d", &choice);

    rewind(fPtr);

    if (choice == 1)
    {
        printf("Enter account number: ");
        scanf("%u", &account);

        fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
        fread(&client, sizeof(struct clientData), 1, fPtr);

        if (client.acctNum != 0)
        {
            printf("\n%-6d%-16s%-11s%10.2f\n",
                   client.acctNum, client.lastName,
                   client.firstName, client.balance);
        }
        else
        {
            printf("Account not found.\n");
        }
    }
    else if (choice == 2)
    {
        printf("Enter last name: ");
        scanf("%s", name);

        while (fread(&client, sizeof(struct clientData), 1, fPtr))
        {
            if (client.acctNum != 0 &&
                strcmp(client.lastName, name) == 0)
            {
                printf("\n%-6d%-16s%-11s%10.2f\n",
                       client.acctNum, client.lastName,
                       client.firstName, client.balance);
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

// menu
unsigned int enterChoice(void)
{
    unsigned int choice;

    printf("\nMENU\n");
    printf("1 - Export to text file\n");
    printf("2 - Update account\n");
    printf("3 - Add new account\n");
    printf("4 - Delete account\n");
    printf("5 - Search account (NEW)\n");
    printf("6 - Exit\n");
    printf("Enter choice: ");

    scanf("%u", &choice);

    return choice;
}
