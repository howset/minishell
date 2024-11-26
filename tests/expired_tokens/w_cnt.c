#include <stdio.h>

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	w_cnt(char *input)
{
	int	i;
	int cnt;
	int flag;

	cnt = 0;
	flag = 0;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			flag = 0;
		else if (!flag)
		{
			flag = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

int main(void)
{
	char	*input;

	input = "two words";
	printf("res:%d\n", w_cnt(input));
	return (0);
}