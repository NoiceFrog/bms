#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const char* og_filename = "account.txt";
const char* temp_filename = "temp.txt";
const char* word_to_remove = "total money: ";

const char* create_account = "-ca";
const char* delete_account = "-da";
const char* deposit = "-d";
const char* withdraw = "-w";
const char* show_money = "-s";
const char* help_page = "-h";

int deposit_amount = 0;
int withdrawal_amount = 0;

int total_money = 0;
int total_money_to_show = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    FILE* og_file = fopen(og_filename, "a");
    if (og_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fclose(og_file);

    if (strcmp(argv[1], create_account) == 0) {
        printf("Account created successfully!\n");
    } else if (strcmp(argv[1], delete_account) == 0) {
        printf("Account successfully deleted!\n");
    } else if (strcmp(argv[1], deposit) == 0) {
        FILE* og_file = fopen(og_filename, "r");
        FILE* temp_file = fopen(temp_filename, "w");

        if (og_file == NULL || temp_file == NULL) {
            perror("Error opening file");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), og_file) != NULL) {
            if (strstr(line, word_to_remove) == NULL) {
                fputs(line, temp_file);
            } else {
                sscanf(line, "total money: %d", &total_money);
            }
        }

        fclose(og_file);
        fclose(temp_file);

        remove(og_filename);
        rename(temp_filename, og_filename);

        FILE* file = fopen(og_filename, "a");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }

        printf("How much money do you want to deposit? Enter below: \n");
        scanf("%d", &deposit_amount);
        total_money += deposit_amount;
        fprintf(file, "total money: %d\n", total_money);
        fclose(file);

        printf("Deposit successful. New total money: %d\n", total_money);

    } else if (strcmp(argv[1], withdraw) == 0) {
        FILE* og_file = fopen(og_filename, "r");
        FILE* temp_file = fopen(temp_filename, "w");

        if (og_file == NULL || temp_file == NULL) {
            perror("Error opening file");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), og_file) != NULL) {
            if (strstr(line, word_to_remove) == NULL) {
                fputs(line, temp_file);
            } else {
                sscanf(line, "total money: %d", &total_money);
            }
        }

        fclose(og_file);
        fclose(temp_file);

        remove(og_filename);
        rename(temp_filename, og_filename);

        printf("How much money would you like to withdraw? Enter below: \n");
        scanf("%d", &withdrawal_amount);
        total_money -= withdrawal_amount;

        FILE* account_file = fopen(og_filename, "a");
        if (account_file == NULL) {
            perror("Error opening file");
            return 1;
        }

        fprintf(account_file, "total money: %d\n", total_money);
        fclose(account_file);

        printf("Withdrawal successful. New total money: %d\n", total_money);

    } else if (strcmp(argv[1], show_money) == 0) {
        FILE* account_file = fopen(og_filename, "r");
        if (account_file == NULL) {
            perror("Error opening file");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), account_file) != NULL) {
            if (strstr(line, word_to_remove) != NULL) {
                sscanf(line, "total money: %d", &total_money_to_show);
            }
        }

        printf("Total money: %d\n", total_money_to_show);
        fclose(account_file);
    } else if (strcmp(argv[1], help_page) == 0) {
        printf("BMS v1 by Angel\n");
        printf("Usage: ./bms [options]\n");
        printf("Options:\n");
        printf("-ca     Create account.\n");
        printf("-da     Delete account.\n");
        printf("-d      Deposit an amount of money.\n");
        printf("-w      Withdraw an amount of money.\n");
        printf("-s      Show total money in account.\n");
        printf("-h      Show this help page.\n");
        printf("\n");
        printf("For any further assistance send my a message on discord.\n");
        printf("My discord: noicefrog\n");
    }
    else {
        printf("Invalid command\n");
    }

    return 0;
}

