#include <stdio.h>
#include <string.h>

#ifndef USER_COM_ENA
	#define USER_COM_ENA
#endif

#include "exer_com.h"

int main(int argv, char *argc[])
{
	ST_SMPL	st_val[] = {
			{'1','2',"Good morning!"},
			{'3','4',"Good afternoon!"}
	};
	ST_SMPL *st_val_p[] = {&st_val[0],&st_val[1]};

	printf("*** Before ****\n");
	printf("struct[0] from = %c\n",st_val_p[0]->from);
	printf("struct[0] to = %c\n",st_val_p[0]->to);
	printf("struct[0] msg = %s\n",st_val_p[0]->msg);

	printf("struct[1] from = %c\n",st_val_p[1]->from);
	printf("struct[1] to = %c\n",st_val_p[1]->to);
	printf("struct[1] msg = %s\n",st_val_p[1]->msg);

	st_val_p[1]->from = 'A';
	st_val_p[1]->to = 'B';
	strcpy(st_val_p[1]->msg,"This is a pen!");


	printf("\nstruct[0] from = %c\n",st_val_p[0]->from);
	printf("struct[0] to = %c\n",st_val_p[0]->to);
	printf("struct[0] msg = %s\n",st_val_p[0]->msg);

	printf("struct[1] from = %c\n",st_val_p[1]->from);
	printf("struct[1] to = %c\n",st_val_p[1]->to);
	printf("struct[1] msg = %s\n",st_val_p[1]->msg);

	return 0;
}
