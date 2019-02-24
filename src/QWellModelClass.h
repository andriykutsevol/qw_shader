/*
 * QWellModelClass.h
 *
 *  Created on: 07 мая 2015 г.
 *      Author: andrey
 */

#ifndef QWELLMODELCLASS_H_
#define QWELLMODELCLASS_H_

#include "head.h"



class QWellModelClass {

private:

	std::vector <float> sin_vertices;
	std::vector <float> axis;
	std::vector <float> axis_color;
	std::vector <float> cube;
	std::vector <GLuint> elements;

	int tsteps,spsteps,j,m,i,period;
	double dt,dx,xc,w,s,k0;
	float *RePsi,*ImPsi,*RePsiOld,*ImPsiOld,*AbsValPsiSq,*V,*xm;

public:
	QWellModelClass();
	virtual ~QWellModelClass();

	float* get_sin_vertices();
	int get_sin_vertices_size();

	float* get_axis();
	int get_axis_size();

	float* get_axis_color();
	int get_axis_color_size();

	float* get_cube();
	int get_cube_size();

	GLuint* get_elements();
	int get_elements_size();


	float* get_gwpRe_vertices();
	int get_gwpRe_size();

	float* get_gwpIm_vertices();
	int get_gwpIm_size();

	float* get_gwpABS_vertices();
	int get_gwpABS_size();

	float* get_gwpX_vertices();
	int get_gwpX_size();

	void update_gwp_ABS();


};

#endif /* QWELLMODELCLASS_H_ */
