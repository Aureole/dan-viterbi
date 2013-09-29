#ifndef _V_MATRIX_H_
#define _V_MATRIX_H_

#include "vtypes.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>

typedef struct vmatrix
{
	float *data;
	v_uint rows;
	v_uint columns;
	v_uint size;
}vmatrix;

vmatrix *vCreateMatrix(v_uint columns, v_uint rows);

void vSetMatrixData(vmatrix *matrix, const float *data);

float vGetMatrixValue(const vmatrix *matrix, v_uint col, v_uint row);

void vReleaseMatrix(vmatrix **matrix);


#endif