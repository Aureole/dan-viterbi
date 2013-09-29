#include "viterbi.h"

void vFreeViterbi(viterbi *v)
{
	assert(v != NULL);
	free(v->score);
	free(v->tmp_path);
	free(v->path);
	v->score = NULL;
	v->tmp_path = NULL;
	v->path = NULL;
}

void vResetViterbi(viterbi *v)
{
	v_uint i;
	assert(v != NULL);
	assert(v->node_score != NULL && v->tran_score != NULL);
	assert(v->tmp_path != NULL && v->path != NULL && v->score != NULL);

	for(i = 0; i < v->node_num * v->state_num; i++)
	{
		v->score[i] = 0;
		v->tmp_path[i] = 0;
	}

	for(i = 0; i < v->tran_score[0]->columns; i++)
	{
		v->tmp_path[i] = i;
		v->score[i] = vGetMatrixValue(v->node_score[0], i, 0);
	}
}


v_bool vSetViterbi(viterbi *v, const vmatrix **node_score, const vmatrix **tran_score, v_uint node_num)
{
	v_uint i;
	v_uint state_num = 0;
	assert(v != NULL && tran_score != NULL && node_num > 0 && node_score != NULL);

	v->tran_score = tran_score;
	v->node_score = node_score;
	v->node_num = node_num;
	for(i = 0; i < node_num - 1; i++)
	{
		if(tran_score[i]->rows != node_score[i + 1]->columns
			||tran_score[i]->columns != node_score[i]->columns)
		{
			return v_false;
		}
	}

	for(i = 0; i < node_num - 1; i++)
	{
		if(tran_score[i]->columns > state_num)
		{
			state_num = tran_score[i]->columns;
		}
		if(tran_score[i]->rows > state_num)
		{
			state_num = tran_score[i]->rows;
		}
	}
	v->state_num = state_num;
	
	v->tmp_path = (v_uint *)malloc(sizeof(v_uint) * node_num * state_num);
	v->path = (v_uint *)malloc(sizeof(v_uint) * node_num);
	v->score = (float *)malloc(sizeof(float) * node_num * state_num);

	if(v->tmp_path == NULL || v->score == NULL || v->path == NULL)
	{
		vFreeViterbi(v);
		return v_false;
	}

	vResetViterbi(v);
	return v_true;
}

void vGetViterbiPath(viterbi *v)
{
	v_uint num;
	int i;
	v_uint max_index;
	v_uint index;
	float max_score;
	float *score;
	v_uint *path;
	assert(v != NULL);
		
	score = v->score;
	path = v->path;
	num = v->tran_score[v->node_num - 2]->rows;
	max_index = 0;
	max_score = -1e30f;
	for(i = 0; i < num; i++)
	{
		index = (v->node_num - 1) * v->state_num + i;
		if(score[index] > max_score)
		{
			max_score = score[index];
			max_index = i;
		}
	}

	path[v->node_num - 1] = max_index;
	for(i = v->node_num - 2; i >= 0; i--)
	{
		path[i] = v->tmp_path[path[i + 1] + (i + 1) * v->state_num];
	}
}

void vRunViterbi(viterbi *v)
{
	v_uint i, j, k;
	v_uint index_pre;
	v_uint index;
	float *score;
	v_uint *path;
	float value;

	vResetViterbi(v);

	score = v->score;
	path = v->tmp_path;

	for(k = 1; k < v->node_num; k++)
	{
		index_pre = (k - 1) * v->state_num;
		for(i = 0; i < v->node_score[k]->columns; i++)
		{
			index = k * v->state_num + i;
			for(j = 0; j < v->tran_score[k - 1]->columns; j++)
			{
				value = score[index_pre + j] 
					+ vGetMatrixValue(v->tran_score[k - 1], j, i)  // 上一个节点是列，当前节点是行（也即当前一行对已上一个节点的所有状态）
					+ vGetMatrixValue(v->node_score[k], i, 0); 
					
				if(value > score[index])
				{
					score[index] = value;
					path[index] = j;
				}
			}
		}
	}

	vGetViterbiPath(v);
}