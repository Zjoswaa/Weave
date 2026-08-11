#include "weave/core/application.h"
#include "weave/core/log.h"
#include "weave/core/window.h"

#include <glad/glad.h>

namespace Weave {
    Application::Application(const ApplicationSpecification& spec) {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::Application()");

        this->spec = spec;

        WindowSpecification window_spec;
        window_spec.decorated = spec.window_decorated;
        window_spec.fullscreen = spec.window_fullscreen;
        window_spec.resizable = spec.window_resizable;
        this->window = Window::create(window_spec);
        this->window->init();
        this->window->set_event_callback([this](const Weave::Event& event) {
            this->on_event(event);
        });

        if (spec.window_maximized && !spec.window_fullscreen) {
            this->window->maximize();
        } else {
            // this->window->center();
        }

        // == Temporary OpenGL setup ==

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        // 3. Create Vertex Array Object & Vertex Buffer Object
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 color;
            out vec3 vertexColor;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                vertexColor = color;
            }
        )";
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        const char* fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            in vec3 vertexColor;
            void main() {
                FragColor = vec4(vertexColor, 1.0f);
            }
        )";
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shader_program = glCreateProgram();
        glAttachShader(shader_program, vertexShader);
        glAttachShader(shader_program, fragmentShader);
        glLinkProgram(shader_program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    };

    Application::~Application() {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::~Application()");

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shader_program);
    };

    void Application::on_event(const Weave::Event& event) {
        WEAVE_LOG_CORE_INFO_TAG("Event", "{}", event.to_string());

        if (event.get_type() == EventType::WindowClose) {
            WEAVE_LOG_CORE_INFO_TAG("Application", "Exiting application.");
            this->running = false;
        }
    }

    void Application::run() {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::run()");

        while(this->running) {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader_program);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            this->window->process_events();
            this->window->swap_buffers();
        }
    }
}
