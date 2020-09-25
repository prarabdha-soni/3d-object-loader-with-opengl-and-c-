#include <cstring>
#include <GL/glut.h>
#include<vector>
#include<string>
#include <math.h>
#include<stdio.h>
using namespace std;

// Trying to implement functions of Chapter 2,3,4 eg.lighting

// Used Redbook and orange book as a referene.

/*
At last in  main() used function used like :-
tDisplayMode
glutInitWindowSize
glutInitWindowPosition
glutCreateWindow
glutReshapeFunction
glutDisplayFunction
glutKeyboardFunction
glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
glLightModelfunction.

*/


extern double ms,pr,fps,rt; // declaring or intializing parameters
extern float lx,lz,x,z,angle;
extern GLuint dlist;
extern int imageNo,opt2;
extern GLfloat angleR,angleZ;
void clearp_data();
void mixedStepLoop();
void processSpecialKeys(int , int , int );
void draw();
void initialOBJ();                                       // initialisation
void objDraw();
void optimisationList();


class data
{
public:
float v[3];
float vn[3];        // Vertex,Normal
float tex[3];

data()
	{
		v[0]=0;v[1]=0;v[2]=0;vn[0]=0;vn[1]=0;vn[2]=0;tex[0]=0;tex[1]=0;tex[2]=0;
	}
};
extern class data p;
vector<data> p_data;

float vtemp,vntemp,vttemp;
vector<float> v;
vector<float> vn;
vector<float> vt;

int i,j;
char line[60];

void clearp_data()
{
	p_data.clear();
}
void initialOBJ()
{

FILE *fp;
fp=fopen("temp.obj","r");

	while(!(feof(fp)))
	{
		i=0;
		fscanf(fp,"%s",line);

		if(line[0]=='v'&&line[1]!='n'&&line[1]!='t')
		{
			while(i<3)
			{
			fscanf(fp,"%f",&vtemp);
			v.push_back(vtemp);
			i++;
			}
		}
		
		else if(line[0]=='v'&&line[1]=='n')
		{
		
			while(i<3)
			{
			fscanf(fp,"%f",&vntemp);
			vn.push_back(vntemp);
			i++;
			}

			
		}
		else if(line[0]=='v'&&line[1]=='t')
		{
			while(i<3)
			{
			fscanf(fp,"%f",&vttemp);	
			vt.push_back(vttemp);
			i++;
			}

		}

		
	}
	 fclose(fp);
	

}

void objDraw()
{
dlist=glGenLists(1);
 FILE *fp2;
 fp2=fopen("temp.obj","r");
 int eq;
 char ch[10];

 while(!(feof(fp2)))
 {	
 	i=0;
 	fscanf(fp2,"%s",line);
	if(line[0]=='f')
	{	

		while(i<3)	
		{
			
			fscanf(fp2,"%d%s",&eq,line);
			eq=eq*3;
			p.v[0]=v[eq];
			p.v[1]=v[eq+1];
			p.v[2]=v[eq+2];
			i++;
			
		
			while(j<strlen(line))
			{
			ch[j]=line[j+2];
			j++;
			}
			ch[j]='\0';

			eq=atoi(ch);
			eq--;
			eq=eq*3;
			j=0;
			p.vn[0]=vn[eq];
			p.vn[1]=vn[eq+1];
			p.vn[2]=vn[eq+2];

		  p_data.push_back(p);
		}
	} 	

 }
 fclose(fp2);
 v.clear();
 vn.clear();
 vt.clear();
}


void optimisationList()
{

glNewList(dlist, GL_COMPILE);

glBegin(GL_TRIANGLES);
for(i=0;i<p_data.size();i++)
{
glNormal3f(p_data[i].vn[0],p_data[i].vn[1],p_data[i].vn[2]);
glVertex3f(p_data[i].v[0],p_data[i].v[1],p_data[i].v[2]);     // vertex3f and normal3f as taught in class
}
glEnd();

glEndList();
}
void mixedStepLoop()
{
    double now = glutGet(GLUT_ELAPSED_TIME);
    double timeElapsedMs =(now-pr);
    ms += timeElapsedMs ;
    while(ms >= rt) 
    {
     
        ms -= rt;
        glutPostRedisplay();
    }
    pr=now;
}



void update()
{
  angleR=angleR+0.5;
    if(angleR>360)
      angleR=0;
}

GLfloat objcolor[]={0.5f,0.5f,0.5f,1.f}; 
GLfloat white[]={1.0f,1.0f,1.0f,1.f};


float diffuseLight[] =
{ 0.8f, 0.8f, 0.8f, 1.0f };
float specularLight[] =
{ 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[] =
{ 0.0f, 20.0f, 2.0f, 1.0f };
float local_view[] =
{ 0.0 };
 

void OnInit()
{
 
  glEnable(GL_LIGHTING); 
 
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0f);
 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
 
 
  glEnable(GL_LIGHT0);
 

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, objcolor);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
}
 void deleteInitial()
{
system("rm temp.obj");
}

GLfloat light0_position[] = {0,0,1.0, 0.0};

void draw()
{


	if(opt2!=1)
  {

 
glEnable(GL_NORMALIZE);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);  
glLightfv(GL_LIGHT0, GL_POSITION, light0_position); 
glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objcolor);

    opt2=1;
    glClearColor (0.0,0.0,0.0,1.0); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(  x, 1.0f, z,
				x+lx, 1.0f, z+lz,
				0.0f, 1.0f, 0.0f);

   	glPushMatrix();
   
    	initialOBJ();
    	objDraw();
    	optimisationList();
    	deleteInitial();
   	glPopMatrix();
   	glutSwapBuffers();
 	}
  else
  {

    glClearColor (0.0,0.0,0.0,1.0); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(  x, 1.0f, z,
        x+lx, 1.0f, z+lz,
        0.0f, 1.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glPushMatrix();
  
    glScalef(0.4,0.4,0.4);
 
    glRotatef(angleR,0,1,0);
    glRotatef(angleZ,1,0,0);                   // Rotating along co-ordinates
    glCallList(dlist);
    glPopMatrix();
    glutSwapBuffers();
  }

}



float lx=0.0f,lz=-1.0f;

float x=0.0f,z=5.0f;

float angle = 0.0f;

void processSpecialKeys(int key, int xx, int yy)
{

switch(key) {
case GLUT_KEY_LEFT:
 angleR=angleR-2;
  break;
case GLUT_KEY_RIGHT:
 angleR=angleR+2;
  break;
case GLUT_KEY_UP:
angleZ+=2; 
 break;
case GLUT_KEY_DOWN:
angleZ-=2;
break;
}

if(angleR>360)
  angleR=0;
if(angleZ>360)
  angleZ=0;
}




GLfloat angleR,angleZ;
int opt2;
class data p;
double ms,pr,fps,rt;
GLuint dlist;
int imageNo,elements;

void initialSetup()
{
	elements=0;
	FILE *filename;
	char temp[50];
	vector<string> name;
	system("(ls | grep .obj)>filelist");
	filename=fopen("filelist","r");

	while(!(feof(filename)))
	{	
		elements++;
		fscanf(filename,"%s",temp);
		name.push_back(temp);
	}

	string systemtext = "cp " + name[imageNo] + " temp.obj";
	system(systemtext.c_str());
	fclose(filename);
	system("rm filelist");
}


void handleResize(int w,int h)
{
    glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	glViewport(0,0,w,h);
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

}

void processKeyboard(unsigned char key,int x,int y)
{

if(key==65||key==97)
{
	if(imageNo!=0)
	imageNo--;
}
if(key==68||key==100)
{	
	if(imageNo<(elements-2))
	imageNo++;

}

opt2=0;
clearp_data();
angleR=0;angleZ=0;
initialSetup();
}

int main(int argc, char** argv)
{

	ms=0;
	pr=0;
	fps=60;
	rt=(1/fps)*1000;

initialSetup();
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
glutInitWindowSize(800,800);
glutInitWindowPosition(100,100);
glutCreateWindow("OBJ Loader");
glutReshapeFunc(handleResize);
glutDisplayFunc(draw);
glutIdleFunc(mixedStepLoop);
glutSpecialFunc(processSpecialKeys);
glutKeyboardFunc(processKeyboard);
glEnable(GL_DEPTH_TEST);
glutMainLoop();
}

