#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;
    
    while (1) {
        // 사용자로부터 입력 받기
        input = readline("Enter a command: ");

        // 입력한 명령어 출력
        printf("You entered: %s\n", input);

        // 명령어가 "exit"인 경우 종료
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // 사용자 입력이 잘못되었을 때 수정하기
        if (strlen(input) > 10) {
            printf("Error: command is too long!");
            rl_replace_line("", strlen(""));
            rl_redisplay();
            
        }

        // 입력한 명령어 저장
        add_history(input);

        // 메모리 할당 해제
        free(input);
        rl_on_new_line();
            
    }

    return 0;
}