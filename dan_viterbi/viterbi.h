#ifndef _VITERBI_H_
#define _VITERBI_H_

#include "vmatrix.h"
#include <assert.h>

typedef struct viterbi
{
	const vmatrix **tran_score;
	const vmatrix **node_score;
	v_uint node_num;
	v_uint state_num;
	float *score;
	v_uint *tmp_path;
	v_uint *path;
}viterbi;

void vFreeViterbi(viterbi *v);

void vResetViterbi(viterbi *v);

v_bool vSetViterbi(viterbi *v, const vmatrix **node_score, const vmatrix **tran_score, v_uint node_num);

void vRunViterbi(viterbi *v);

#endif