#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(0.6f, 0.7f, 0.8f, 1.0f);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);

  // lights
  // textures  
  // meshes

  grObjects.clear();
  glClearColor(0.4, 0.5, 0.6, 0.7);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  grObjects.push_back(new EjesRGB(200.0));
  /*
  Canjilon* c = new Canjilon(100);
  c->setModelMat(glm::translate(c->getModelMat(), dvec3(250, 1, 1)));
  grObjects.push_back(c);
  Tablero* c2 = new Tablero(50);
  c2->setModelMat(glm::scale(c2->getModelMat(), dvec3(5, 0.5, 0.2)));
  c2->setModelMat(glm::translate(c2->getModelMat(), dvec3(25, 38, 250)));
  grObjects.push_back(c2);
  Tablero* c3 = new Tablero(50);
  c3->setModelMat(glm::scale(c3->getModelMat(), dvec3(5, 0.5, 0.2)));
  c3->setModelMat(glm::translate(c3->getModelMat(), dvec3(25, 38, -250)));
  grObjects.push_back(c3);
  */
  Rotor* rotor = new Rotor(100, 100, 40);
  grObjects.push_back(rotor);
  Rectangulo* rectangulo = new Rectangulo(200, 40);
  rectangulo->setModelMat(glm::rotate(rectangulo->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
  rectangulo->setModelMat(glm::translate(rectangulo->getModelMat(), dvec3(-100, 0, 0)));
  grObjects.push_back(rectangulo);

  Rotor* rotor2 = new Rotor(100, 100, 40);
  rotor2->setModelMat(glm::translate(rotor2->getModelMat(), dvec3(400, 0, 0)));
  grObjects.push_back(rotor2);
  Rectangulo* rectangulo2 = new Rectangulo(200, 40);
  rectangulo2->setModelMat(glm::rotate(rectangulo2->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
  rectangulo2->setModelMat(glm::translate(rectangulo2->getModelMat(), dvec3(300, 0, 0)));
  grObjects.push_back(rectangulo2);

  Rotor* rotor3 = new Rotor(100, 100, 40);
  rotor3->setModelMat(glm::translate(rotor3->getModelMat(), dvec3(400, 400, 0)));
  grObjects.push_back(rotor3);
  Rectangulo* rectangulo3 = new Rectangulo(200, 40);
  rectangulo3->setModelMat(glm::translate(rectangulo3->getModelMat(), dvec3(300, 400, 0)));
  rectangulo3->setModelMat(glm::rotate(rectangulo3->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
  grObjects.push_back(rectangulo3);

  Rotor* rotor4 = new Rotor(100, 100, 40);
  rotor4->setModelMat(glm::translate(rotor4->getModelMat(), dvec3(0, 400, 0)));
  grObjects.push_back(rotor4);
  Rectangulo* rectangulo4 = new Rectangulo(200, 40);
  rectangulo4->setModelMat(glm::translate(rectangulo4->getModelMat(), dvec3(-100, 400, 0)));
  rectangulo4->setModelMat(glm::rotate(rectangulo4->getModelMat(), radians(90.0), dvec3(1, 0, 0)));
  grObjects.push_back(rectangulo4);

  Chasis* chasis = new Chasis(400);
  chasis->setModelMat(glm::translate(chasis->getModelMat(), dvec3(190, 150, -25)));
  chasis->setModelMat(glm::scale(chasis->getModelMat(), dvec3(1,1, 0.1)));
  grObjects.push_back(chasis);

  //  grObjects.push_back(new Dragon(3000));
//  grObjects.push_back(new Triangulo(100));
//  grObjects.push_back(new Rectangulo(80, 100));
}

void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}

void Scene::escena2D()
{
	grObjects.clear();
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	grObjects.push_back(new EjesRGB(200.0));
	grObjects.push_back(new Dragon(3000));
	grObjects.push_back(new Triangulo(100));
	grObjects.push_back(new Rectangulo(80, 100));
}

void Scene::escena3D()
{
	grObjects.clear();
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	grObjects.push_back(new EjesRGB(200.0));
//	grObjects.push_back(new Suelo(500, 500, 3, 3));
//	Estrella3D* e = new Estrella3D(100, 6, 100);  // dvec3(0, 150, 0)
//	e->setModelMat(glm::translate(e->getModelMat(), dvec3(250, 1, 250)));
//	grObjects.push_back(e);  // dvec3(0, 150, 0)
	Caja* c = new Caja(100);
	c->setModelMat(glm::translate(c->getModelMat(), dvec3(250, 1, 250)));
	grObjects.push_back(c);
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------
void Scene::render(dmat4 const& modelViewMat)
{
	for (Entity* el: grObjects)
	{
		el->render(modelViewMat);
	}
}
//-------------------------------------------------------------------------
