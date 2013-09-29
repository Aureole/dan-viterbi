#include "viterbi.h"
#include <conio.h>
#include <stdio.h>


float n0[] = {2, 1, 3, 4};
float n1[] = {4, 2};
float n2[] = {6, 2, 7};
float t1[] = {2, 1, 5, 7, 2, 9, 3, 9};
float t2[] = {6, 2, 6, 8, 4, 4};


int main()
{
	vmatrix *tran[2], *node[3];
	viterbi v;
	v_uint i;
	tran[0] = vCreateMatrix(4, 2);
	tran[1] = vCreateMatrix(2, 3);
	node[1] = vCreateMatrix(2, 1);
	node[0] = vCreateMatrix(4, 1);
	node[2] = vCreateMatrix(3, 1);

	vSetMatrixData(tran[0], t1);
	vSetMatrixData(tran[1], t2);
	vSetMatrixData(node[0], n0);
	vSetMatrixData(node[1], n1);
	vSetMatrixData(node[2], n2);

	vSetViterbi(&v, node, tran, 3); 
	vRunViterbi(&v);

	for(i = 0; i < v.node_num; i++)
	{
		printf("%u ", v.path[i]);
	}
	_getch();
	

	vReleaseMatrix(&tran[0]);
	vReleaseMatrix(&tran[1]);
	vReleaseMatrix(&node[0]);
	vReleaseMatrix(&node[1]);
	vReleaseMatrix(&node[2]);


	return 0;
}