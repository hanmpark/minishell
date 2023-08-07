/*
* Converts a given uppercase character to its corresponding
* lowercase representation.
*/
int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
		character += 32;
	return (character);
}
