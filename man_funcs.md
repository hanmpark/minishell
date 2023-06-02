# Man of all authorized functions + references

## readline();
```c
char	*readline (const char *prompt);
```
- reads a line from the terminal and return it, using prompt as a prompt.<br>
The line returned is allocated. Therefore must free(); when not used anymore.
