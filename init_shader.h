#ifndef _INIT_SHADER_H_
#define _INIT_SHADER_H_
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_SIZE 1024

int init_shader(char * filename, GLenum type)
{
	size_t filesize;			// Size of the shader source
	char * filebuf;				// Buffer to store the shader source in
	char log[LOG_SIZE + 1];			// Error log
	int log_length;				// Size of the error log
	FILE * src = fopen(filename,"r");	// Shader file
	int ret;				// Return value, shader ID


	// Find get the total size of the source
	fseek(src,0,SEEK_END);
	filesize = ftell(src);
	rewind(src);

	// Create the source buffer, load the source into memory
	filebuf = malloc(sizeof(char) * filesize);
	fread(filebuf,1,filesize,src);

	// Create the shader, returns 0 if error
	ret = glCreateShader(type);

	// Pass in the source for compliation
	glShaderSource(ret, 1, &filebuf, &filesize);
	glCompileShader(ret);

	// Check for errors
	glGetShaderInfoLog(ret,LOG_SIZE,&log_length,log);

	// Return an error code if compilation failed
	if (log_length) {
		fprintf(stderr,"Shader '%s' compile error: %s\n",filename,log);
		return -1;
	}

	// Cleanup: free buffer, close file
	fclose(src);
	free(filebuf);

	return ret;
}


#endif
