#include "Mesh.h"

constexpr double PI = 3.14159265;

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void)
{
	delete[] vertices;  vertices = nullptr;
	delete[] colors;    colors = nullptr;
	delete[] textures;    textures = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
		}
		if (textures != nullptr) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, textures);
		}

		glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
	Mesh* m = new Mesh();
	m->primitive = GL_LINES;
	m->numVertices = 6;

	m->vertices = new dvec3[m->numVertices];
	// X axis vertices
	m->vertices[0] = dvec3(0.0, 0.0, 0.0);
	m->vertices[1] = dvec3(l, 0.0, 0);
	// Y axis vertices
	m->vertices[2] = dvec3(0, 0.0, 0.0);
	m->vertices[3] = dvec3(0.0, l, 0.0);
	// Z axis vertices
	m->vertices[4] = dvec3(0.0, 0.0, 0.0);
	m->vertices[5] = dvec3(0.0, 0.0, l);

	m->colors = new dvec4[m->numVertices];
	// X axis color: red  ( Alpha = 1 : fully opaque)
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------
Mesh * Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble
	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	Mesh* m2 = new Mesh();
	m2->primitive = GL_LINE_STRIP;
	m2->numVertices = numVert;

	m2->vertices = new dvec3[m2->numVertices];

	double x = verIni.x;
	double y = verIni.y;

	for (int i = 0; i < m2->numVertices; i++)
	{
		m2->vertices[i] = dvec3(x, y, 0.0);

		x = x + ladoIni * cos(radians(angIni));
		y = y + ladoIni * sin(radians(angIni));
		ladoIni += incrLado;
		angIni += incrAng;
	}

	return m2;
}

//-------------------------------------------------------------------------
Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];

	double pr1 = 0.787473;
	double pr2 = 1 - pr1;
	double x = 0;
	double y = 0;

	for (int i = 0; i < m->numVertices; i++)
	{
		m->vertices[i] = dvec3(x, y, 0.0);
		double azar = rand() / double(RAND_MAX);
		double aux = x;
		if (azar < pr1) {
			x = 0.824074 * x + 0.281482 * y - 0.882290;
			y = -0.212346 * aux + 0.864198 * y - 0.110607;
		} // T1
		else {
			x = 0.088272 * x + 0.520988 * y + 0.785360;
			y = -0.463889 * aux - 0.377778 * y + 8.095795;
		} // T2
	}

	return m;
}

Mesh * Mesh::generaTriangulo(GLdouble r)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];

	double angIni = 90;
	double x = 0;
	double y = 0;

	//	centro C = (0, 0) y radio R = r:
	for (int i = 0; i < 3; i++)
	{
		x = r * cos(radians(angIni));
		y = r * sin(radians(angIni));
		m->vertices[i] = dvec3(x, y, 0.0);
		angIni += 120;
	}

	return m;
}

Mesh * Mesh::generaTrianguloRGB(GLdouble r)
{
	Mesh * m = generaTriangulo(r);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generaTrianguloAnimado(GLdouble r)
{
	Mesh * m = generaTriangulo(r);
	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[2] = dvec4(1.0, 0.0, 0.0, 1.0);

	return m;
}

Mesh * Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0.0, h, 0.0);
	m->vertices[1] = dvec3(w, h, 0.0);
	m->vertices[2] = dvec3(0.0, 0.0, 0.0);
	m->vertices[3] = dvec3(w, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh *m = generaSuelo(w, h);
	m->textures = new dvec2[m->numVertices];
	m->textures[0] = dvec2(0, rh);
	m->textures[1] = dvec2(0, 0);
	m->textures[2] = dvec2(rw, rh);
	m->textures[3] = dvec2(rw, 0);

	return m;
}

Mesh * Mesh::generaSuelo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0.0, 0.0, h);
	m->vertices[1] = dvec3(w, 0.0, h);
	m->vertices[2] = dvec3(0.0, 0.0, 0.0);
	m->vertices[3] = dvec3(w, 0.0, 0.0);

	return m;
}

Mesh * Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
	Mesh * m = generaRectangulo(w, h);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 1.0);

	return m;
}

Mesh * Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;

	m->vertices = new dvec3[m->numVertices];
	double x = 30;
	double y = 30;
	double ang = 0;

	m->vertices[0] = dvec3(0.0, 0.0, 0.0);

	for (int i = 1; i < m->numVertices - 1; i++)
	{
		double z = 1;
		if (i % 2 == 0)
			z = 2;
		x = (re / z) * cos(radians(ang));
		y = (re / z) * sin(radians(ang));
		m->vertices[i] = dvec3(x, y, h);
		ang += 360 / (m->numVertices - 2);
	}
	m->vertices[m->numVertices - 1] = m->vertices[1];

	return m;
}

Mesh * Mesh::generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h)
{
	Mesh *m = generaEstrella3D(r, nL, h);
	m->numVertices = 2 * nL + 2;
	m->textures = new dvec2[m->numVertices];
	double x = 30;
	double y = 30;
	double ang = 0;

	m->textures[0] = dvec2(0.0, 0.0);

	for (int i = 1; i < m->numVertices - 1; i++)
	{
		double z = 0.5;
		if (i % 2 == 0)
			z = 0.25;
		x = z * cos(radians(ang));
		y = z * sin(radians(ang));
		m->textures[i] = dvec2(x, y);
		ang += 360 / (m->numVertices - 2);
	}
	m->textures[m->numVertices - 1] = m->textures[1];

	return m;
}

Mesh * Mesh::generaContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	double x = l / 2;

	m->vertices[0] = dvec3(-x, x, -x);
	m->vertices[1] = dvec3(-x, -x, -x);
	m->vertices[2] = dvec3(-x, x, x);
	m->vertices[3] = dvec3(-x, -x, x);
	m->vertices[4] = dvec3(x, x, x);
	m->vertices[5] = dvec3(x, -x, x);
	m->vertices[6] = dvec3(x, x, -x);
	m->vertices[7] = dvec3(x, -x, -x);
	m->vertices[8] = m->vertices[0];
	m->vertices[9] = m->vertices[1];

	return m;
}

Mesh * Mesh::generaCuboLleno(GLdouble l)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 16;

	m->vertices = new dvec3[m->numVertices];
	double x = l / 2;

	m->vertices[0] = dvec3(x, x, -x);
	m->vertices[1] = dvec3(-x, x, -x);
	m->vertices[2] = dvec3(x, x, x);
	m->vertices[3] = dvec3(-x, x, x);
	m->vertices[4] = m->vertices[1];
	m->vertices[5] = dvec3(-x, -x, -x);
	m->vertices[6] = m->vertices[3];
	m->vertices[7] = dvec3(-x, -x, x);
	m->vertices[8] = dvec3(x, x, x);
	m->vertices[9] = dvec3(x, -x, x);
	m->vertices[10] = m->vertices[0];
	m->vertices[11] = vec3(x, -x, -x);
	m->vertices[12] = m->vertices[1];
	m->vertices[13] = m->vertices[5];
	m->vertices[14] = m->vertices[9];
	m->vertices[15] = m->vertices[7];

	return m;
}

Mesh * Mesh::generaCajaTexCor(GLdouble l)
{
	Mesh *m = generaContCubo(l);

	m->textures = new dvec2[m->numVertices];
	double x = 1;
	m->textures[0] = dvec2(0, 0);
	m->textures[1] = dvec2(1, 0);
	m->textures[2] = dvec2(0, 1);
	m->textures[3] = dvec2(1, 1);
	m->textures[4] = dvec2(0, 0);
	m->textures[5] = dvec2(1, 0);
	m->textures[6] = dvec2(0, 1);
	m->textures[7] = dvec2(1, 1);
	m->textures[8] = m->textures[0];
	m->textures[9] = m->textures[1];
	return m;
}

MBR::MBR(GLint mm, GLint nn, dvec3* perf)
{
	m = mm;
	n = nn;
	perfil = perf;
	vertexBuilding();
	normalize();
	render();
}

MBR ::~MBR()
{
	Mesh::~Mesh();
	if (perfil != nullptr) {
		delete[] perfil; 
		perfil = nullptr;
	}
	if (normals != nullptr) {
		delete[] normals;
		normals = nullptr;
	}
}

void MBR::vertexBuilding() {
	// Definir el array vertices de tamaño numVertices(=n*m)
	numVertices = n * m;
	vertices = new dvec3[numVertices];
	for (int i = 0; i < n; i++) {
		// Cada vuelta genera la muestra i-ésima de vértices
		double theta = i * 2 * PI / n;
		double c = cos(theta);
		double s = sin(theta);
		// R_y de más abajo es la matriz de rotación sobre el eje Y
		for (int j = 0; j < m; j++) {
			int indice = i * m + j;
			// Aplicar la matriz al punto j-ésimo del perfil
			double x = c * perfil[j][0] + s * perfil[j][2];
			double z = -s * perfil[j][0] + c * perfil[j][2];
			dvec3 p = dvec3(x, perfil[j][1], z);
			vertices[indice] = p;
		}
	}
}

void MBR::normalize() {
	// Definir el array normals de tamaño numVertices
	numVertices = n * m;
	normals = new dvec3[numVertices];
	// e inicializar sus componentes al vector cero(=dvec3(0,0,0))
	for (int i = 0; i < numVertices; i++)
		normals[i] = dvec3(0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) {
			// Recorrido de todos los vértices
			// Ojo, i<n (obliga a usar %(n*m))
			// y j<m-1 (para excluir los vértices del borde superior)
			int indice = i * m + j;
			// Por cada cara en la que el vértice ocupa la esquina
			// inferior izquierda, se determinan 3 índices i0, i1, i2
			// de 3 vértices consecutivos de esa cara 
			GLint i0 = indice;
			GLint i1 = indice + m;
			i1 = i1 % numVertices;
			GLint i2 = (indice + 1 + m);
			i2 = i2 % numVertices;
			//GLint i3 = indice + 1;

			dvec3 aux0 = vertices[i0];
			dvec3 aux1 = vertices[i1];
			dvec3 aux2 = vertices[i2];
			dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);
			normals[i0] += norm;
			normals[i1] += norm;
			normals[i2] += norm;
			//normals[i3] += norm;
		}
		normals[i] = glm::normalize(normals[i]);
	}
}

void MBR::render() {
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		// Activación de vertex arrays de colores y
		// coordenadas de textura, si hace el caso.
		// No olvidar desactivarlos
		if (normals != nullptr) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, normals);
			primitive = GL_POLYGON; // o GL_LINE_LOOP
			// Se dan índices de vértices de caras cuadrangulares
			for (int i = 0; i < n; i++) {
				// Unir muestra i-ésima con (i+1)%n-ésima
				for (int j = 0; j < m - 1; j++) {
					// Empezar en esquina inferior izquierda de la cara
					unsigned int indice = i * m + j;
					unsigned int index[] = { indice, (int)(indice + m) % (int)(n * m),
						(int)(indice + m + 1) % (int)(n * m),
						indice + 1 };
					glDrawElements(primitive, 4, GL_UNSIGNED_INT, index);
				}
			}
		}
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}