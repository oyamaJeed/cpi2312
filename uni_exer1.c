#include <stdio.h>
#include <string.h>
#include "exer_com.h"

int main(int argv, char *argc[])
{
	UNI_EXER	uni_exer;
	uni_exer.exer.from = 'C';
	uni_exer.exer.to = 'D';
	strcpy(	uni_exer.exer.msg,"Good evening!");
	UNI_EXER	*uni_val_p = &uni_exer;

	printf("*** Init ****\n");
	printf("uni st form = %c\n",uni_val_p->exer.from);
	printf("uni st to = %c\n",uni_val_p->exer.to);
	printf("uni st msg = %s\n",uni_val_p->exer.msg);

	uni_val_p->exer.from = 'E';
	uni_val_p->exer.to = 'F';
	strcpy(uni_val_p->exer.msg,"This is an apple!");

	printf("\n*** Modify ****\n");
	printf("uni st form = %c\n",uni_exer.exer.from);
	printf("uni st to = %c\n",uni_exer.exer.to);
	printf("uni st msg = %s\n",uni_exer.exer.msg);

	return 0;
}
