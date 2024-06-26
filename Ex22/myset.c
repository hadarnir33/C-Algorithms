#include <stdio.h>
#include <string.h>

#include "set.h"
#include "validations.h"

#define MAX_COMMAND_LENGTH 100


void execute_command(char *command, SetPtr sets[]){
    char *command_type, *command_args, *set_name, *numbers_list;
    SetPtr sets_from_command_args[3];
    command_type = strtok(command, " ");
    command_args = command_type + strlen(command_type) + 1;
    remove_spaces_and_tabs(command_args);

    if(strcmp(command_type, "read_set") == 0){
        set_name = strtok(command_args, ",");
        numbers_list = (set_name + strlen(set_name) + 1);
        read_set(find_set_by_name(set_name, sets), numbers_list);
    }
    else if(strcmp(command_type, "print_set") == 0){
        set_name = command_args;
        print_set(find_set_by_name(set_name, sets));
    }
    else if(strcmp(command_type, "union_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        union_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
    else if(strcmp(command_type, "intersect_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        intersect_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
    else if(strcmp(command_type, "sub_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        sub_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
    else if(strcmp(command_type, "symdiff_set") == 0){
        get_sets_from_command_args(command_args, sets, sets_from_command_args);
        sym_diff_set(sets_from_command_args[0], sets_from_command_args[1], sets_from_command_args[2]);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    Set* SETA, * SETB, * SETC, * SETD, * SETE, * SETF;
    SetPtr sets[6];

    SETA = init_set();
    SETB = init_set();
    SETC = init_set();
    SETD = init_set();
    SETE = init_set();
    SETF = init_set();

    sets[0] = SETA;
    sets[1] = SETB;
    sets[2] = SETC;
    sets[3] = SETD;
    sets[4] = SETE;
    sets[5] = SETF;

    printf("Enter command: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = '\0';  /* Remove the newline character */

    while(validate_command(command)){
        execute_command(command, sets);

        printf("Enter command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = '\0';  /*Remove the newline character */
    }

    return 0;
}