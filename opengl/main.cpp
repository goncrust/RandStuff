#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void) {
    GLFWwindow *window;

    /* Initialize glfw */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 760, "Hello World", NULL, NULL);
    if (!window) {
    glfwTerminate();
    return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize glew */
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    /* Print version */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* -------------- Setup Vertex Buffers ----------------- */
    float positions[] = { -0.5, -0.5, 0.0, 0.5, 0.5, -0.5 };

    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id); // Generate one buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id); // Select the buffer
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW); // Write data to buffer

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* ------------------- Draw ------------------------ */
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw vertices (from 0 to third)

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
