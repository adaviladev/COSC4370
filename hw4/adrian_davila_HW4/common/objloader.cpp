#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

#include <glm/glm.hpp>

#include "objloader.hpp"

using namespace glm;
using namespace std;

bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec3> & out_normals, std::vector<glm::vec4> & out_colors) {
	printf("Loading OBJ file %s...\n", path);

	fstream fin(path);
	string txtLine;

	int ctr = 0;
	getline(fin, txtLine);
	int polygonCount = atoi(txtLine.c_str());
	while (getline(fin, txtLine)) {
		if (txtLine == "") {
			continue;
		}
		float x, y, z, nx, ny, nz, r, g, b, a;
		stringstream ss;
		ss << txtLine << endl;
		ss >> x;
		ss >> y;
		ss >> z;
		ss >> nx;
		ss >> ny;
		ss >> nz;
		ss >> r;
		ss >> g;
		ss >> b;
		ss >> a;

		out_vertices.push_back(vec3(x, y, z));
		out_normals.push_back(vec3(nx, ny, nz));
		out_colors.push_back(vec4(r, g, b, a));
	}

	return true;
}


#ifdef USE_ASSIMP // don't use this #define, it's only for me (it AssImp fails to compile on your machine, at least all the other tutorials still work)

// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

bool loadAssImp(
	const char * path,
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
) {

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

											// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}


	// Fill face indices
	indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i<mesh->mNumFaces; i++) {
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

#endif