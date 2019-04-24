#pragma once
#include"Mesh.h"
#include"Material.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<vector>
#include "Camera.h"
#include "LightMgr.h"

class Model
{
public:
	vector<Mesh>  meshes;
	vector<Material*> materialList;
	void Draw(Camera *camera, LightMgr &light);
	Model(string modelPath, vector< Material* > materialList);
	~Model();

private:
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};


