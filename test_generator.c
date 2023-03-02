#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: ./generator [filename]\n");
		return 0;
	}
	FILE *file = fopen(argv[1], "w");
	int n;
	scanf("%d", &n);

	// Doar add-uri. Folosit pentru testele in/test{4, 10, 16, 22}.in
	/*
	for (int i = 0; i < n; i++)
		fprintf(file, "A %d\n", i);
	fprintf(file, "P\nS");
	*/
	//Doar modify-uri. Folosit pentru testele in/test{5, 11, 17, 23}.in
	/*
	fprintf(file, "A 0\n");
	for (int i = 0; i < n; i++)
		fprintf(file, "M %d %d\n", i, i + 1);
	fprintf(file, "P\nS");
	*/
	// Doar remove-uri (si add-urile necesare). Folosit pentru testele in/test{6, 12, 18, 24}.in
	/*
	for (int i = 0; i < n; i++)
		fprintf(file, "A %d\n", i);
	for (int i = 0; i < n; i++)
		fprintf(file, "R %d\n", i);
	fprintf(file, "A 1\nP\nS");
	*/
	// Combinate. Folosit pentru testele in/test{7, 13, 19, 25}.in
	/*
	for (int i = 0; i < n; i++)
		fprintf(file, "A %d\n", i);
	fprintf(file, "P\n");
	for (int i = n; i > 0; i--)
		fprintf(file, "M %d %d\n", i - 1, i);
	fprintf(file, "P\n");
	for (int i = 0; i < n; i++)
		fprintf(file, "R %d\n", i + 1);
	fprintf(file, "A 1\nP\nS");
	*/
	// Add-uri dupa remove-uri. Folosit pentru testele in/test{8, 14, 20, 26}.in
	/*
	for (int i = 0; i < n; i++)
		fprintf(file, "A %d\n", i);
	for (int i = 0; i < n; i++)
		fprintf(file, "R %d\n", i);
	for (int i = 0; i < n; i++)
		fprintf(file, "A %d\n", i);
	fprintf(file, "P\nS");
	*/
	// Combinate. Folosit pentru testele in/test{9, 15, 21, 27}.in
	
	for (int i = 0; i < n; i++)
		fprintf(file, "A %d\n", i);
	for (int i = 0; i < n; i += 2)
		fprintf(file, "R %d\n", i);
	fprintf(file, "P\n");
	for (int i = 1; i < n; i += 2)
		fprintf(file, "M %d %d\n", i, i + 1);
	fprintf(file, "P\n");
	for (int i = 1; i < n; i += 2)
		fprintf(file, "A %d\n", i);
	for (int i = 0; i < n; i += 3)
		fprintf(file, "R %d\n", i);
	fprintf(file, "P\nS");
	
	fclose(file);
	return 0;
}