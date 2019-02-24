/*
 * triangle_shader_func.cpp
 * /media/HLAM/Workspaces/SVN_COPY/QT/Qw_Doc/CODES/4/ (шейдеры и vbo отсюда).
 * /media/HLAM/Workspaces/SVN_COPY/Import/OpenGLWS/gsgl_line/src/	(glut и класс шейдеров отсюда).
 *
 *  Created on: 04 мая 2015 г.
 *      Author: andrey
 */

#include "head.h"
#include "GLShader.h"
#include "QWellModelClass.h"

#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

//#include "GlShader.h"

float delay = 0.01;

// Наш класс шейдера
GlShader shader;
//! Переменные с индентификаторами ID

//------------------------------------------

//! ID атрибута вершин
GLint  Attrib_vertex;

//! ID атрибута цветов
GLint  Attrib_color;

//! ID Vertex Buffer Object
GLuint VBO_vertex;

//! ID Vertex Buffer Object
GLuint VBO_color;

//! ID VBO for element indices
GLuint VBO_element;

//! Количество индексов
GLint Indices_count;

//! Матрица проекции
mat4 Proj_Matrix;
GLint  Proj_Matrix_unif;

mat4 Mod_Matrix;
GLint Mod_Matrix_unif;

mat4 Cube_Matrix;
GLint Cube_Matrix_unif;

mat4 LookAt_Matrix;
GLint LookAt_Matrix_unif;

GLint time_unif_Index;
int my_time = 0;

float z_coord = 0;


QWellModelClass qwellModel;
GLuint axis_vbo, axis_color_vbo, sin_vert_vbo;

GLuint Cube_Subr_Index;
GLuint Axis_Subr_Index;
GLuint Wave_Draw_Index;
GLuint GWP_Draw_Index;

GLuint gwp_x_vbo;
GLuint gwp_Re_vbo;
GLuint gwp_Im_vbo;
GLuint gwp_abs_vbo;

GLint gwp_x_coord_Index;
GLint gwp_y_coord_Index;





//! Вершина
struct vertex
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

//! Инициализация OpenGL, здесь пока по минимальному
void initGL()
{
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
}

//! Проверка ошибок OpenGL, если есть то выводит в консоль тип ошибки
void checkOpenGLerror()
{
  GLenum errCode;
  if((errCode=glGetError()) != GL_NO_ERROR)
    std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

void TimerFunction(int value)
{
	// Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(1,TimerFunction, 1);
}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_LEFT :
			Mod_Matrix = glm::rotate(Mod_Matrix, 5.0f, vec3(0.0f, 1.0f, 0.0f));
			break;
		case GLUT_KEY_RIGHT :
			Mod_Matrix = glm::rotate(Mod_Matrix, -5.0f, vec3(0.0f, 1.0f, 0.0f));
			break;
		case GLUT_KEY_UP :
			Mod_Matrix = glm::rotate(Mod_Matrix,-5.0f, vec3(1.0f, 0.0f, 0.0f));
			break;
		case GLUT_KEY_DOWN :
			Mod_Matrix = glm::rotate(Mod_Matrix, 5.0f, vec3(1.0f, 0.0f, 0.0f));

			break;
	}
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
		{
		case 'w':
			Mod_Matrix = glm::translate(Mod_Matrix, vec3(0.0f, 0.1f, 0.0f));
			break;

		case 's':
			Mod_Matrix = glm::translate(Mod_Matrix, vec3(0.0f, -0.1f, 0.0f));
			break;

		case 'a':
			Mod_Matrix = glm::translate(Mod_Matrix, vec3(-0.1f, 0.0f, 0.0f));
			break;

		case 'd':
			Mod_Matrix = glm::translate(Mod_Matrix, vec3(0.1f, 0.0f, 0.0f));
			break;

//		case 'p':
//			cameraView.toggleMouseWarp();
//			break;

		case 27:
			exit(0);
			break;

		}
}

void mouseWheel(int wheel, int direction, int x, int y)
{

	if(wheel == 3)
		//Mod_Matrix = glm::translate(Mod_Matrix, vec3(0.0f, 0.0f, -0.1f));
		z_coord = z_coord - 0.1f;
	    LookAt_Matrix = glm::lookAt(vec3(0.0f, 0.0f, z_coord),vec3(0.0f, 0.0f, -3.0f),vec3(0.0f, 1.0f, 0.0f));
	if(wheel == 4)
		//Mod_Matrix = glm::translate(Mod_Matrix, vec3(0.0f, 0.0f, 0.1f));
		z_coord = z_coord + 0.1f;
	    LookAt_Matrix = glm::lookAt(vec3(0.0f, 0.0f, z_coord),vec3(0.0f, 0.0f, -3.0f),vec3(0.0f, 1.0f, 0.0f));

//	std::cout<< "wheel: "<< wheel << std::endl;
//	std::cout<< "direction: "<< direction <<std::endl;
//	std::cout<< "x: "<< x <<std::endl;
//	std::cout<< "y: "<< y <<std::endl;

}

//! Инициализация шейдеров
void initShader()
{
//  //! Исходный код шейдеров
//  const GLchar* vsSource =
//    "attribute vec3 coord;\n"
//    "attribute vec3 color;\n"
//    "varying vec3 var_color;\n"
//    "uniform mat4 matrix;\n"
//    "void main() {\n"
//    "  gl_Position = matrix * vec4(coord, 1.0);\n"
//    "  var_color = color;\n"
//    "}\n";
//  const GLchar* fsSource =
//    "varying vec3 var_color;\n"
//    "void main() {\n"
//    "  gl_FragColor = vec4(var_color, 1.0);\n"
//    "}\n";

//  if(!shader.load(vsSource, fsSource))
//  {
//    std::cout << "error load shader \n";
//    return;
//  }


	if(!shader.loadFiles("./shaders/vsSource.gsgl", "./shaders/fsSource.gsgl"))
	{
		std::cout << "error load shader \n";
		return;
	}

  ///! Вытягиваем ID атрибута из собранной программы
  Attrib_vertex = shader.getAttribLocation("coord");

  //! Вытягиваем ID юниформ
  Attrib_color = shader.getAttribLocation("color");


  //! Вытягиваем ID юниформ матрицы проекции
  Proj_Matrix_unif = shader.getUniformLocation("projectionMatrix");

  Mod_Matrix_unif = shader.getUniformLocation("modelMatrix");

  LookAt_Matrix_unif = shader.getUniformLocation("viewMatrix");

  Cube_Matrix_unif = shader.getUniformLocation("CubeMatrix");

  Cube_Subr_Index = shader.GetSubroutineIndex("Cube_Draw");
  Axis_Subr_Index = shader.GetSubroutineIndex("Axis_Draw");
  Wave_Draw_Index = shader.GetSubroutineIndex("Wave_Draw");

  time_unif_Index = shader.getUniformLocation("time");

  //-----------------------------
  gwp_x_coord_Index = shader.getAttribLocation("gwp_x_coord");
  gwp_y_coord_Index = shader.getAttribLocation("gwp_y_coord");
  GWP_Draw_Index = shader.GetSubroutineIndex("GWP_Draw");

  //-----------------------------

  checkOpenGLerror();
}

//! Инициализация VBO_vertex
void initVBO()
{
  //! Вершины куба
  vertex vertices[] = {
	  {-1.0f, -1.0f, -1.0f},
	  {1.0f, -1.0f, -1.0f},
	  {1.0f,  1.0f, -1.0f},
	  {-1.0f, 1.0f, -1.0f},
	  {-1.0f, -1.0f,  1.0f},
	  {1.0f, -1.0f,  1.0f},
	  {1.0f,  1.0f,  1.0f},
	  {-1.0f,  1.0f,  1.0f}
  };
  //! Цвета куба без альфа компонента
  vertex colors[] = {
	  {1.0f, 0.5f, 1.0f},
	  {1.0f, 0.5f, 0.5f},
	  {0.5f, 0.5f, 1.0f},
	  {0.0f, 1.0f, 1.0f},
	  {1.0f, 0.0f, 1.0f},
	  {1.0f, 1.0f, 0.0f},
	  {1.0f, 0.0f, 1.0f},
	  {0.0f, 1.0f, 1.0f}
  };
  //! Индексы вершин, обшие и для цветов
  GLint indices[] = {
    0, 4, 5, 0, 5, 1,
    1, 5, 6, 1, 6, 2,
    2, 6, 7, 2, 7, 3,
    3, 7, 4, 3, 4, 0,
    4, 7, 6, 4, 6, 5,
    3, 0, 1, 3, 1, 2
  };

  // Создаем буфер для вершин
  glGenBuffers(1, &VBO_vertex);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Создаем буфер для цветов вершин
  glGenBuffers(1, &VBO_color);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  // Создаем буфер для индексов вершин
  glGenBuffers(1, &VBO_element);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_element);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Indices_count = sizeof(indices) / sizeof(indices[0]);


  //-----------------------------------------------------
  // AXIS

	glGenBuffers(1, &axis_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, axis_vbo);
	glBufferData(GL_ARRAY_BUFFER, qwellModel.get_axis_size(), qwellModel.get_axis(), GL_STATIC_DRAW);

	glGenBuffers(1, &axis_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, axis_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, qwellModel.get_axis_color_size(), qwellModel.get_axis_color(), GL_STATIC_DRAW);


	//---------------------------------------------------
	// Sine Wave
	std::cout<<"Sine Wave Data Size: "<< qwellModel.get_sin_vertices_size() << std::endl;
	glGenBuffers(1, &sin_vert_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, sin_vert_vbo);
	glBufferData(GL_ARRAY_BUFFER, qwellModel.get_sin_vertices_size(), qwellModel.get_sin_vertices(), GL_STATIC_DRAW);


	//-----------------------------------------------------
	// GWP

	std::cout<<"get_gwpABS_vertices: " << qwellModel.get_gwpABS_vertices() << std::endl;
	std::cout<<"get_gwpABS_size: " << qwellModel.get_gwpABS_size() << std::endl;

	glGenBuffers(1, &gwp_abs_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gwp_abs_vbo);
	//glBufferData(GL_ARRAY_BUFFER, qwellModel.get_gwpABS_size(), qwellModel.get_gwpABS_vertices(), GL_DYNAMIC_DRAW);

	glGenBuffers(1, &gwp_x_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gwp_x_vbo);
	glBufferData(GL_ARRAY_BUFFER, qwellModel.get_gwpX_size(), qwellModel.get_gwpX_vertices(), GL_DYNAMIC_DRAW);




  checkOpenGLerror();
}

void freeVBO()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &VBO_element);
  glDeleteBuffers(1, &VBO_element);
  glDeleteBuffers(1, &VBO_color);
}

void resizeWindow(int width, int height)
{
	  glViewport(0, 0, width, height);

	  height = height > 0 ? height : 1;
	  const GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;

	  Proj_Matrix= glm::perspective(45.0f, aspectRatio, 1.0f, 200.0f);

	  Mod_Matrix = glm::translate(Mod_Matrix, vec3(-1.0f, -0.5f, -2.0f));
	  Mod_Matrix = glm::rotate(Mod_Matrix, 8.0f, vec3(0.0f, 1.0f, 0.0f));

	  LookAt_Matrix = glm::lookAt(vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 0.0f, -3.0f),vec3(0.0f, 1.0f, 0.0f));

	  Cube_Matrix = glm::translate(Cube_Matrix, vec3(1.0f, 0.0f, 0.0f));

}

//! Отрисовка
void render()
{


  my_time = my_time + 1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //! Устанавливаем шейдерную программу текущей
  shader.use();

  shader.setUniform(time_unif_Index, my_time);

  //! Передаем матрицу в шейдер
  shader.setUniform(Proj_Matrix_unif, Proj_Matrix);
  shader.setUniform(LookAt_Matrix_unif, LookAt_Matrix);
  shader.setUniform(Mod_Matrix_unif, Mod_Matrix);

  //--------------------------------------------------
  shader.UniformSubroutinesuiv(&Axis_Subr_Index);

  glBindBuffer(GL_ARRAY_BUFFER, axis_vbo);
  glEnableVertexAttribArray(Attrib_vertex);
      //! Указывая pointer 0 при подключенном буфере, мы указываем что данные в VBO
      //glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);

  //glBindBuffer(GL_ARRAY_BUFFER, axis_color_vbo);
  glEnableVertexAttribArray(Attrib_color);
      //glVertexAttribPointer(Attrib_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glVertexAttribPointer(Attrib_color, 3, GL_FLOAT, GL_FALSE,
			6*sizeof(float), (void*)(3*sizeof(float)));


  //! Передаем данные на видеокарту(рисуем)
  	glLineWidth (1.0);
  	glDrawArrays(GL_LINES, 0, 6); // 6 точек (наши три линии).

  //! Отключаем массив атрибутов
  glDisableVertexAttribArray(Attrib_vertex);

  //! Отключаем массив атрибутов
  glDisableVertexAttribArray(Attrib_color);


  //--------------------------------------------------
  //--------------------------------------------------
  // Собственно GWP.

  shader.UniformSubroutinesuiv(&GWP_Draw_Index);


  glBindBuffer(GL_ARRAY_BUFFER, gwp_abs_vbo);
    qwellModel.update_gwp_ABS();
	glBufferData(GL_ARRAY_BUFFER, qwellModel.get_gwpABS_size(), qwellModel.get_gwpABS_vertices(), GL_DYNAMIC_DRAW);
  	  glEnableVertexAttribArray(gwp_y_coord_Index);
  	  glVertexAttribPointer(gwp_y_coord_Index, 1, GL_FLOAT, GL_FALSE, 0, 0);


  glBindBuffer(GL_ARRAY_BUFFER, gwp_x_vbo);
  	  glEnableVertexAttribArray(gwp_x_coord_Index);
  	  glVertexAttribPointer(gwp_x_coord_Index, 1, GL_FLOAT, GL_FALSE, 0, 0);

      //! Передаем данные на видеокарту(рисуем)
      	glLineWidth (1);
      	glDrawArrays(GL_LINE_STRIP, 0, 4000); // 6 точек (наши три линии).

  //-----------------
  // Update AbsValPsiSq
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
        qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
         qwellModel.update_gwp_ABS();
 //   	glBindBuffer(GL_ARRAY_BUFFER, gwp_abs_vbo);
 //   	glBufferData(GL_ARRAY_BUFFER, qwellModel.get_gwpABS_size(), qwellModel.get_gwpABS_vertices(), GL_DYNAMIC_DRAW);

        glDisableVertexAttribArray(gwp_abs_vbo);
        glDisableVertexAttribArray(gwp_x_vbo);

  //--------------------------------------------------
  //--------------------------------------------------

  	//Синусоида (тут переключается шейдерная подпрограмма)
  shader.setUniform(Cube_Matrix_unif, Cube_Matrix);
  shader.UniformSubroutinesuiv(&Wave_Draw_Index);


  glBindBuffer(GL_ARRAY_BUFFER, sin_vert_vbo);
    glEnableVertexAttribArray(Attrib_vertex);
    glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);

    glEnableVertexAttribArray(Attrib_color);
    glVertexAttribPointer(Attrib_color, 3, GL_FLOAT, GL_FALSE,
  			6*sizeof(float), (void*)(3*sizeof(float)));


    //! Передаем данные на видеокарту(рисуем)
    	glLineWidth (0.1);
    	glDrawArrays(GL_LINE_STRIP, 0, 100); // 6 точек (наши три линии).

    glDisableVertexAttribArray(Attrib_vertex);
    glDisableVertexAttribArray(Attrib_color);



  //--------------------------------------------------
  //--------------------------------------------------
//   Cube_Matrix = glm::rotate(Cube_Matrix, 2.0f, vec3(1.0f, 0.0f, 0.0f));
//   shader.setUniform(Cube_Matrix_unif, Cube_Matrix);
//   shader.UniformSubroutinesuiv(&Cube_Subr_Index);
//
//  //! Подлючаем буфер с индексами вершин общий для цветов и их вершин
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_element);
//
//  //! ВЕРШИНЫ
//  //! Включаем массив атрибутов для вершин
//  glEnableVertexAttribArray(Attrib_vertex);
//    //! Подключаем VBO
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);
//      //! Указывая pointer 0 при подключенном буфере, мы указываем что данные в VBO
//      glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//  //! ЦВЕТА
//  //! Включаем массив атрибутов для цветов
//  glEnableVertexAttribArray(Attrib_color);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
//      glVertexAttribPointer(Attrib_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//
//  //! Передаем данные на видеокарту(рисуем)
//  glDrawElements(GL_TRIANGLES, Indices_count, GL_UNSIGNED_INT, 0);
//
//  //! Отключаем массив атрибутов
//  glDisableVertexAttribArray(Attrib_vertex);
//
//  //! Отключаем массив атрибутов
//  glDisableVertexAttribArray(Attrib_color);
//
//  checkOpenGLerror();

  glutSwapBuffers();
}

int triangle_shader_func(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Simple shaders");




  //! Обязательно перед инициализации шейдеров
  GLenum glew_status = glewInit();
  if(GLEW_OK != glew_status)
  {
     //! GLEW не проинициализировалась
    std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
    return 1;
  }

  //! Проверяем доступность OpenGL 2.0
  if(!GLEW_VERSION_2_0)
  {
     //! OpenGl 2.0 оказалась не доступна
    std::cout << "No support for OpenGL 2.0 found\n";
    return 1;
  }

  //! Инициализация
  initGL();
  initVBO();
  initShader();


  glutReshapeFunc(resizeWindow);
  glutDisplayFunc(render);
  glutTimerFunc(1, TimerFunction, 1);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  glutMouseFunc(mouseWheel);
  glutMainLoop();

  //! Освобождение ресурсов, хотя в нашем случаи сюда выполнение никогда не дойдет,
  // так, как управление не выйдет из glutMainLoop цикла
  freeVBO();
}
