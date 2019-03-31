#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::update()
{
}

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}

Poliespiral::Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}

Triangulo::Triangulo(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloAnimado(r);
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity()
{
//	mesh = Mesh::generaRectanguloRGB(w, h);
	mesh = Mesh::generaRectangulo(w, h);
}

Suelo::Suelo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaSuelo(w, h);
}

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Entity()
{
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	textura.load("..\\Bmps\\baldosaC.bmp");
}

//Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Entity()  // dvec3 pos
//{
//	mesh = Mesh::generaEstrella3D(re, np, h);
//	modelMat = translate(modelMat, dvec3(0, 100, 0));
//}

Estrella3D::Estrella3D(GLdouble r, GLdouble nL, GLdouble h) : Entity()
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h);
	modelMat = translate(modelMat, dvec3(0, 100, 0));
	textura.load("..\\Bmps\\baldosaP.bmp");
}

Caja::Caja(GLdouble l) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l);
	textura.load("..\\Bmps\\container.bmp");
	texturaInner.load("..\\Bmps\\papelE.bmp");
}

Canjilon::Canjilon(GLdouble l) : Caja(l)
{
}

Tablero::Tablero(GLdouble l) : Caja(l)
{
}

QuadricEntity::QuadricEntity() : Entity()
{
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble rr) : QuadricEntity()
{
	r = rr;
}

Cylinder::Cylinder(GLdouble br, GLdouble tr, GLdouble h) : QuadricEntity()
{
	baseRadius = br;
	topRadius = tr;
	height = h;
}

Rotor::Rotor(GLdouble br, GLdouble tr, GLdouble h, GLdouble w, GLdouble a) : QuadricEntity()
{
	baseRadius = br;
	topRadius = tr;
	height = h;
	base = w;
	altura = a;
}

Chasis::Chasis(GLdouble l) : Entity()
{
	mesh = Mesh::generaCuboLleno(l);
}

Dron::Dron(GLdouble br, GLdouble tr, GLdouble h, GLdouble w, GLdouble a, GLdouble l) : QuadricEntity()
{
	baseRadius = br;
	topRadius = tr;
	height = h;
	base = w;
	altura = a;
	lado = l;
	r1 = new Rotor(100, 100, 40, 200, 40);
	r2 = new Rotor(100, 100, 40, 200, 40);
	r3 = new Rotor(100, 100, 40, 200, 40);
	r4 = new Rotor(100, 100, 40, 200, 40);
	c = new Chasis(4);
}

Disk::Disk(GLdouble ir, GLdouble o) : QuadricEntity()
{
	innerRadius = ir;
	outerRadius = o;
}

PartialDisk::PartialDisk(GLdouble ir, GLdouble o, GLdouble sa, GLdouble sw) : QuadricEntity()
{
	innerRadius = ir;
	outerRadius = o;
	startAngle = sa;
	sweepAngle = sw;
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};

Poliespiral::~Poliespiral()
{
	delete mesh; mesh = nullptr;
};

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
};

Triangulo::~Triangulo()
{
	delete mesh; mesh = nullptr;
};

Rectangulo::~Rectangulo()
{
	delete mesh; mesh = nullptr;
};

Suelo::~Suelo()
{
	delete mesh; mesh = nullptr;
};

Estrella3D::~Estrella3D()
{
	delete mesh; mesh = nullptr;
};

Caja::~Caja()
{
	delete mesh; mesh = nullptr;
};

Canjilon::~Canjilon()
{
	delete mesh; mesh = nullptr;
};

Tablero::~Tablero()
{
	delete mesh; mesh = nullptr;
};

Rotor::~Rotor()
{
	delete mesh; mesh = nullptr;
};

Chasis::~Chasis()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}

//-------------------------------------------------------------------------
void Poliespiral::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glColor3d(0, 0, 1);
		mesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------
void Dragon::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 matAux = modelViewMat;
		matAux = scale(matAux, dvec3(40, 40, 0));
		uploadMvM(matAux);
		glLineWidth(2);
		glColor3d(0, 0, 1);
		glPointSize(2);
		mesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
		glPointSize(1);
	}
}

void Triangulo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		double x = 100 * cos(radians(anguloTraslada));
		double y = 100 * sin(radians(anguloTraslada));
		modelMat = translate(modelMat, dvec3(x, y, 0));
		uploadMvM(modelViewMat);
		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 0, 1));
		uploadMvM(modelViewMat);
		mesh->render();
		modelMat = mat;
	}
}

void Triangulo::update()
{
	anguloRota += 3;
	anguloTraslada += 3;
}

void Rectangulo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(modelMat, dvec3(100, 0, 0));
		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 1, 0 ));
		modelMat = translate(modelMat, dvec3(-100, 0, 0));
		uploadMvM(modelViewMat);
		glColor3d(0, 0, 0);
		mesh->render();
		modelMat = mat;
	}
}

void Rectangulo::update()
{
	anguloRota += 5;
}

void Suelo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		textura.bind();
		mesh->render();
		textura.unbind();
	}
}

void Estrella3D::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 100, 0));

		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 1, 0));
		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 0, 1));
		uploadMvM(modelViewMat);
		glLineWidth(1);
		textura.bind();
		mesh->render();
		modelMat = rotate(modelMat, radians(180.0), dvec3(1, 0, 0));
		uploadMvM(modelViewMat);
		mesh->render();
		glLineWidth(1);
		mesh->render();
		modelMat = mat;
		textura.unbind();
	}
}

void Estrella3D::update()
{
	anguloRota++;
}

void Caja::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 50, 0));
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		textura.bind();
		mesh->render();
		textura.unbind();
		glDisable(GL_CULL_FACE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		texturaInner.bind();
		mesh->render();
		modelMat = mat;
		glLineWidth(1);
		texturaInner.unbind();
		glDisable(GL_CULL_FACE);
	}
}

void Canjilon::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 50, 0));
		modelMat = translate(modelMat, dvec3(0, radians(anguloTraslada),0));
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		textura.bind();
		mesh->render();
		textura.unbind();
		glDisable(GL_CULL_FACE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		texturaInner.bind();
		mesh->render();
		modelMat = mat;
		glLineWidth(1);
		texturaInner.unbind();
		glDisable(GL_CULL_FACE);
	}
}

void Canjilon::update()
{
	anguloRota += 50;
	anguloTraslada += 50;
}

void Tablero::update()
{
	anguloRota++;
}

void Sphere::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	// Fijar el modo en que se dibuja la entidad con
	// gluQuadricDrawStyle(q, ...);
	gluSphere(q, r, 50, 50);
}

void Cylinder::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	glColor3f(1, 1, 1);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, baseRadius, topRadius, height, 50, 50);
}

void Rotor::render(glm::dmat4 const& modelViewMat) {
	dmat4 mat = modelViewMat;
//	glColor3d(1, 0, 0);
	mat = rotate(mat, radians(90.0), dvec3(1, 0, 0));
	uploadMvM(mat);
	gluCylinder(q, baseRadius, topRadius, height, 50, 50);
	glColor3d(0, 0, 0);
	Rectangulo* rectangulo = new Rectangulo(base, altura);
	rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(-100, -40, 0)));
	rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(100, 0, 0)));
	rectangulo->setModelMat(glm::rotate(rectangulo->getModelMat(), radians(anguloRota), dvec3(0, 1, 0)));
	rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(-100, 0, 0)));
	rectangulo->render(modelViewMat);
}

void Rotor::update()
{
	anguloRota += 5;
}

void Dron::render(glm::dmat4 const& modelViewMat) {
	glColor3d(1, 0, 0);
	r1->render(modelViewMat);
	glColor3d(0, 1, 0);
	r2->setModelMat(glm::translate(r2->getModelMat(), dvec3(400, 0, 0)));
	r2->render(modelViewMat);
	
}

void Disk::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	// Fijar el modo en que se dibuja la entidad con
	// gluQuadricDrawStyle(q, ...);
	gluDisk(q, innerRadius, outerRadius, 20, 8);
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	// Fijar el modo en que se dibuja la entidad con
	// gluQuadricDrawStyle(q, ...);
	gluPartialDisk(q, innerRadius, outerRadius, 20, 8, startAngle, sweepAngle);
}

void Chasis::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		modelMat = translate(mat, dvec3(0, 50, 0));
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glColor3f(0, 0, 1);
		mesh->render();
		modelMat = mat;
		glLineWidth(1);
	}
}

//glCullFace(GL_FRONT / GL_BACK);
