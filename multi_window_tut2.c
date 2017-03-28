#include<stdio.h>
#include<stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>


float vert[][3] = {
		{0, 0 ,0},
		{0, 0, 1},
		{0, 1, 0},
		{0, 1, 1},
		{1, 0, 0},
		{1, 0, 1},
		{1, 1, 0},
		{1, 1, 1}
	};

int edges[][2]  = {
		{0, 1},
		{0, 4},
		{5, 4},
		{5, 1},
		{7, 6},
		{7, 3},
		{3, 2},
		{2, 6},
		{3, 1},
		{7, 5},
		{0, 2},
		{4, 6}
};


typedef struct {
	int r, c;
	float **matrix;
} TransformMatrix;

typedef struct {
	float *matrix;
} Vertex;

typedef struct {
	int noOfVertex;
	int size;
	Vertex **vertices;
	int noOfEdges, edgeSize;
	int **edges;
} VertexGroup;

VertexGroup *vg=NULL;
VertexGroup *vg1=NULL;
GLuint texture;

// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;

// angle for rotating triangle
float angle = 0.0f;
float angle2 = 0.0f;


/* --------Car Definition Starts--------*/
VertexGroup *car_vg=NULL;

float  car_vertexes[][3] = {
		{ 0, 0, 0 }, // a
		{ 0, 2, 0 }, // b
		{ 3.5, 2, 0 }, //c
		{ 6.5, 4, 0 }, //d
		{ 10.5, 4, 0 }, //e
		{ 14.5, 4, 0 }, //f
		{ 6.5, 2, 0 }, //g
		{ 10.5, 2, 0 }, //h
		{ 14.5, 2, 0 }, //i
		{ 18.5, 2, 0 }, //j
		{ 21.5, 2, 0 }, //k
		{ 3, 0, 0 }, //l
		{ 3.5, 1, 0 }, //m
		{ 6.5, 1, 0 }, //n
		{ 7, 0, 0 }, //o
		{ 7.5, 0, 0 }, //p
		{ 10.5, 0, 0 }, //q
		{ 14.5, 0, 0 }, //r
		{ 15.5, 0, 0 }, //s
		{ 16, 1, 0 }, //t
		{ 19, 1, 0 }, //u
		{ 19.5, 0, 0 }, // v
		{ 21.5, 0, 0 }, // w

		{ 0 , 0 ,7.08},
		{ 0 , 2 ,7.08},
		{ 3.5 , 2 ,7.08},
		{ 6.5 , 4 ,7.08},
		{ 10.5 , 4 ,7.08},
		{ 14.5 , 4 ,7.08},
		{ 6.5 , 2 ,7.08},
		{ 10.5 , 2 ,7.08},
		{ 14.5 , 2 ,7.08},
		{ 18.5 , 2 ,7.08},
		{ 21.5 , 2 ,7.08},
		{ 3 , 0 ,7.08},
		{ 3.5 , 1 ,7.08},
		{ 6.5 , 1 ,7.08},
		{ 7 , 0 ,7.08},
		{ 7.5 , 0 ,7.08},
		{ 10.5 , 0 ,7.08},
		{ 14.5 , 0 ,7.08},
		{ 15.5 , 0 ,7.08},
		{ 16 , 1 ,7.08},
		{ 19 , 1 ,7.08},
		{ 19.5 , 0 ,7.08},
		{ 21.5 , 0 ,7.08},


		{0,0,0}

};

int car_edges[][2] = {
		{ 0 , 1 },
		{ 1 , 2 },
		{ 2 , 3 },
		{ 3 , 4 },
		{ 4 , 5 },
		{ 5 , 9 },
		{ 9 , 10 },
		{ 2 , 6 },
		{ 6 , 7 },
		{ 7 , 8 },
		{ 8 , 9 },
		{ 9 , 10 },
		{ 3 , 6 },
		{ 4 , 7 },
		{ 5 , 8 },
		{ 5 , 9 },
		{ 0 , 11 },
		{ 11 , 12 },
		{ 12 , 13 },
		{ 11 , 14 },
		{ 13 , 14 },
		{ 14 , 15 },
		{ 6 , 15 },
		{ 15 , 16 },
		{ 7 , 16 },
		{ 16 , 17 },
		{ 8 , 17 },
		{ 17 , 18 },
		{ 18 , 19 },
		{ 19 , 20 },
		{ 20 , 21 },
		{ 18 , 21 },
		{ 21 , 22 },
		{ 10 , 22 },

		{ 23 , 24 },
		{ 24 , 25 },
		{ 25 , 26 },
		{ 26 , 27 },
		{ 27 , 28 },
		{ 28 , 32 },
		{ 32 , 33 },
		{ 25 , 29 },
		{ 29 , 30 },
		{ 30 , 31 },
		{ 31 , 32 },
		{ 32 , 33 },
		{ 26 , 29 },
		{ 27 , 30 },
		{ 28 , 31 },
		{ 28 , 32 },
		{ 23 , 34 },
		{ 34 , 35 },
		{ 35 , 36 },
		{ 34 , 37 },
		{ 36 , 37 },
		{ 37 , 38 },
		{ 29 , 38 },
		{ 38 , 39 },
		{ 30 , 39 },
		{ 39 , 40 },
		{ 31 , 40 },
		{ 40 , 41 },
		{ 41 , 42 },
		{ 42 , 43 },
		{ 43 , 44 },
		{ 41 , 44 },
		{ 44 , 45 },
		{ 33 , 45 },

		{ 0, 23}, // a
		{ 1, 24}, // b
		{ 2, 25}, // c
		{ 3, 26}, // d
		{ 5, 28}, // f
		{ 9, 32}, // j
		{ 10, 33}, // k
		{ 23, 46}, // w

		{0,0}
};

/* --------Car Definition Ends----------*/

GLuint LoadTexture( const char * filename )
{

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	file = fopen( filename, "rb" );

	if ( file == NULL ) return 0;
	width = 64;
	height = 64;
	data = (unsigned char *)malloc( width * height * 3 );
	//int size = fseek(file,);
	fread( data, width * height * 3, 1, file );
	fclose( file );

	for(int i = 0; i < width * height ; ++i)
	{
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];

		data[index] = R;
		data[index+2] = B;

	}


	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );

	return texture;
}

void drawStrokeText(char*string,int x,int y,int z)
{
	glPushMatrix();

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 10.0f,
				1.0f, 1.0f,  1.0f,
				0.0f, 1.0f,  0.0f);

	glTranslatef(x, y, z);
	glScalef(0.003f,0.003f,.001);


	char *c;
	for (c=string; *c != 0; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	}

	glPopMatrix();
}


void allocateMatrix(float ***MATRIX, int noOfRows, int noOfColumns) {
	float **matrix = *MATRIX = (float **) malloc(sizeof(float *) * noOfRows);
	matrix[0] = (float *) malloc(sizeof(float) * noOfColumns * noOfRows);

    int i,j;
	//assigning the sub-pointers
    for(i = 0; i < noOfRows; i++)
    	matrix[i] = *matrix + noOfColumns * i;

    for(i = 0; i < noOfRows; i++) {
		for(j = 0; j < noOfColumns; j++) {
			matrix[i][j] = 0;
		}
	}
}

void getIdentityMatrix(float **matrix) {
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if (i == j) matrix[i][j] = 1.0;
			else matrix[i][j] = 0.0;
		}
	}
}

void printMatrix(float **matrix) {
	int i, j;
	printf("\n[Matrix:\n");
	for(i = 0; i < 4; i++) {
		printf("\t[");
		for(j = 0; j < 4; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("],\n");
	}
	printf("]");
}

void printMatrixGeneral(float **matrix , int noOfRows, int noOfColumns) {
	int i, j;
	printf("\n[Matrix:\n");
	for(i = 0; i < noOfRows; i++) {
		printf("\t[");
		for(j = 0; j < noOfColumns; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("],\n");
	}
	printf("]");
}

void printVertex(Vertex *v) {
	if (v) printf("[[ Vertex : (%f, %f, %f) ]]", v->matrix[0], v->matrix[1], v->matrix[2]);
	else printf("Vertex: NULL");
}

void printVertexGroup(VertexGroup *vg) {
	if (vg){
		printf("\n[[Vertex Group:\n\tCapacity: %d\n\tNo. of Vertex:%d\n", vg->size, vg->noOfVertex);
		int i;
		printf("\tVertices : {\n\t\t");
		for(i = 0; i < vg->noOfVertex; i++){
			printVertex((vg->vertices)[i]);
			printf(",\n\t\t");
		}
		printf("}\n]]");

		printf("\tEdges : {\n\t\t");
		for(i = 0; i < vg->noOfEdges; i++){
			printf("V[%d] -- V[%d]", (vg->edges)[i][0], (vg->edges)[i][1]);
			printf(",\n\t\t");
		}
		printf("}\n]]");


	}
	else printf("Vertex: NULL");
}

void multiplyMatGeneral(float **mat1, float **mat2, int row1, int col1, int row2, int col2, float **result) {
	int i, j, k;
	for(i = 0; i < col2; i++)	{
		for(j = 0; j < row1; j++)	{
			result[j][i] = 0;
			for(k = 0; k < col1; k++) {
				result[j][i] += mat1[j][k] * mat2[k][i];
			}
		}
	}
}

void multiplyMat(float **mat1, float **mat2, float **result) {
	multiplyMatGeneral(mat1, mat2, 4, 4, 4, 4, result);
}


void applyMatrixVertexGroupMatrix(float **mat1, VertexGroup *vg, float **mat2) {
	/* Don't use, doesn't preserve edges */
	float **tempMat;
	allocateMatrix(&tempMat, 4, vg->noOfVertex);

	int i;
	for(i = 0; i < vg->noOfVertex; i++) {
		tempMat[0][i] = (vg->vertices)[i]->matrix[0];
		tempMat[1][i] = (vg->vertices)[i]->matrix[1];
		tempMat[2][i] = (vg->vertices)[i]->matrix[2];
		tempMat[3][i] = (vg->vertices)[i]->matrix[3];
	}
	multiplyMatGeneral(mat1, tempMat, 4, 4, 4, vg->noOfVertex, mat2);
}

void clearVertexGroup(VertexGroup *vertexGroup) {
	vertexGroup->noOfVertex = 0;
}

int createVertexGroup(VertexGroup **vertexGroup, int size){
	VertexGroup *vg = *vertexGroup = (VertexGroup *) malloc(sizeof(VertexGroup));
	if(!vg) {
			printf("\nMalloc Failed\n");
			return 0;
	} else {
		vg->noOfVertex = 0;
		vg->noOfEdges = 0;
		vg->size = size;
		vg->edgeSize = size*2;
		vg->vertices = (Vertex **) malloc(sizeof(Vertex) * (vg->size));
		vg->edges = (int **) malloc(sizeof(int) * 2 * (vg->edgeSize));

		if(!vg->vertices ) {
			printf("\nMalloc Failed\n");
			return 0;
		} else {

		}
	}
	return 1;
}

int createVertex(Vertex **vertex, float x, float y, float z) {
	Vertex *v = *vertex = (Vertex *) malloc(sizeof(Vertex));
	if(!(v)) {
		printf("\nMalloc Failed:Vertex\n");
		return 0;
	} else {
		v->matrix = (float *) malloc((sizeof(int)) * 4);
		if(!v->matrix) {
			printf("\nMalloc Failed:Vertex\n");
			return 0;
		} else {
			v->matrix[0] = x;
			v->matrix[1] = y;
			v->matrix[2] = z;
			v->matrix[3] = 1;
		}
	}
	return 1;
}

int addVertexToGroup(VertexGroup *vg, Vertex *v) {
	if (vg->noOfVertex + 1 > vg->size) {
		vg->size += 5;
		vg->vertices = (Vertex **) realloc(vg->vertices, (sizeof(Vertex)) * vg->size);
		if(!vg->vertices )  {
			printf("\nRealloc Failed\n");
			return 0;
		}
	}

	vg->vertices[vg->noOfVertex] = v;
	vg->noOfVertex +=1;
	return 1;
}

int addEdgeToGroup(VertexGroup *vg, int vertex1, int vertex2) {
	if (vg->noOfEdges + 1 > vg->edgeSize) {
		vg->edgeSize += 5;
		vg->edges = (int **) realloc(vg->edges, (sizeof(int)) * 2 * vg->edgeSize);
		if(!vg->edges )  {
			printf("\nRealloc Failed\n");
			return 0;
		}
	}

	int *edge = (int *) malloc(sizeof(int) * 2);

	if(!edge) {
		printf("The Edge allocation failed, try again later.");
		return 0;
	}
	edge[0] = vertex1;
	edge[1] = vertex2;
	vg->edges[vg->noOfEdges] = edge;
	vg->noOfEdges +=1;

	return 1;
}

// for newline
void nl()	{
	printf("\n");
}

void applyMatrixVertexGroup(float **mat1, VertexGroup *vg, VertexGroup *vg2) {
	float **tempMat, **out;
	allocateMatrix(&tempMat, 4, vg->noOfVertex);
	allocateMatrix(&out, 4, vg->noOfVertex);

	int i;
	for(i = 0; i < vg->noOfVertex; i++) {
		tempMat[0][i] = (vg->vertices)[i]->matrix[0];
		tempMat[1][i] = (vg->vertices)[i]->matrix[1];
		tempMat[2][i] = (vg->vertices)[i]->matrix[2];
		tempMat[3][i] = (vg->vertices)[i]->matrix[3];
	}
	multiplyMatGeneral(mat1, tempMat, 4, 4, 4, vg->noOfVertex, out);

	clearVertexGroup(vg2);
	Vertex *v;
	for(i = 0; i < vg->noOfVertex; i++){
		createVertex(&v, out[0][i], out[1][i], out[2][i]);
		addVertexToGroup(vg2, v);
	}

	int i0, v1, v2;
	for(i0 = 0; i0 < vg->noOfEdges; i0++) {
		v1 = vg->edges[i0][0];
		v2 = vg->edges[i0][1];
		addEdgeToGroup(vg2, v1, v2);
	}
}

void displayVertexGroup(VertexGroup *vg) {
	if (vg) {
		int i, v1, v2;
		Vertex *a1, *a2;
		float x, y, z;
		for (i= 0; i < vg->noOfEdges; i++) {
			v1 = vg->edges[i][0];
			v2 = vg->edges[i][1];

			a1 = vg->vertices[v1];
			a2 = vg->vertices[v2];

			glBegin(GL_LINE_STRIP);

				x = a1->matrix[0];
				y = a1->matrix[1];
				z = a1->matrix[2];
				glVertex3f(x,y,z);
				x = a2->matrix[0];
				y = a2->matrix[1];
				z = a2->matrix[2];
				glVertex3f(x,y,z);

			glEnd();
		}
	}
}

void createTransformMatrix(float **mat, float x, float y, float z) {
	getIdentityMatrix(mat);
	mat[0][3] = x;
	mat[1][3] = y;
	mat[2][3] = z;

}



void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the view port to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Model view
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	char *x = "Edwin Clement";

	drawStrokeText(x, 0,-1,0);




	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 10.0f,
			1.0f, 1.0f,  1.0f,
			0.0f, 1.0f,  0.0f);
	glColor3f(.5,0,0);
	glTranslatef(4, 4, -0);

	glTranslatef(+.5, +.5, +.5);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-.5, -.5, -.5);


	displayVertexGroup(vg);
	angle+=0.4f;

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 10.0f,
			1.0f, 1.0f,  1.0f,
			0.0f, 1.0f,  0.0f);

	glColor3f(.5,0,0);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	displayVertexGroup(car_vg);

 // Render Settings
	glBindTexture (GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glColor3ub(255,255,255);

	glBegin(GL_QUADS);

	// Top Left
	glTexCoord2f(0, 1);
	glVertex2f(0,1);

	// Top Right
	glTexCoord2f(1, 1);
	glVertex2f(1, 1);

	// Bottom Right
	glTexCoord2f(1, 0);
	glVertex2f(1, 0);

	// Bottom Left
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);

}

void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_F1 :
				red = 1.0;
				green = 0.0;
				blue = 0.0; break;
		case GLUT_KEY_F2 :
				red = 0.0;
				green = 1.0;
				blue = 0.0; break;
		case GLUT_KEY_F3 :
				red = 0.0;
				green = 0.0;
				blue = 1.0; break;

	}
}

void createVertexGroupFromData(VertexGroup **vg1, float vertexes[][3], int v, int edges[][2], int e) {
	VertexGroup *vg = *vg1 = (VertexGroup *) malloc(sizeof(VertexGroup));
	if(!vg) {
			printf("\nMalloc Failed\n");
			return;
	} else {
		vg->noOfVertex = 0;
		vg->noOfEdges = 0;
		vg->size = v;
		vg->edgeSize = e;
		vg->vertices = (Vertex **) malloc(sizeof(Vertex) * (vg->size));
		vg->edges = (int **) malloc(sizeof(int) * 2 * (vg->edgeSize));

		if(!vg->vertices ) {
			printf("\nMalloc Failed\n");
			return;
		} else {

		}
	}

	Vertex *v1;
	int i;

	for(i=0; i < v; i++) {
		createVertex(&v1, vertexes[i][0], vertexes[i][1], vertexes[i][2]);
		addVertexToGroup(vg, v1);
	}

	for(i=0; i < e; i++) {
		addEdgeToGroup(vg, edges[i][0], edges[i][1]);
	}
}


int main(int argc, char **argv) {
	// test texture


	VertexGroup *temp, *temp2;
	createVertexGroupFromData(&temp2, vert, 8, edges, 12);
	float **translateCube; allocateMatrix(&translateCube, 4,4);
	createTransformMatrix(translateCube, 0,0,0);
	createVertexGroup(&vg, 100);
	applyMatrixVertexGroup(translateCube, temp2, vg);

	createVertexGroupFromData(&temp, car_vertexes, (sizeof(car_vertexes) / sizeof(float)) / 3,
			car_edges, (sizeof(car_edges) / sizeof(float)) / 2);

	// create a scale down matrix
	float **scaleDown= NULL;
	allocateMatrix(&scaleDown,4,4);
	scaleDown[0][0] = .3;
	scaleDown[1][1] = .3;
	scaleDown[2][2] = .3;

	float **translateCar= NULL;
	allocateMatrix(&translateCar,4,4);
	createTransformMatrix(translateCar, -5.5, 0, 0);

	float **transformMatrix = NULL;
	allocateMatrix(&transformMatrix,4,4);

	multiplyMat(scaleDown, translateCar, transformMatrix);

	createVertexGroup(&car_vg, 100);
	applyMatrixVertexGroup(transformMatrix, temp, car_vg);

	//printVertexGroup(car_vg);



	// initialize GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,728);
	glutCreateWindow("CG Project - ");

	// register callback
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	texture= LoadTexture( "texture1.bmp" );


	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
