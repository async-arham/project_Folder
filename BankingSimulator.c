#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> // For console color functions

const char* ACCOUNT_FILE = "account.dat";

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void setColor(int color);
void printHeader()		;
void printLine();

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;

int main() {
    system("cls");
    SetConsoleTitle("Bank of NED University - Console Banking System");

    while (1) {
        setColor(11);
        printHeader();
        printf("\n");
        setColor(15);
        printf("\t1) Create Account\n");
        printf("\t2) Deposit Money\n");
        printf("\t3) Withdraw Money\n");
        printf("\t4) Check Balance\n");
        printf("\t5) Exit\n");
        printLine();
        printf("\nEnter your choice: ");

        int choice;
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                check_balance();
                break;
            case 5:
                setColor(10);
                printf("\nThank you for banking with us.\n");
                printf("Visit again - Bank of NED University\n");
                setColor(15);
                return 0;
            default:
                setColor(12);
                printf("\nInvalid Choice! Please Try Again.\n");
                setColor(15);
        }
        printf("\nPress Enter to return to Main Menu...");
        getchar(); getchar();
        system("cls");
    }
}

// Set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Print program header
void printHeader() {
    setColor(9);
printf("==============================================\n");
printf("              BANK OF NED UNIVERSITY           \n");
printf("==============================================\n");

}

// Print separator line
void printLine() {
    setColor(8);
    printf("----------------------------------------------\n");
    setColor(15);
}

// Create account
void create_account() {
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL) {
        setColor(12);
        printf("\nError: Unable to open file!\n");
        setColor(15);
        return;
    }

    while (getchar() != '\n');
    printHeader();
    printf("\nEnter Username: ");
    gets(acc.name);
    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);

    acc.balance = 0;
    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);

    setColor(10);
    printf("\nAccount Created Successfully!\n");
    printLine();
    setColor(15);
}

// Deposit money
void deposit_money() {
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        setColor(12);
        printf("\nError: Unable to open file!\n");
        setColor(15);
        return;
    }

    int acc_no;
    float money;
    Account acc_r;

    printHeader();
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Deposit: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == acc_no) {
            acc_r.balance += money;
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);

            setColor(10);
            printf("\nSuccessfully Deposited %.2f\n", money);
            printf("New Balance: %.2f\n", acc_r.balance);
            printLine();
            setColor(15);
            return;
        }
    }

    fclose(file);
    setColor(12);
    printf("\nAccount Number %d not found!\n", acc_no);
    printLine();
    setColor(15);
}

// Withdraw money
void withdraw_money() {
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        setColor(12);
        printf("\nError: Unable to open file!\n");
        setColor(15);
        return;
    }

    int acc_no;
    float money;
    Account acc_r;

    printHeader();
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Withdraw: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == acc_no) {
            if (acc_r.balance >= money) {
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                fclose(file);

                setColor(10);
                printf("\nWithdrawn Rs. %.2f Successfully!\n", money);
                printf("Remaining Balance: %.2f\n", acc_r.balance);
                printLine();
                setColor(15);
                return;
            } else {
                setColor(12);
                printf("\nInsufficient Balance!\n");
                setColor(15);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    setColor(12);
    printf("\nAccount Number %d not found!\n", acc_no);
    printLine();
    setColor(15);
}

// Check balance
void check_balance() {
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL) {
        setColor(12);
        printf("\nError: Unable to open file!\n");
        setColor(15);
        return;
    }

    int acc_no;
    Account acc_r;

    printHeader();
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    while (fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == acc_no) {
            setColor(11);
            printf("\nAccount Holder: %s\n", acc_r.name);
            printf("Account Number: %d\n", acc_r.acc_no);
            printf("Current Balance: Rs. %.2f\n", acc_r.balance);
            printLine();
            fclose(file);
            setColor(15);
            return;
        }
    }

    fclose(file);
    setColor(12);
    printf("\nAccount Number %d not found!\n", acc_no);
    printLine();
    setColor(15);
}