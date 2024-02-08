#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 500

typedef struct
{
    unsigned char memory[MEMORY_SIZE];
    int pointer;
    char *instructions;
} BrainfuckInterpreter;

void loadCode(BrainfuckInterpreter *interpreter, char *code)
{
    interpreter->instructions = code;
}

void interpret(BrainfuckInterpreter *interpreter)
{
    char input [MEMORY_SIZE];

    char output[MEMORY_SIZE];
    int outputIndex = 0;
    int loopStack[MEMORY_SIZE];
    int loopStackIndex = 0;

    int i = 0;
    char command;
    while ((command = interpreter->instructions[i]) != '\0')
    {
        switch (command)
        {
        case '>':
            interpreter->pointer++;
            break;
        case '<':
            interpreter->pointer--;
            break;
        case '+':
            interpreter->memory[interpreter->pointer] = (interpreter->memory[interpreter->pointer] + 1) % 256;
            break;
        case '-':
            interpreter->memory[interpreter->pointer] = (interpreter->memory[interpreter->pointer] - 1 + 256) % 256;
            break;
        case '.':
            output[outputIndex++] = interpreter->memory[interpreter->pointer];
            break;
        case ',':
            input[i] = getchar();
            break;
        case '[':
            if (interpreter->memory[interpreter->pointer] == 0)
            {
                int loopDepth = 1;
                while (loopDepth > 0)
                {
                    i++;
                    if (interpreter->instructions[i] == '[')
                    {
                        loopDepth++;
                    }
                    else if (interpreter->instructions[i] == ']')
                    {
                        loopDepth--;
                    }
                }
            }
            else
            {
                loopStack[loopStackIndex++] = i;
            }
            break;
        case ']':
            if (interpreter->memory[interpreter->pointer] != 0)
            {
                i = loopStack[loopStackIndex - 1];
            }
            else
            {
                loopStackIndex--;
            }
            break;
        }

        i++;
    }

    output[outputIndex] = '\0';
    printf("Output: %s\n", output);
}

int main(int argc, char *argv[])
{
    BrainfuckInterpreter interpreter;
    char *brainfuckCode = argv[1];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <BrainfuckCode>\n", argv[0]);
        return 1;
    }
    printf("Brainfuck code: %s\n", brainfuckCode);

    loadCode(&interpreter, brainfuckCode);
    interpret(&interpreter);

    return 0;
}
