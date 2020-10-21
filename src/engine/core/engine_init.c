//
// Created by holmes on 17/10/2020.
//

#include "engine_init.h"

main_systems mainSystems;

bool engine_init(const char *window_name, unsigned short screen_width, unsigned short screen_height) {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());

        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    mainSystems.window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(mainSystems.window == NULL) {
        SDL_Log("Failed to create window: %s\n", SDL_GetError());

        return false;
    }

    mainSystems.glContext = SDL_GL_CreateContext(mainSystems.window);
    if(mainSystems.glContext == NULL) {
        SDL_Log("Failed to create OpenGL context: %s\n", SDL_GetError());

        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if(GLEW_OK != error) {
        SDL_Log("Failed to initialize GLEW: %s\n", glewGetErrorString(error));

        return false;
    }

    SDL_Log("Using GLEW %s\n", glewGetString(GLEW_VERSION));

    printf("\nOpenGL version: %s\n", glGetString(GL_VERSION));
    printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Rendering device: %s\n", glGetString(GL_RENDERER));

    return true;
}