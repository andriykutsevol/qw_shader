/*
 * head.h
 *
 *  Created on: 28 апр. 2015 г.
 *      Author: andrey
 */

#ifndef HEAD_H_
#define HEAD_H_

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <GL/glut.h>

#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <math.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


int triangle_shader_func(int argc, char **argv);

void glm_func();



#endif /* HEAD_H_ */
