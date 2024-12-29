#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

constexpr float points[24] = {
	-5.0, 5.0, 5.0,
	5.0, 5.0, 5.0,
	-5.0, -5.0, 5.0,
	5.0, -5.0, 5.0,

	-5.0, 5.0, -5.0,
	5.0, 5.0, -5.0,
	-5.0, -5.0, -5.0,
	5.0, -5.0, -5.0 };

constexpr int edges[] = {
	1, 2, 3, 4,
	5, 6, 7, 8,
	1, 2, 5, 6,
	3, 4, 7, 8,
	5, 1, 7, 3,
	6, 2, 8, 4 };

constexpr int fov = 90;

float projX1 = 0.0;
float projY1 = 0.0;

float projX2 = 0.0;
float projY2 = 0.0;

float projX3 = 0.0;
float projY3 = 0.0;

float projX4 = 0.0;
float projY4 = 0.0;

int point1 = 0;
int point2 = 0;
int point3 = 0;
int point4 = 0;

float coordX = 0.0;
float coordY = 0.0;
float coordZ = 0.0;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	int curPoint = 0;
	float theta = 0.0;

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		if (curPoint < std::size(edges) && (!(point1 >= std::size(points)) || !(point2 >= std::size(points)) || !(point3 >= std::size(points)) || !(point4 >= std::size(points)))) {
			point1 = edges[curPoint];
			point2 = edges[curPoint + 1];
			point3 = edges[curPoint + 2];
			point4 = edges[curPoint + 3];

			// Point 1
			
			std::cout << point1 << "\n";
			
			coordX = points[3 * (point1 - 1) + 0];
			coordY = points[3 * (point1 - 1) + 1];
			coordZ = points[3 * (point1 - 1) + 2];

			coordX = ((coordX * cos(theta)) + (coordZ * sin(theta)));
			coordZ = ((coordX * -(sin(theta))) + (coordZ * cos(theta)));

			if ((coordZ > 0)) {
				projX1 = (coordX) / (coordZ * tan(fov / 2));
				projY1 = (coordY) / (coordZ * tan(fov / 2));

				// Point 2

				coordX = points[3 * (point2 - 1) + 0];
				coordY = points[3 * (point2 - 1) + 1];
				coordZ = points[3 * (point2 - 1) + 2];

				coordX = ((coordX * cos(theta)) + (coordZ * sin(theta)));
				coordZ = ((coordX * -(sin(theta))) + (coordZ * cos(theta)));

				if ((coordZ > 0)) {
					projX2 = (coordX) / (coordZ * tan(fov / 2));
					projY2 = (coordY) / (coordZ * tan(fov / 2));

					// Point 3

					coordX = points[3 * (point3 - 1) + 0];
					coordY = points[3 * (point3 - 1) + 1];
					coordZ = points[3 * (point3 - 1) + 2];

					coordX = ((coordX * cos(theta)) + (coordZ * sin(theta)));
					coordZ = ((coordX * -(sin(theta))) + (coordZ * cos(theta)));

					if ((coordZ > 0)) {
						projX3 = (coordX) / (coordZ * tan(fov / 2));
						projY3 = (coordY) / (coordZ * tan(fov / 2));

						// Point 4

						coordX = points[3 * (point4 - 1) + 0];
						coordY = points[3 * (point4 - 1) + 1];
						coordZ = points[3 * (point4 - 1) + 2];

						coordX = ((coordX * cos(theta)) + (coordZ * sin(theta)));
						coordZ = ((coordX * -(sin(theta))) + (coordZ * cos(theta)));

						if ((coordZ > 0)) {
							projX4 = (coordX) / (coordZ * tan(fov / 2));
							projY4 = (coordY) / (coordZ * tan(fov / 2));

							glBegin(GL_QUADS);
							// glColor3f((rand() % 101)/100, (rand() % 101) / 100, (rand() % 101) / 100);
							glVertex2f(projX1, projY1);
							glVertex2f(projX2, projY2);
							glVertex2f(projX3, projY3);
							glVertex2f(projX4, projY4);
							glEnd();

						}

					}

				}

			}

			std::cout << projX1 << " " << projY1 << "\n";

			curPoint = curPoint + 4;

			if (curPoint < std::size(edges)) {
				curPoint = 0;
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}