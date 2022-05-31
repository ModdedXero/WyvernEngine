#pragma once

#include <Wyvern/Core/Math/Vector.h>

#include <vector>

namespace Wyvern
{
	struct Mesh
	{
	public:
		std::vector<Vector3> vertices;
		std::vector<Vector2> uvs;
		std::vector<int> indices;

		Mesh()
		{
			std::vector<Vector3> vertices = {
	{-0.5f, -0.5f, -0.5f },
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},

	{-0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f, -0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},

	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},

	{-0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f, -0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{ 0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f,  0.5f},
	{-0.5f, -0.5f, -0.5f},

	{-0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f, -0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{ 0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f,  0.5f},
	{-0.5f,  0.5f, -0.5f},
			};
			std::vector<Vector2> uvs = {};
			std::vector<int> indices = {
				0, 1, 2,
				2, 3, 0,
				4, 5, 3,

				6, 7, 8,
				8, 9, 6,
				10, 11, 9,

				12, 13, 14,
				14, 15, 12,
				16, 17, 15,

				18, 19, 20,
				20, 21, 18,
				22, 23, 21,

				24, 25, 26,
				26, 27, 24,
				28, 29, 27,

				30, 31, 32,
				33, 34, 30,
			};

			this->vertices = vertices;
			this->uvs = uvs;
			this->indices = indices;
		}
	};
}