/* Checks whether a given character is an alphabetic character.
* It determines if the character is either an uppercase letter (A-Z) 
* or a lowercase letter (a-z).
*/
int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
