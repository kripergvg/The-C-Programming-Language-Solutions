void reverse(char* s) {
	if (*s == '\0') {
		return;
	}

	reverse(s + 1);
	putchar(*s);
}

void main() {
	char *s = "qwerty";
	reverse(s);
}

