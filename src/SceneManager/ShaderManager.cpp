/*
 * File:   ShaderManager.cpp
 * Author: daddy
 *
 * Created on September 29, 2013, 12:40 PM
 */

#include "ShaderManager.h"
#include <iostream>
#include <fstream>
#include <vector>

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Initialize()
{


}

GLuint ShaderManager::LoadProgramFromFile(std::string name, std::string vertexShader, std::string fragmentShader)
{
	std::string VertexShaderCode;
	std::ifstream VertexShaderFile(vertexShader.c_str(), std::ios::in);
	if(VertexShaderFile.is_open())
  {
		std::string Line = "";
		while(getline(VertexShaderFile, Line))
		{
		  VertexShaderCode += "\n" + Line;
		}

		VertexShaderFile.close();
	}
	else
  {
		printf("Could not open %s", vertexShader.c_str());
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderFile(fragmentShader.c_str(), std::ios::in);
	if(FragmentShaderFile.is_open())
  {
		std::string Line = "";
		while(getline(FragmentShaderFile, Line))
    {
      FragmentShaderCode += "\n" + Line;
    }
		FragmentShaderFile.close();
	}
	else
  {
		printf("Could not open %s", fragmentShader.c_str());
		return 0;
	}

	return LoadProgram(name, VertexShaderCode, FragmentShaderCode);
}

GLuint ShaderManager::LoadProgram(std::string name, std::string vertexShaderCode, std::string fragmentShaderCode, std::string vertexShaderName, std::string fragmentShaderName)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLint Result = GL_FALSE;
	int InfoLogLength;

	char const * VertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	char const * FragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	if (ProgramID > 0)
  {
      programs[name] = {ProgramID, vertexShaderCode, fragmentShaderCode};
  }

	return ProgramID;

}
