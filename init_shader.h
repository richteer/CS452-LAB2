#ifndef _INIT_SHADER_H_
#define _INIT_SHADER_H_
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

int init_shader(char * filename, GLenum type)
{
	size_t filesize;
	char * filebuf;
	char log[100];
	int log_length;
	FILE * src = fopen(filename,"r");
	int ret;

	fseek(src,0,SEEK_END);
	filesize = ftell(src);
	rewind(src);	
	filebuf = malloc(sizeof(char) * filesize);

	ret = glCreateShader(type);
	glShaderSource(ret, 1, &filebuf, &filesize);
	glCompileShader(ret);

	glGetShaderInfoLog(ret,99,&log_length,log);

	if (log_length) {
		fprintf(stderr,"Shader compile error: %s\n",log);
		return -1;
	}

	fclose(src);
	free(filebuf);

	return ret;
}


#endif
