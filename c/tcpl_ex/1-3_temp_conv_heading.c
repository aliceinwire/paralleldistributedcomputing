#include <stdio.h>
/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version */
main()
{
	float fahr;
	printf("%3s %6s\n", "fahr", "celc");
	for (fahr = 300; fahr >= 0; fahr = fahr - 20)
		printf("%3.0f %6.1f\n", fahr, (5.0/9.0) * (fahr-32.0));
}

