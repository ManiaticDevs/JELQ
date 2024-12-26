#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/glut.h> // I wish I was joking but glut loves iostream, so define iostream before this

#include "Model.hpp" // our headersss

// Best to use the [using namespace] because entry point (main func) would be obscured if we do define this is a class and/or as part of a namespace
using namespace Renderer;

// outline our methods
void processInput(GLFWwindow* window);
void showFPS(GLFWwindow* pWindow);

// MACROSS! (probably not the best idea but who caress)
// Camera macros
#define FOV 45.0f
#define zNear 0.1f
#define zFar 100.0f

// Window macros
#define w_width 640
#define w_height 480

double lastTime = glfwGetTime();
int nbFrames;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    // For perspective reasons we set this up
    GLfloat aspect = (GLfloat)w_width / (GLfloat)w_height;
    
    window = glfwCreateWindow(w_width, w_height, "Hello World", NULL, NULL);
    
    // if the window failed to create do this
    if (!window) 
    {
        std::cout << "Failed to create window!\n";
        glfwTerminate();
        return -1;
    }

    // Assign opengl context to this thread (are we multithreading? nah)
    glfwMakeContextCurrent(window);

    float pitch = 0.0f; // x axis
    float yaw = 0.0f;   // y axis

    // cube model from Model.hpp
    Cube* cube = new Cube();

    lastTime = glfwGetTime();

    // by default this is set to 1 (and we don't even need the line here) but is capped at 16FPS.
    // putting it to 0 causes it to run unlimited but allows us to cap the framerate ourselves
    glfwSwapInterval(1);

    // Run this loop whilst user hasn't requested a terminate signal
    while (!glfwWindowShouldClose(window))
    {
        showFPS(window);
        yaw += 2.2f; // rotate that
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers (If you don't you get nothing)
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        // handle keyboard inputs
        processInput(window);

        // Setup camera
        glMatrixMode(GL_PROJECTION);               // Load in projection mode
        glLoadIdentity();                          // Reset (because other matrices are being used)
        gluPerspective(FOV, aspect, zNear, zFar);  // Set the perspective of the camera using defined macros

        // We use 1.0 for the angles because that's tells the function to only rotate on that axis hence why the rest are 0.0
        glRotatef(-90, 1.0, 0.0, 0.0);  // look down
        glRotatef(-yaw, 0.0, 1.0, 0.0); // rotate along y
        glTranslatef(0.0, 16.0, 0.0);   // set camera position above the cubes (always do this after rotations)
        
        // Draw our cubes! (They all share the same angles tho)
        cube->draw(0.0f, 0.0f, -7.0f);
        cube->draw(0.0f, 0.0f, 7.0f);
        cube->draw(7.0f, 0.0f, 0.0f);
        cube->draw(-7.0f, 0.0f, 0.0f);

        // Swap back and front buffers (we are double buffering after all)
        glfwSwapBuffers(window);

        // Try to get any events from window
        glfwPollEvents();
    }
    
    // Welp the user has requested the terminate signal soo here we are
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_A)) {
        std::cout << "Pressing\n";
    }
}


void showFPS(GLFWwindow* pWindow)
{
    // Measure speed
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;
    if (delta >= 1.0) { // If last cout was more than 1 sec ago
        std::cout << 1000.0 / double(nbFrames) << "\n";

        double fps = double(nbFrames) / delta;

        nbFrames = 0;
        lastTime = currentTime;
    }
}