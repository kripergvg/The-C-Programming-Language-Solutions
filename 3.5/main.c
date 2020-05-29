void main() {

}

void itob(int number, char converted[], unsigned int base) {
	unsigned int index = 0;
	while (number >=base)
	{
		int remainder = number % base;
		number /= base;

		if (remainder <= 9) {
			converted[index] = remainder + '0';
		}
		else {
			wh
			int digit = remainder % 10;
			remainder/ = 10;
		}


	}
}