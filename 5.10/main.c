#include <stdio.h>

int stack[1024];
int stack_index = 0;

void stack_push(int number);
int stack_pop();

void main(int arg_count, char* args[]) {
	for (int i = 1; i < arg_count; i++)
	{
		char* symbolp = args[i];
		char symbol = *symbolp;
		int number = 0;

		if (0 <= symbol - '0' && symbol - '0' <= 9)
		{
			while (symbol != '\0')
			{
				number = number * 10 + symbol - '0';
				symbolp++;
				symbol = *symbolp;
			}

			stack_push(number);
		}
		else {
			switch (symbol)
			{
			case '+':
			{
				int op1 = stack_pop();
				int op2 = stack_pop();
				stack_push(op1 + op2);
				break;
			}

			case '*':
			{
				int op1 = stack_pop();
				int op2 = stack_pop();
				stack_push(op1 * op2);
				break;
			}
			case '/':
			{
				int op1 = stack_pop();
				int op2 = stack_pop();
				stack_push(op2 / op1);
				break;
			}

			default:
				break;
			}
		}
	}

	printf("%d\n", stack_pop());
}

void stack_push(int number) {
	stack[stack_index] = number;
	stack_index++;
}

int stack_pop() {
	stack_index--;
	return stack[stack_index];
}

