#include "main.h"

#include "level.hpp"

#include "colors.hpp"

#include <vector>
#include <memory>
#include <chrono>
#include <thread>

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

float camera_x = 0.0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;

const int fps = 120;

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    glm::vec3 eye(get_position().x, 0, 1);
    glm::vec3 target(get_position().x, 0, 0);
    glm::vec3 up(0, 1, 0);

    Matrices.view = glm::lookAt(eye, target, up);
    glm::mat4 VP = Matrices.projection * Matrices.view;

    levelDraw(window, VP);
}


void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    initLevel();

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    glClearColor(COLOR_BLACK.r/256.0, COLOR_BLACK.g/256.0, COLOR_BLACK.b/256.0, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

int main(int argc, char **argv) {
    int width  = 1440;
    int height = 900;

    window = initGLFW(width, height);

    initGL(window, width, height);
    while (!glfwWindowShouldClose(window)) {
        if(screen_zoom < 1.0)
            screen_zoom = std::min(1.0, screen_zoom + 0.001);
        else if(screen_zoom > 1.0)
            screen_zoom = std::max(1.0, screen_zoom - 0.001);
        reset_screen();

        auto start = std::chrono::steady_clock::now();
        {
            draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        auto end = std::chrono::steady_clock::now();
        int time_spent_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        int sleep_time = std::max(0, int(1000/fps) - time_spent_ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));        
    }
    quit(window);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
