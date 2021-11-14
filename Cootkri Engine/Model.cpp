#include "Model.h"

#include <GeometryShader.h>

Model::Model(std::string pathway) {

	isDrawable = true;
	mesh.Load(pathway);

}

void Model::draw(void* genericShader) {

	GeometryShader& shader = *((GeometryShader*)genericShader);
	Entity* ent = getEntity();
	if (!ent) {
		return;
	}
	Transform& trans = ent->getTrans();
	shader.setTransMatrix(trans.getMatrix());
	shader.setRotationMatrix(trans.getRotMatrix());
	mesh.draw();

}