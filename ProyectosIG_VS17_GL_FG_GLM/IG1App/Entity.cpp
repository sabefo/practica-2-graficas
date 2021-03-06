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

EjesRGB::EjesRGB(GLdouble l) : Entity()
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

Tablero::Tablero(GLdouble l) : Entity()
{
	mesh = Mesh::generaContCubo(l);
}

Aspanoria::Aspanoria(GLdouble l, GLdouble b) : Entity()
{
	basecanjilon = l;
	basetablero = b;
	c = new Canjilon(100);
	t1 = new Tablero(50);
	t2 = new Tablero(50);
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

Rotor::Rotor(GLdouble br, GLdouble tr, GLdouble h, GLdouble w, GLdouble a, bool sentido) : QuadricEntity()
{
	baseRadius = br;
	topRadius = tr;
	height = h;
	base = w;
	altura = a;
	angulo = 0;
	anguloRota = sentido ? -5 : 5;
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
	r1 = new Rotor(100, 100, 40, 200, 40, true);
	r2 = new Rotor(100, 100, 40, 200, 40, false);
	r3 = new Rotor(100, 100, 40, 200, 40, false);
	r4 = new Rotor(100, 100, 40, 200, 40, true);
	c = new Chasis(400);
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

Cone::Cone(GLdouble h, GLdouble r) : Entity()
{
	/*h = h;
	r = r;*/
	int m = 3; // m=n�mero de puntos del perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.0, h, 0.0);
	mesh = new MBR(m, 50, perfil);
}

Esfera::Esfera(GLint p, GLint m, GLdouble r) : Entity()
{
	pp = p;
	mm = m;
	rr = r;

	GLdouble x = 0;
	GLdouble y = r;
	GLdouble incremento = 180.0 / m;
	GLdouble angulo = 90.0;

	dvec3* perfil = new dvec3[mm];
	
	for (int i = 0; i < m-1; i++)
	{
		perfil[i] = dvec3(x, y, 0.0);
		angulo += incremento;
		x = r * cos(radians(angulo));
		y = r * sin(radians(angulo));

	}
	perfil[m - 1] = dvec3(0, -r, 0.0);

	mesh = new MBR(pp, mm, perfil);
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

Aspanoria::~Aspanoria()
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

Cone::~Cone()
{
	if (mesh != nullptr)
	{
		delete mesh; mesh = nullptr;
	}
	/*if (mesh != nullptr)
	{
		delete mesh; mesh = nullptr;
	}*/
};

Esfera::~Esfera()
{
	if (mesh != nullptr)
	{
		delete mesh; mesh = nullptr;
	}
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
		modelMat = rotate(modelMat, radians(anguloRota), dvec3(0, 1, 0));
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
		modelMat = translate(modelMat, dvec3(radians(anguloTraslada / -1), radians(anguloTraslada), 0));
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

void Tablero::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 mat = modelMat;
		glColor3d(0, 0, 0);
		modelMat = rotate(mat, radians(anguloRota), dvec3(0, 0, 1));
		uploadMvM(modelViewMat);
		glLineWidth(2);
		mesh->render();
		modelMat = mat;
		glLineWidth(1);
	}
}

void Tablero::update()
{
	anguloRota += 50;
}

void Aspanoria::render(glm::dmat4 const& modelViewMat) {
	dmat4 mat1 = modelViewMat;
	mat1 = translate(mat1, dvec3(250, 1, 1));
	c->render(mat1);
	c->update();
	dmat4 mat2 = modelViewMat;
	mat2 = scale(mat2, dvec3(5, 0.5, 0.2));
	mat2 = translate(mat2, dvec3(25, 100, 250));
	t1->render(mat2);
	t1->update();
	dmat4 mat3 = modelViewMat;
	mat3 = scale(mat3, dvec3(5, 0.5, 0.2));
	mat3 = translate(mat3, dvec3(25, 100, -250));
	t2->render(mat3);
	t2->update();
}

void Aspanoria::update()
{
	anguloRota += 5;
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
	mat = rotate(mat, radians(90.0), dvec3(1, 0, 0));
	uploadMvM(mat);
	gluCylinder(q, baseRadius, topRadius, height, 50, 50);
	glColor3d(0, 0, 0);
	Rectangulo* rectangulo = new Rectangulo(base, altura);
	rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(-100, -40, 0)));
	rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(100, 0, 0)));
	rectangulo->setModelMat(glm::rotate(rectangulo->getModelMat(), radians(angulo), dvec3(0, 1, 0)));
	rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(-100, 0, 0)));
	rectangulo->render(modelViewMat);
}

void Rotor::update()
{
	angulo += anguloRota;
}

void Dron::render(glm::dmat4 const& modelViewMat) {
	dmat4 mat1 = modelViewMat;
	glColor3d(1, 0, 0);
	r1->render(mat1);
	r1->update();
	dmat4 mat2 = modelViewMat;
	mat2 = translate(mat2, dvec3(400, 0, 0));
	glColor3d(0, 1, 0);
	r2->render(mat2);
	r2->update();
	dmat4 mat3 = modelViewMat;
	mat3 = translate(mat3, dvec3(400, 0, 400));
	glColor3d(0, 1, 0);
	r3->render(mat3);
	r3->update();
	dmat4 mat4 = modelViewMat;
	mat4 = translate(mat4, dvec3(0, 0, 400));
	glColor3d(1, 0, 0);
	r4->render(mat4);
	r4->update();
	dmat4 mat5 = modelViewMat;
	mat5 = translate(mat5, dvec3(190, -60, 150));
	mat5 = rotate(mat5, radians(90.0), dvec3(1, 0, 0));
	mat5 = scale(mat5, dvec3(1, 1, 0.1));
	c->render(mat5);
}

void Dron::update()
{
	r1->update();
	r2->update();
	r3->update();
	r4->update();
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
	glColor3f(1.8, 0.0, 0.5);
	gluQuadricDrawStyle(q, GLU_POINT);
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

void Cone::render(dmat4 const &modelViewMat)
{
	glColor3f(1, 0, 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	uploadMvM(modelViewMat);
	mesh->render();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//void Cone::update()
//{
//}
//glCullFace(GL_FRONT / GL_BACK);

void Esfera::render(dmat4 const &modelViewMat)
{
	glColor3f(1, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	uploadMvM(modelViewMat);
	mesh->render();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Esfera::update()
{
}