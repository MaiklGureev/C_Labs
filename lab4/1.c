#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

const float RAND_MAX_F = RAND_MAX;
 
float get_rand() {
	 
    return rand() / RAND_MAX_F;
}

float get_rand_range(const float min, const float max) {
    return get_rand() * (max - min) + min;
}

void drawBox(float x, float y, float w, float h, float r, float g, float b){

	glColor3f(r, g, b);
	
	glBegin(GL_POLYGON);
		
	//верх
	glVertex3f(-w+x,h+y,0);	
	glVertex3f(w+x,h+y,0);
	
	//основание
	glVertex3f(w+x,-h+y,0.0);
	glVertex3f(-w+x,-h+y,0.0);
	
	glEnd();
	
	}
	
void drawCircle(float x, float y, float s, float r,float g, float b){
	glLineWidth(10.0);

	glColor3f(r, g, b); 
	
	glBegin(GL_POLYGON);
	

		for (int i=0;i<50;i++) {
		float angle = 2*3.14*i/50;
		glVertex2f(cos(angle)*s+x, sin(angle)*s+y);
		}
	
	glEnd();
	
	}	

void drawGrass(float x, float y, float s, float interval, int count ){
	
	x -= interval;
	
	for (int i=0;i<count;i++) {
		srand(time(NULL));
		float k = get_rand_range(0,1);
		srand(time(NULL));
		float j = get_rand_range(0,1);

		glBegin(GL_POLYGON);
		glColor3f(0.67, 1.0, 0.18);
		glVertex3f(1*s/8+x+interval,1*s+y,0);
		glVertex3f(1*s/4+x+interval,-1*s+y,0);	
		glVertex3f(-1*s/4+x+interval,-1*s+y,0);
		glEnd();
		x += interval;	
		}
	}

void display(void) {

  glClearColor(0.68, 0.76, 0.86, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_NORMALIZE);  
  glEnable(GL_COLOR_MATERIAL);    // Разрешить материал
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  
	//зелёный фон травы
	glColor3f(0.13, 0.54, 0.13);
	glBegin(GL_POLYGON);
	
	glVertex3f(1,-0.5,0);
	glVertex3f(-1,-0.5,0);	
	glVertex3f(-1,-1,0.0);
	glVertex3f(1,-1,0.0);
	glEnd();
	
	//ствол
	drawBox(0.65,-0.3,
			0.1,0.3,
			0.54,0.26,0.0);				
	
	//листья
	drawCircle(0.5,0.2,0.2, 0.19,0.8,0.19);
	drawCircle(0.8,0.2,0.2, 0.19,0.8,0.19);
	drawCircle(0.8,0.5,0.3, 0.19,0.8,0.19);
	drawCircle(0.5,0.5,0.3, 0.19,0.8,0.19);
	drawCircle(0.65,0.1,0.15, 0.19,0.8,0.19);
	
	float v = 0;
	for(int i =0;i<=7;i++){
	//трава
	drawGrass(-0.98,-0.5+v,0.04,0.03,100);
	v -=0.02;
	drawGrass(-1,-0.5+v,0.05,0.04,100);
	v -=0.02;
	drawGrass(-0.98,-0.5+v,0.05,0.04,100);
	v -=0.02;
	}


	drawCircle(0,0.75,0.13, 0,0.74,1);
	drawCircle(-0.15,0.77,0.11, 0,0.74,1);
	drawCircle(-0.15,0.73,0.12, 0,0.74,1);
	drawCircle(-0.32,0.75,0.14, 0,0.74,1);
	
	drawCircle(-0.4,0.35,0.12, 0,0.74,1);
	drawCircle(-0.55,0.37,0.13, 0,0.74,1);
	drawCircle(-0.55,0.33,0.14, 0,0.74,1);
	drawCircle(-0.72,0.35,0.13, 0,0.74,1);


	
	
    
  

    glutSwapBuffers();/*Во-вторых после рисования нужно попросить OpenGL сменить экранные буфера при помощи glutSwapBuffers (),
     ведь у нас включена двойная буферизация. Все рисуется на скрытом от пользователя буфере и затем происходит смена буферов. 
     Делается это для получения плавной анимации и для того, чтобы не было эффекта мерцания экрана.*/
    glFlush();
}
void main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (500, 500);
    glutCreateWindow ("Image");

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glEnable(GL_NORMALIZE);

    glutDisplayFunc(display);
    glutMainLoop ();
}
