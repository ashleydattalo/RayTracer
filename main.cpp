/*
   CPE 471 Lab 1 
   Base code for Rasterizer
   Example code using B. Somers' image code - writes out a sample tga
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <iomanip> 
#include <map>
#include <string>
#include <iterator>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/normal.hpp>

#include "Image.h"
#include "types.h"
#include "Camera.hpp"
#include "ViewFrustrum.hpp"
#include "Sphere.hpp"
#include "Rainbow.hpp"

#define WIDTH 300
#define HEIGHT 300

void rayTrace();
glm::vec3 computeViewRay(int i, int j);
void printVec(glm::vec3 vec, std::string str);
void singleSphere();
void createSpheres();
void setBunny();
// newFunction

Camera cam(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), WIDTH, HEIGHT);
Image img(WIDTH, HEIGHT);

std::vector<Sphere *> spheres;

glm::vec3 lightPos(0.0f, 0.0f, 5.0f);

int main(void) {
   // createSpheres();
   setBunny();
   // singleSphere();
   rayTrace();
}

void rayTrace() {
   Rainbow rainbow(0, HEIGHT);
   for (int i=0; i < WIDTH; i++) {
      for (int j=0; j < HEIGHT; j++) {
         glm::vec3 rayDir = computeViewRay(i, j);
         for (int s = 0; s < spheres.size(); s++) {
            Sphere *sphere = spheres[s];
            if (sphere->intersects(rayDir)) {
               // sphere->setColor(rainbow.getColor(j));
               glm::vec3 col = sphere->calcBlinnPhong(rayDir, lightPos);
               color_t color;
               color.r = col.x;
               color.g = col.y;
               color.b = col.z;
               color.f = 1.0f;
               img.pixel(i, j, color);
            }
         }

      }
   }
   img.WriteTga((char *)"output.tga", true); 
}

glm::vec3 computeViewRay(int i, int j) {
   glm::vec3 rayDir;
   glm::vec3 eye = cam.getPosition();
   glm::mat4 view = cam.getView();
   ViewFrustrum frustrum = cam.getFrustrum();


   glm::vec3 l, r, t, b, n;
   l = frustrum.left;
   r = frustrum.right;
   t = frustrum.top;
   b = frustrum.bottom;
   n = frustrum.near;

   glm::vec4 uvwSource;
   uvwSource.x = l.x + (r.x - l.x) * (i + 0.5f) / (float)WIDTH;
   uvwSource.y = b.y + (t.y - b.y) * (j + 0.5f) / (float)HEIGHT;
   uvwSource.z = -n.z;
   uvwSource.w = 1.0f;

   glm::mat4 eyeMat;
   eyeMat = glm::translate(eyeMat, eye);

   glm::vec3 source = -eyeMat * view * uvwSource;

   rayDir = glm::vec3(normalize(source - eye));

   return rayDir;
}

void singleSphere() {
   glm::vec3 eye = cam.getPosition();
   glm::vec3 color(1.0f);
   float radius = 0.5f;
   glm::vec3 center(0.0f, 0.0f, 0.0f);
   Sphere *sphere = new Sphere(center, radius, color, eye);
   spheres.push_back(sphere);  
}

void createSpheres() {
   glm::vec3 eye = cam.getPosition();
   glm::vec3 color(1.0f);
   float radius = 0.02f;
   glm::vec3 center(0.0f, 0.0f, 0.0f);

   float gridSize = 5.0f;
   float buf = 1.3f;

   for(int k = 0; k < 15; k++) {
      // inc += 0.1f;
      for(float i = 0.1f; i < gridSize; i++) {
         for(float j = 0.1f; j < gridSize; j++) {
            float stepX = buf * i / gridSize;
            float stepY = buf * j / gridSize;
            center.x = -0.5 + stepX;
            center.y = -0.5 + stepY;
            center.z = -k;
            // printVec(center, "center");
            Sphere *sphere = new Sphere(center, radius, color, eye);
            spheres.push_back(sphere);  
         }
      }
   }
}

float randFloat(float l, float h) {
   float r = rand() / (float)RAND_MAX;
   return (1.0f - r) * l + r * h;
}

void setBunny() {
   glm::vec3 eye = cam.getPosition();
   glm::vec3 color(1.0f);
   float radius = 0.05f;
    const char *path = "bunny.obj";
    int numVertices = 0;
    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        exit(0);
    }
    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            vertex *= 8;
            vertex.y -= 0.85f;
            vertex.x += 0.15f;
            printVec(vertex, "vertex");
            Sphere *sphere = new Sphere(vertex, radius, color, eye);
            spheres.push_back(sphere); 
            numVertices++;
        }
        if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );

            // glm::vec3 force = glm::normalize(glm::vec3(-0.466541, 2.08864, 0.117601) - vertex);
            // if (useNormal) {

            //     data.push_back(normal.x);
            //     data.push_back(normal.y);
            //     data.push_back(normal.z);                
            // }
        }
        // if ( strcmp( lineHeader, "f" ) == 0 ){
        //     glm::vec3 triangle;
        //     fscanf(file, "%f %f %f\n", &triangle.x, &triangle.y, &triangle.z );

        //     std::cout << std::endl << triangle.x << " ";
        //     std::cout << triangle.y << " ";
        //     std::cout << triangle.z << " ";

        //     glm::vec3 vert1, vert2, vert3;

        //     float offset;
        //     offset = (triangle.x -1) * 3;
        //     vert1.x = data[offset + 0];
        //     vert1.y = data[offset + 1];
        //     vert1.z = data[offset + 2];

        //     offset = (triangle.y -1) * 3;
        //     vert2.x = data[offset + 0];
        //     vert2.y = data[offset + 1];
        //     vert2.z = data[offset + 2];

        //     offset = (triangle.z -1) * 3;
        //     vert3.x = data[offset + 0];
        //     vert3.y = data[offset + 1];
        //     vert3.z = data[offset + 2];


        //     addLine(vert1, vert2);
        //     addLine(vert1, vert3);
        //     addLine(vert2, vert3);

        //     numFaces++;
        // }

    }
}


void printVec(glm::vec3 vec, std::string str) {
   std::cout << str << ": ";
   std::cout << vec.x;
   std::cout << " ";
   std::cout << vec.y;
   std::cout << " ";
   std::cout << vec.z;
   std::cout << std::endl;
}

// newFunction