/*
 * QWellModelClass.cpp
 *
 *  Created on: 07 мая 2015 г.
 *      Author: andrey
 */

#include "head.h"
#include "QWellModelClass.h"

QWellModelClass::QWellModelClass() {
	// TODO Auto-generated constructor stub

	std::cout << "QWellModelClass Constructor;" << std::endl;

	// Квадрат состоит из двух треугольников.
	// всего нужно отрисовать 6 вершин, которые выбираются из glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Т.е. всего тут вершины 4-е так как мы все таки рисуем квадрат
	// Но рисуем его двумя треугольниками треугольниками, поэтому есть
	// повторяющиеся вершины. И что бы их не отрисовавать заново мы используем ebo:
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);  // this->elements...

    //============================================================
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    	this->axis.push_back(1.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    //-----------------------------------	ось X
    this->axis.push_back(2.0f);
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    	this->axis.push_back(1.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    //============================================================
    this->axis.push_back(0.0f);
    this->axis.push_back(2.0f);
    this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(1.0f);
    	this->axis.push_back(0.0f);
    //-----------------------------------	ось Y
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(1.0f);
    	this->axis.push_back(0.0f);
    //============================================================
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    this->axis.push_back(-2.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(1.0f);
    //-----------------------------------	ось Z
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(0.0f);
    	this->axis.push_back(1.0f);
    //=================================================
    //=================================================

    	int i;
    	float x, y, z;
    	for(i=0; i<1000; i++){
    		x = 0/10.0f;
    		y = i/10.0f;
    		z = -i/10.0f;
    		this->sin_vertices.push_back(x);
    		this->sin_vertices.push_back(y);
    		this->sin_vertices.push_back(z);
    			this->sin_vertices.push_back(1.0f);
    			this->sin_vertices.push_back(0.0f);
    			this->sin_vertices.push_back(0.0f);
    	}


//    	this->sin_vertices.push_back(0.0f);
//    	this->sin_vertices.push_back(0.0f);
//    	this->sin_vertices.push_back(0.0f);
//    		this->sin_vertices.push_back(1.0f);
//    		this->sin_vertices.push_back(0.0f);
//    		this->sin_vertices.push_back(0.0f);
//
//    	this->sin_vertices.push_back(1.0f);
//    	this->sin_vertices.push_back(1.0f);
//    	this->sin_vertices.push_back(0.0f);
//    		this->sin_vertices.push_back(1.0f);
//    		this->sin_vertices.push_back(0.0f);
//    		this->sin_vertices.push_back(0.0f);

    	  dt=1E-7;
    	  dx=0.0005;
    	  tsteps=100;
    	  spsteps=4000;
    	  xc=0.4;
    	  w=0.05;
    	  k0=450;
    	  period=10;

    	/* Allocate memory and initialize contents to zero */
    	RePsi=(float*)calloc(spsteps+2, sizeof(float));
    	ImPsi=(float*)calloc(spsteps+2, sizeof(float));
    	//RePsi[0] = 0;
    	//ImPsi[0] = 0;
    	RePsiOld=(float*)calloc(spsteps+2, sizeof(float));
    	ImPsiOld=(float*)calloc(spsteps+2, sizeof(float));
    	AbsValPsiSq=(float*)calloc(spsteps+2, sizeof(float));
    	V=(float*)calloc(spsteps+2, sizeof(float));
    	xm=(float*)calloc(spsteps+2, sizeof(float));


    	for(j=1; j<=spsteps; j++) {
    		xm[j]=((float)j)*dx;
    		RePsi[j]=exp(-(pow((xm[j]-xc),2))/(pow(w,2)))*cos(k0*xm[j]);
    		ImPsi[j]=exp(-(pow((xm[j]-xc),2))/(pow(w,2)))*sin(k0*xm[j]);
    		AbsValPsiSq[j]=pow(RePsi[j],2)+pow(ImPsi[j],2);

    		/* Round very small numbers zero to avoid artifacts when plotting */
    		if(fabs(RePsi[j])<1E-20) { RePsi[j]=0.0; }
    		if(fabs(ImPsi[j])<1E-20) { ImPsi[j]=0.0; }
    		if(fabs(AbsValPsiSq[j])<1E-20) { AbsValPsiSq[j]=0.0; }

    	    RePsiOld[j]=RePsi[j];
      	    ImPsiOld[j]=ImPsi[j];

    	}

    	  for(j=1; j<=spsteps; j++) {
    	    if((j>=int(spsteps*0.35))&&(j<=int(spsteps*0.55))){
    	    	V[j]=6.2E4;
    	    }
    	  }


    	  s=dt/(dx*dx);
    	  m = 1;
}


void QWellModelClass::update_gwp_ABS(){


	for(j=1; j<=spsteps; j++) {
		/* The if test before each of the next two lines is necessary to implement
		the leapfrog approach. If m is odd only RePsi is updated, and if m is
		even only ImPsi is updated. */
		if(m%2==1) {
			ImPsi[j]=ImPsi[j]+s*(RePsi[j+1]+RePsi[j-1])-2*(s+V[j]*dt)*RePsi[j];

		/* Periodically calculate the probability density and output it to a file */

			AbsValPsiSq[j]=pow(RePsi[j],2)+ImPsi[j]*ImPsiOld[j];
			if(fabs(AbsValPsiSq[j])<1E-20) { AbsValPsiSq[j]=0.0; }

			/* The following line assigns the value of ImPsiOld to the ImPsi value
			just updated.  ImPsiOld will be used in the probability density
			calculation two time steps hence. */
			ImPsiOld[j]=ImPsi[j];
		} else {
			RePsi[j]=RePsi[j]-s*(ImPsi[j+1]+ImPsi[j-1])+2*(s+V[j]*dt)*ImPsi[j];

			/* Periodically calculate the probability density and output it to a file */

			AbsValPsiSq[j]=RePsi[j]*RePsiOld[j]+pow(ImPsi[j],2);
			if(fabs(AbsValPsiSq[j])<1E-20) { AbsValPsiSq[j]=0.0; }

			RePsiOld[j]=RePsi[j];
		}



	}

	m++;


}


QWellModelClass::~QWellModelClass() {
	// TODO Auto-generated destructor stub
}



float* QWellModelClass::get_sin_vertices(){

	return this->sin_vertices.data();
}

int QWellModelClass::get_sin_vertices_size(){

	return this->sin_vertices.size() * sizeof(float);
}





float* QWellModelClass::get_axis(){

	return this->axis.data();
}

int QWellModelClass::get_axis_size(){

	return this->axis.size() * sizeof(float);
}



float* QWellModelClass::get_axis_color(){

	return this->axis_color.data();
}

int QWellModelClass::get_axis_color_size(){

	return this->axis_color.size() * sizeof(float);
}






float* QWellModelClass::get_cube(){

	return this->cube.data();
}

int QWellModelClass::get_cube_size(){

	return this->cube.size() * sizeof(float);
}





//-----------------------------------------------------
//-----------------------------------------------------

GLuint* QWellModelClass::get_elements(){

	return this->elements.data();
}

int QWellModelClass::get_elements_size(){

	return this->elements.size() * sizeof(float);
}

//-----------------------------------------------------
//-----------------------------------------------------

float* QWellModelClass::get_gwpRe_vertices(){

	return this->RePsi;
}

int QWellModelClass::get_gwpRe_size(){

	return (this->spsteps+2) * sizeof(float);
}

//-----------------------------------------------------
//-----------------------------------------------------


float* QWellModelClass::get_gwpIm_vertices(){

	return this->ImPsi;
}

int QWellModelClass::get_gwpIm_size(){

	return (this->spsteps+2) * sizeof(float);
}

//-----------------------------------------------------
//-----------------------------------------------------


float* QWellModelClass::get_gwpX_vertices(){

	return this->xm;
}

int QWellModelClass::get_gwpX_size(){

	return (this->spsteps+2) * sizeof(float);
}

//-----------------------------------------------------
//-----------------------------------------------------


float* QWellModelClass::get_gwpABS_vertices(){

	return this->AbsValPsiSq;
}

int QWellModelClass::get_gwpABS_size(){

	return (this->spsteps+2) * sizeof(float);
}
















