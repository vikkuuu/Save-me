#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h> 
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
int z1=0;

int c=0;

GLfloat arr[2][150];

int foodx[25];
int foody[25];
int F=0;
int P=0;
int poisonx[25];
int poisony[25];

void makesquare()
{
	glColor3f(0,0,1);
	glPushMatrix();
	//glTranslatef(ax*100,by*100,0);
	glBegin(GL_POLYGON);
	glVertex2f(A+ax*5,B+by*5);
	glVertex2f(A+by*10,B+ax*10);
	glVertex2f(A+ax*25,B+by*25);
	glVertex2f(A-by*10,B-ax*10);
	glEnd();
	glPopMatrix();
}

void maketail()
{
	int ta,tb;
	glPointSize(5);
	glColor3f(1,1,0);
	glPushMatrix();
	//glTranslatef(ax*100,by*100,0);
    glBegin(GL_POINTS);
	for(int i=0;i<150;i++)
	{		
       ta=arr[0][i];
       tb=arr[1][i];
		glVertex2f(ta,tb);
	}
	glEnd();
	glPointSize(1);
	glPopMatrix();
}

bool check_collision(int posx,int posy)
{
	for(int i=0;i<P;i++)
		if((posx<poisonx[i]+45&&posx>poisonx[i]-45)||((posy<poisony[i]+75&&posx>poisony[i]-75)))
			return true;

	for(int i=0;i<F;i++)
		if((posx<foodx[i]+45&&posx>foodx[i]-45)||((posy<foody[i]+75&&posy>foody[i]-75)))
			return true;

	return false;
}

void Create()
{
	int choice=rand()%2;

	if(F<10&&choice==1)
	{
		while(1)
		{
			int posx=rand()%1366;
			if(posx<15)
				posx=15;
			if(posx>1351)
				posx=1351;

			int posy=768+rand()%1000;

			if(!check_collision(posx,posy))
			{
				foodx[F]=posx;
				foody[F]=posy;
				F++;
				break;
			}
		}
	}
	if(P<10&&choice==0)
	{
		while(1)
		{
			int posx=rand()%1366;
			if(posx<15)
				posx=15;
			if(posx>1351)
				posx=1351;

			int posy=768+rand()%1000;

			if(!check_collision(posx,posy))
			{
				poisonx[P]=posx;
				poisony[P]=posy;
				P++;
				break;
			}
		}
	}
}

void makefood()
{
	for(int i=0;i<F;i++)
	{
		glColor3f(0,1,0);
		glBegin(GL_POLYGON);
		glVertex2f(foodx[i]-15,foody[i]-15);
		glVertex2f(foodx[i]+15,foody[i]-15);
		glVertex2f(foodx[i]+15,foody[i]+15);
		glVertex2f(foodx[i]-15,foody[i]+15);
		glEnd();
	}

	for(int i=0;i<F;i++)
	{
		if(foody[i]>0)
			foody[i]-=1;
		else
		{
			while(1)
			{
				int posx=rand()%1366;
				if(posx<15)
				posx=15;
				if(posx>1351)
					posx=1351;

				int posy=768+rand()%1000;

				if(!check_collision(posx,posy))
				{
					foodx[i]=posx;
					foody[i]=posy;
					break;
				}
			}
		}
	}
}

void makepoison()
{
	for(int i=0;i<P;i++)
	{
		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
		glVertex2f(poisonx[i]-15,poisony[i]-15);
		glVertex2f(poisonx[i]+15,poisony[i]-15);
		glVertex2f(poisonx[i]+15,poisony[i]+15);
		glVertex2f(poisonx[i]-15,poisony[i]+15);
		glEnd();
	}

	for(int i=0;i<P;i++)
	{
		if(poisony[i]>0)
			poisony[i]-=1;
		else
		{
			while(1)
			{
				int posx=rand()%1366;
				if(posx<15)
				posx=15;
				if(posx>1351)
					posx=1351;

				int posy=768+rand()%1000;

				if(!check_collision(posx,posy))
				{
					poisonx[i]=posx;
					poisony[i]=posy;
					break;
				}
			}
		}
	}
}

void Collision()
{
	for(int i=0;i<F;i++)
	{
		if(((A+5<foodx[i]+15&&A+5>foodx[i]-15)||(A-5<foodx[i]+15&&A-5>foodx[i]-15))&&((B+5<foody[i]+15&&B+5>foody[i]-15)||(B-5<foody[i]+15&&B-5>foody[i]-15)))
		{
			cout<<1;
			while(1)
			{
				int posx=rand()%1366;
				if(posx<15)
				posx=15;
				if(posx>1351)
					posx=1351;

				int posy=768+rand()%1000;

				if(!check_collision(posx,posy))
				{
					foodx[i]=posx;
					foody[i]=posy;
					break;
				}
			}
		}
	}
	for(int i=0;i<P;i++)
	{
		if(((A+5<poisonx[i]+15&&A+5>poisonx[i]-15)||(A-5<poisonx[i]+15&&A-5>poisonx[i]-15))&&((B+5<poisony[i]+15&&B+5>poisony[i]-15)||(B-5<poisony[i]+15&&B-5>poisony[i]-15)))
		{
			cout<<2;
			exit(0);
		}
	}
}

void mydisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1,1,1,0);

	Create();

	makefood();
	makepoison();

	Collision();

	makesquare();
    maketail();
    
	if(Z==0)
	{
		glClearColor(1,0,0,0);

	}

	glFlush();
}

void Mymouse(int button,int state,int x,int y)
{

	//cout<<x<<" "<<y<<endl;
	a=x;
	b=y;
	glutPostRedisplay();
}

void motionmouse(int x,int y)
{
	// cout<<x<<" "<<y<<endl;

	 a=x;
	b=y;
	glutPostRedisplay();
}


void passivemotion(int x,int y)
{
	//cout<<x<<" "<<y<<endl;

	a=x;
	b=y;
	glutPostRedisplay();
}

void init()
{
    glLoadIdentity();
    glOrtho(0,1366,768,0,-1,1);
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
	glutPostRedisplay();
}

void chase()
{
	float D=sqrt(((a-A)*(a-A))+(b-B)*(b-B));

    ax=(a-A)/D;
    by=(b-B)/D;

  //  cout<<ax<<" "<<by<<endl;

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
	else
     chase();
	
	glutTimerFunc(3,Time,0);
}



int main(int argc,char **argv)
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
   glutInitWindowSize(1366,768);
   glutCreateWindow("CAUGHT ME");
   init();
   glutDisplayFunc(mydisplay);
   glutTimerFunc(1000,Time,0);
   glutSetCursor(9);
   glutMouseFunc(Mymouse);
   glutMotionFunc(motionmouse);
   glutPassiveMotionFunc(passivemotion);
   glutMainLoop();
   return 0;
}
