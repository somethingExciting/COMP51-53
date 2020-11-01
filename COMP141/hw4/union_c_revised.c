#include <stdio.h>
#include <string.h>


union Smorgasbord {
	int i;
	char string[50];
	float f;
};


int main() {

	union Smorgasbord smorgasbord; 

	smorgasbord.i = 47;
	printf("smorgasbord.i = %d\n", smorgasbord.i);

	strcpy(smorgasbord.string, "aaaa");
	printf("smorgasbord.string = %s\n", smorgasbord.string);

	smorgasbord.f = 834.63;
	printf("smorgasbord.f = %f\n", smorgasbord.f);

	return 0;
}
