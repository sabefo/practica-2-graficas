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
