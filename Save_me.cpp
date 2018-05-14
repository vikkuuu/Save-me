#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

GLfloat A=30;
GLfloat B=300;

GLfloat a=0;
GLfloat b=0;

GLfloat ax=0;
GLfloat by=0;

float w=0;
float k=0;
float s=0;
int j=1;
int Z=1;

int c=0;

GLfloat arr[2][150];



void makesquare()
{
	glColor3f(0,0,1);

	glBegin(GL_POLYGON);
	glVertex2f(A+ax*5,B+by*5);
	glVertex2f(A+by*10,B+ax*10);
	glVertex2f(A+ax*25,B+by*25);
	glVertex2f(A-by*10,B-ax*10);
	glEnd();
}

void maketail()
{
	int ta,tb;

	//float p=10;

	glPointSize(5);
	glColor3f(1,1,0);

    glBegin(GL_POINTS);
	for(int i=0;i<150;i++)
	{
		
       ta=arr[0][i];
       tb=arr[1][i];

	
	glVertex2f(ta,tb);

	//p=p-(i/10);
	
	}

	glEnd();

	glPointSize(1);
}


void mydisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1,1,1,0);

    //glPushMatrix();

    
    //glTranslatef(k,0,0);
   // glScalef(w/1000,w/1000,1);
    


    //glTranslatef(A+10,B+10,0);
    //glScalef(s,s,1);
    //glRotatef(w,0,0,1);
    //glTranslatef(-(A+10),-(B+10),0);

    makesquare();
    maketail();

    //glPopMatrix();
    
	if(Z==0)
	{
		glClearColor(1,0,0,0);

	}

	glFlush();

	
}

void Mymouse(int button,int state,int x,int y)
{

	cout<<x<<" "<<y<<endl;
	//A=x;
	//B=y;
    
    //glutSwapBuffers();
	//glutPostRedisplay();
}

void motionmouse(int x,int y)
{
	 cout<<x<<" "<<y<<endl;

	// A=x;
	//B=y;

    // glutSwapBuffers();
	//glutPostRedisplay();
}


void passivemotion(int x,int y)
{
	cout<<x<<" "<<y<<endl;

	a=x;
	b=y;

    //glutSwapBuffers();
	glutPostRedisplay();
}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1,1,1,0);

    
	//glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();

    glOrtho(0,1366,768,0,-1,1);

    //glMatrixMode(GL_MODELVIEW);

    for(int i=0;i<150;i++)
    {
    	arr[0][i]=0;
    	arr[1][i]=0;
    }

}

void FUN()
{   
	if(w<360)
	w=w+0.1;

   else
   	w=0;

   k=k+0.01;

   if(j==1)
    {  s=s+0.1;
       if(s>=3)
       	j=0;
   }
   else
   	{  s=s-0.1;
       if(s<=3)
       	j=1;
   }

	//glutSwapBuffers();

	glutPostRedisplay();
}

void chase()
{
	float D=sqrt(((a-A)*(a-A))+(b-B)*(b-B));

    ax=(a-A)/D;
    by=(b-B)/D;

    arr[0][c]=A;
    arr[1][c]=B;

    c++;

    if(c>149)
    	c=0;

    A=A+ax;
    B=B+by;


    if(w<360)
	w=w+1;

   else
   	w=0;


    if(a>=A-5&&a<=A+5&&b<=B+5&&b>=B-5)
    {
        Z=0;
    }

    glutPostRedisplay();
}


void Time(int value)
{
	if(Z==0)
	{

	}

	//FUN();
	//glutIdleFunc(chase);
		else
     chase();
	
	glutTimerFunc(3,Time,0);
}



int main(int argc,char **argv)
{
   int ID;

   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
   glutInitWindowSize(1366,768);
   //glutInitWindowPosition(100,100);
   ID=glutCreateWindow("CAUGHT ME");

   init();

   glutDisplayFunc(mydisplay);
   glutTimerFunc(1000,Time,0);
    glutSetCursor(9);
   glutMouseFunc(Mymouse);
   //glutMotionFunc(motionmouse);
   glutPassiveMotionFunc(passivemotion);

   glutSetWindow(ID);

   //glutIdleFunc(chase);


  // glutCreateSubWindow(ID,500,500,100,100);

   printf("%u",ID);

   glutMainLoop();

   return 0;

}
