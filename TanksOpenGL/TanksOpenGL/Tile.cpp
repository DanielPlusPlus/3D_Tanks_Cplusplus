#include "Tile.h"

void Tile::render(void) {
	for (int i = 0; i < 8; i++) {
		glm::vec4 point(cubeVert[i * 3], cubeVert[i * 3 + 1], cubeVert[i * 3 + 2], 1.0f);
		point = transformationMatrix * point;
		cubeVert[i * 3] = point.x;
		cubeVert[i * 3 + 1] = point.y;
		cubeVert[i * 3 + 2] = point.z;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cubeVert);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, cubeNorm);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cubeCols);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubeInd);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	return;
}

void Tile::translate(const glm::vec3& translation) {
	transformationMatrix = glm::translate(transformationMatrix, translation);
	if (translation.z == 1.0f) {
		higher = true;
	}
	return;
}

void Tile::rotate(float angle, const glm::vec3& axis) {
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(angle), axis);
	return;
}

void Tile::scale(const glm::vec3& scaling) {
	transformationMatrix = glm::scale(transformationMatrix, scaling);
	return;
}

bool Tile::isColliding(float x, float y)  {
	if (!higher) return false;
	float left = transformationMatrix[3][0];
	float right = left + 1.0f;
	float top = transformationMatrix[3][1];
	float bottom = top - 1.0f;
	return x >= left && x <= right && y >= bottom && y <= top;
}

bool Tile::isHigher() {
	return higher;
}