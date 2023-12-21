#include "shell.h"

/**
 * _strlen - Returns the Length of a Chars
 * @s: String to measure
 * Return: Length of String
 */
int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);
	while (*s++)
		x++;
	return (x);
}

/**
 * _strcmp - Compares Two Strings
 * @s1: First String
 * @s2: Second String
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Verifies if Needle Starts with Haystack
 * @haystack: The search chars
 * @needle: Substring to Search
 * Return: Ptr to Next Chars of Haystack
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Combines Two Strings
 * @dest: The dest string
 * @src: Source String
 * Return: Ptr to Dest Buf
 */
char *_strcat(char *dest, char *src)
{
	char *res = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (res);
}
