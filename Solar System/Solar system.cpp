#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>

#define BLACK 0, 0, 0

double rotateAngle, angle, angleDelta;		//radian
int sun = 0, earth = 0, moon = 0, day = 0;

#define PI 3.1416

void drawAxis() {
	glBegin(GL_LINES); {
		glColor3f(0, 1, 0);
		//Y axis
		glVertex3f(0, -150, 0);
		glVertex3f(0, 150, 0);

		//X axis
		glColor3f(0, 0, 1);
		glVertex3f(-150, 0, 0);
		glVertex3f(150, 0, 0);

		//Z axis
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, -150);
		glVertex3f(0, 0, 150);
	}glEnd();
}
/*glPushMatrix(); {
	} glPopMatrix();
*/
void display() {
	glClearColor(BLACK, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 200, 0, 0, 0, 0, 0, 1);
	//gluLookAt(100,100,100,	0,0,0,	0,0,1);

	drawAxis();
	glColor3f(1, 1, 1);

	//Drawing Ellipse
	glBegin(GL_LINES); {
		for (rotateAngle = 0; rotateAngle <= 2 * PI; rotateAngle = rotateAngle + angleDelta) {
			glVertex3f(40 * cos(rotateAngle), 32 * sin(rotateAngle), 0);
			glVertex3f(40 * cos(rotateAngle + angleDelta), 32 * sin(rotateAngle + angleDelta), 0);
		}
	}glEnd();

	//Drawing Sun
	glPushMatrix(); {
		glRotatef(sun, 0, 0, 1);		//Rotating on its own axis
		glutWireSphere(10, 10, 10);
	} glPopMatrix();

	//This translation will make earth to move along the ellipse, so no need to call glRotatef()
	glTranslatef(40 * cos(angle), 32 * sin(angle), 0);
	glPushMatrix(); {
		glRotatef(earth, 0, 0, 1);		//Rotating on its own axis
		glutWireSphere(5, 10, 10);
	} glPopMatrix();

	//Drawing Circle
	glBegin(GL_LINES); {
		for (rotateAngle = 0; rotateAngle <= 2 * PI; rotateAngle = rotateAngle + angleDelta) {
			glVertex3f(13 * cos(rotateAngle), 13 * sin(rotateAngle), 0);
			glVertex3f(13 * cos(rotateAngle + angleDelta), 13 * sin(rotateAngle + angleDelta), 0);
		}
	}glEnd();

	//This translation will make moon to move along the circle, so no need to call glRotatef()
	glTranslatef(13 * cos(angle), 13 * sin(angle), 0);

	/*
	* We also can use the two lines below, instead of above line, those two lines togather do
	* the same job as above line, so remove comment from next two lines and comment out the line
	* above to see the effect.
	*/

	//glRotatef(day, 0, 0, 1);
	//glTranslatef(13, 0, 0);

	glRotatef(moon, 0, 0, 1);			//Rotating on its own axis
	//Drawing Moon
	glutWireSphere(1.5, 10, 10);

	glutSwapBuffers();
}

void animate() {
	angle += angleDelta;				//rotate at 0.002 radians per frame

	day = (day + 1) % 360;
	sun = (sun + 1) % 360;
	earth = (earth + 1) % 360;
	moon = (moon + 1) % 360;
	glutPostRedisplay();
}

void init() {
	rotateAngle = angle = 0;
	angleDelta = 0.002;

	glClearColor(BLACK, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1.333333, 0.1, 10000.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Solar System");

	init();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	glutMainLoop();

	return 0;
}
