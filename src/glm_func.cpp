/*
 * glm_func.cpp
 *
 *  Created on: 07 мая 2015 г.
 *      Author: andrey
 */

#include "head.h"

void glm_func(){
std::cout<<"glm_func()" << std::endl;

glm::mat4 trans;
trans = glm::rotate(trans, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));

glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
printf("%f, %f, %f\n", result.x, result.y, result.z);

}


