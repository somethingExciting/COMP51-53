#include <stdio.h>
#include <string.h>


union Smorgasbord {
	int i;
	char string[50];
	float f;
};


int main() {

	union Smorgasbord smorgasbord; 

	strcpy(smorgasbord.string, "aaaa");
	smorgasbord.f = 834.63;
	smorgasbord.i = 47;

	printf("smorgasbord.i = %d\n", smorgasbord.i);
	printf("smorgasbord.string = %s\n", smorgasbord.string);
	printf("smorgasbord.f = %f\n", smorgasbord.f);

	return 0;
}
