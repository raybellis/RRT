/*
 *  primitive/mesh.cpp
 *  RRT
 *
 *  Created by Ray Bellis on 08/02/2015.
 *  Copyright 2015 Ray Bellis. All rights reserved.
 *
 */

#include <iostream>
#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include <rrt/math.h>
#include "mesh.h"

static point3 toPoint(const aiVector3D& v)
{
	return point3(v[0], v[1], v[2]);
}

static vector3 toVector(const aiVector3D& v)
{
	return vector3(v[0], v[1], v[2]);
}

mesh::mesh(const std::string& filename)
{
	using namespace Assimp;

	Importer	importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT, nullptr);
	importer.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE, true, nullptr);
	importer.SetExtraVerbose(true);
	const aiScene *scene = importer.ReadFile(filename,
		aiProcess_ConvertToLeftHanded |
		aiProcess_SortByPType |
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_PreTransformVertices |
		aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);

	if (!scene) {
		throw std::runtime_error(importer.GetErrorString());
	}

	if (scene->mNumMeshes < 1) {
		throw std::runtime_error("no meshes found");
	}

	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		compound *c = new compound();
		auto mesh = scene->mMeshes[m];
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& f = mesh->mFaces[i];
			if (f.mNumIndices != 3) continue;

			const auto *x = f.mIndices;
			const auto *p = mesh->mVertices;
			const auto *n = mesh->mNormals;
			*c += new triangle(
					toPoint(p[x[0]]), toPoint(p[x[1]]), toPoint(p[x[2]]),
					toVector(n[x[0]]), toVector(n[x[1]]), toVector(n[x[2]]));
		}
		*this += c;
		std::cout << "mesh[" << m << "] loaded with " << mesh->mNumFaces << " faces and " << mesh->mNumVertices << " vertices" << std::endl;
	}
}
