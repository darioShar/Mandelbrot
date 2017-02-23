#pragma once
#include <string>
#include "FatalError.h"
#include <fstream>
#include <vector>
#include <glew/glew.h>

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void linkShaders();

		void compileShader(const std::string & filePath, GLuint id);

		void addAttribute(const std::string& attributeName);

		GLuint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};