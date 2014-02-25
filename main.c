#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "init_shader.h"

#define DERP 0
#define NOPE 1

unsigned int program;

void show_stuff(void)
{
	int vaoID,vboID;
	glClear(GL_COLOR_BUFFER_BIT);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	

	// DO OBJECT STUFF HERE
	GLfloat vertices[3*6] = {
		-0.25f,-0.5f,0.0f,
		-0.5f,0.0f,0.0f,
		-0.25f,0.5f,0.0f,
		0.25,0.5f,0.0f,
		0.5f,0.0f,0.0f,
		0.25,-0.5f,0.0f};


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_POLYGON, 0, 3*6 );


	glFlush();

}


void init(void)
{
	GLuint vs,fs;
	char log[1000];
	int loglen;

	// Initialize the shader program
	program = glCreateProgram();
	vs = init_shader("vertexshader.glsl", GL_VERTEX_SHADER); // Prepare the vertex shader
	if (vs <= 0) exit(NOPE);

	fs = init_shader("fragmentshader.glsl", GL_FRAGMENT_SHADER); // Prepare the fragment shader
	if (fs <= 0) exit(NOPE);

	// Attach the shaders to the program
	glAttachShader(program,vs);
	glAttachShader(program,fs);

	// Prep the program for use
	glLinkProgram(program);
	
	// Error checking
	glGetProgramInfoLog(program, 1000, &loglen,log);
	if (loglen) {
		fprintf(stderr,"Link Program Failed: %s\n",log);
		exit(NOPE);
	}

	// If we haven't failed yet, use the program in rendering	
	glUseProgram(program);

}

int main(int argc, char ** argv)
{
	
	glutInit(&argc,argv);
	glutCreateWindow("Lab 2");

	glutInitContextVersion(4,3);
	glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_COMPATIBILITY_PROFILE);

	init();
	
	glutDisplayFunc(show_stuff);
	glutMainLoop();

	return DERP;
}
