/*
* Converts a given lowercase character
* to its corresponding uppercase representation.
*/
int	ft_toupper(int character)
{
	if (character >= 97 && character <= 122)
		character -= 32;
	return (character);
}
