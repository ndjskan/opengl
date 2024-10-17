#include <glad/glad.h>
#include <GLFW/glfw3.h>
const char* vertex_shader_source =
"#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 mycolor;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x,aPos.y, 0, 1);\n"
"    mycolor=aColor;\n"
"}\n";

const char* fragment_shader_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 mycolor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(mycolor,1.0);\n"
"}\n";


int main()
{
	float triangle[] =
	{
	    -0.25,0.25,   0.0,1.0,1.0,
		0.25,-0.25,   1.0,0.0,1.0,
		-0.25,-0.25,  1.0,1.0,0.0,
	}; const int size = sizeof(triangle) / 4;
	
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(window_x, window_y, "opengl", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	gladLoadGL();
	glViewport(0, 0, window_x, window_y);
	int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1 , &vertex_shader_source,NULL);
	glCompileShader(vertexshader);
	int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragmentshader);
	int shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	GLuint VAO, VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * 4, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * 4, (void*)(2*4));
	glEnableVertexAttribArray(1);
	glUseProgram(shaderprogram);
	glBindVertexArray(VAO);
  
	while (glfwWindowShouldClose(window)==false) 
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glBufferData(GL_ARRAY_BUFFER, size, final, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, (size / 4) / 2);
	}
	
	return 0;
}
