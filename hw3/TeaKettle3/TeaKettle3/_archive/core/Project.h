#pragma once

class Project {
public:
	Project(
		GLuint VertexShaderId,
		GLuint FragmentShaderId,
		GLuint ProgramId,
		GLuint VaoId,
		GLuint VboId,
		GLuint ColorBufferId,
		GLuint NormalBufferId,
		GLuint MVPMatrixID,
		GLuint NormalMatrixID,
		GLuint ModelViewMatrixID,
		GLuint LightArrayID);
	~Project();
	void Initialize(int, char*[]);
	void InitWindow(int, char*[]);
	void ResizeFunction(int, int);
	void RenderFunction(void);

	void CreateShaders(const GLchar* vs, const GLchar* fs);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void viewChange(unsigned char key, int xmouse, int ymouse);

	void Cleanup(void);
	void CreateVBO();
	void DestroyVBO(void);
	void DestroyShaders(void);
};