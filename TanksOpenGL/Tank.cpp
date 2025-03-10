#include "Tank.h"

void Tank::render(void) {
	for (int i = 0; i < 8; i++) {
		glm::vec4 point(truckVert[i * 3], truckVert[i * 3 + 1], truckVert[i * 3 + 2], 1.0f);
		point = transformationMatrix * point;
		truckVert[i * 3] = point.x;
		truckVert[i * 3 + 1] = point.y;
		truckVert[i * 3 + 2] = point.z;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, truckVert);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, truckNorm);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, truckCols);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, truckInd);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glm::mat4 transformationMatrix2 = glm::translate(transformationMatrix, glm::vec3(0.1f, -0.1f, 0.0f));
	for (int i = 0; i < 8; i++) {
		glm::vec4 point(hullVert[i * 3], hullVert[i * 3 + 1], hullVert[i * 3 + 2], 1.0f);
		point = transformationMatrix2 * point;
		hullVert[i * 3] = point.x;
		hullVert[i * 3 + 1] = point.y;
		hullVert[i * 3 + 2] = point.z;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, hullVert);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, hullNorm);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, hullCols);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, hullInd);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glm::mat4 transformationMatrix3 = glm::translate(transformationMatrix, glm::vec3(0.3f, -0.2f, -0.0f));
	for (int i = 0; i < 8; i++) {
		glm::vec4 point(gunVert[i * 3], gunVert[i * 3 + 1], gunVert[i * 3 + 2], 1.0f);
		point = transformationMatrix3 * point;
		gunVert[i * 3] = point.x;
		gunVert[i * 3 + 1] = point.y;
		gunVert[i * 3 + 2] = point.z;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, gunVert);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, gunNorm);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, gunCols);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, gunInd);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	return;
}

void Tank::translate(const glm::vec3& translation) {
	transformationMatrix = glm::translate(transformationMatrix, translation);
	return;
}

void Tank::rotate(float angle, const glm::vec3& axis) {
	glm::vec3 pivot(0.25f, -0.25f, -0.25f);
	transformationMatrix = glm::translate(transformationMatrix, pivot);
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(angle), axis);
	transformationMatrix = glm::translate(transformationMatrix, -pivot);
}

void Tank::scale(const glm::vec3& scaling) {
	transformationMatrix = glm::scale(transformationMatrix, scaling);
	return;
}