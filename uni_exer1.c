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

	printf("\n*** Init ****\n");
	printf("uni st form = %c\n",uni_exer.exer.from);
	printf("uni st to = %c\n",uni_exer.exer.to);
	printf("uni st msg = %s\n",uni_exer.exer.msg);




	/*
	printf("union long=%ld\n", uni_val.l_mnb);
	for(int i=0; i<4; i++)	{
		printf("union sary c_ary=0x%02x\n", uni_val.sary.c_ary[i]);
	}

	for(int j=0; j<4; j++)	{
		uni_val_p->sary.c_ary[j] = 0x50 + j;
	}

	printf("*** After ****\n");

	printf("union long=%ld\n", uni_val_p->l_mnb);
	for(int i=0; i<4; i++)	{
		printf("union sary c_ary=0x%02x\n", uni_val_p->sary.c_ary[i]);
	}

	printf("COM_VALUE=%d\n", COM_VALUE);
	*/
	return 0;
}
