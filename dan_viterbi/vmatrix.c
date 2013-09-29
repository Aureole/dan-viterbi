#include "vmatrix.h"

vmatrix *vCreateMatrix(v_uint columns, v_uint rows)
{
	vmatrix *matrix;
	assert(rows != 0 && columns != 0);
	matrix = (vmatrix *)malloc(sizeof(vmatrix));
	if(matrix == NULL)
	{
		return NULL;
	}

	matrix->data = (float *)malloc(sizeof(float) * rows * columns);
	if(matrix->data == NULL)
	{
		free(matrix);
		return NULL;
	}
	matrix->columns = columns;
	matrix->rows = rows;
	return matrix;
}

void vSetMatrixData(vmatrix *matrix, const float *data)
{
	assert(matrix != NULL && data != NULL);
	memcpy(matrix->data, data, sizeof(float) * matrix->columns * matrix->rows);
}

float vGetMatrixValue(const vmatrix *matrix, v_uint col, v_uint row)
{
	v_uint index;
	assert(col < matrix->columns && row < matrix->rows);
	index = row * matrix->columns + col;
	return matrix->data[index];
}

void vReleaseMatrix(vmatrix **matrix)
{
	assert(matrix != NULL && (*matrix) != NULL);
	free((*matrix)->data);
	free((*matrix));
	*matrix = NULL;
}