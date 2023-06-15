/* Checks whether a given character is alphanumeric, meaning it is either
* an alphabetic character (a-z, A-Z) or a digit (0-9).
*/
int	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) || \
		(c >= '0' && c <= '9'));
}
