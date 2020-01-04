#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "VItem.h"


class Utils
{
public:
	static int AddTriangle(
		float* points, int id,
		float x0, float y0, float z0,
		float x1, float y1, float z1,
		float x2, float y2, float z2)
	{
		points[id] = x0;
		id++;
		points[id] = y0;
		id++;
		points[id] = z0;
		id++;
		points[id] = x1;
		id++;
		points[id] = y1;
		id++;
		points[id] = z1;
		id++;
		points[id] = x2;
		id++;
		points[id] = y2;
		id++;
		points[id] = z2;
		id++;
		return id;
	}

	static void Bind(VItem& item, std::vector<float> points)
	{
		item.points = points;

		glGenVertexArrays(1, &(item.vao));
		glGenBuffers(1, &(item.vbo));
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(item.vao);

		glBindBuffer(GL_ARRAY_BUFFER, item.vbo);
		glBufferData(GL_ARRAY_BUFFER, item.points.size() * sizeof(float), item.points.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	static void Draw(VItem item)
	{
		glBindVertexArray(item.vao);
		glDrawArrays(GL_TRIANGLES, 0, item.points.size() * sizeof(float));
	}
};

