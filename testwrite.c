#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* write c to file descriptor*/

int main(void) {
    
	ft_putchar_fd('H', 1); // STDIN
	ft_putchar_fd(' ', 1); // STDOUT
	ft_putchar_fd('H', 1); // STDERR

	return 0;
}