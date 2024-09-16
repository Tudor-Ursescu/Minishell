#include "minishell.h"

int main (void)
{
	char *prompt;
	char *input;
	input = readline("awaiting command: ");
	// if (input == NULL)
		// reprompt
	prompt = malloc((ft_strlen(input) + 1 )* sizeof(char));

	ft_strlcpy(prompt, input, ft_strlen(input) + 1);
	// printf("Prompt: %s", input);
	free(input);
	free(prompt);
}	