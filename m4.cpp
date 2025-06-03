#include "stb_image.h"
#include "gl_utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define GL_LOG_FILE "gl.log"
#include <iostream>
#include <vector>

using namespace std;

GLFWwindow *g_window = NULL;

struct Image
{
    int id;
    char *fileName;
    unsigned int texture;
    GLuint VAO;
    float rotateXRadius, rotateYRadius;
    float xScale, yScale;
    float offsetx, offsety, offsetz;
};

int g_gl_height = 600;
int g_gl_width = 800;

int loadTexture(unsigned int &texture, char *filename)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLfloat max_aniso = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
    // set the maximum!
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);

    int width, height, nrChannels;

    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 4)
        {

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
}

GLuint generateVAO(float size)
{
    float vertices[] = {
        size, size, 1.0f, 0.0f,   // top right
        size, -size, 1.0f, 1.0f,  // bottom right
        -size, -size, 0.0f, 1.0f, // bottom left
        -size, size, 0.0f, 0.0f,  // top left
    };

    unsigned int indices[] = {
        2, 1, 0,
        0, 3, 2};

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

vector<Image *> generateModel()
{
    vector<Image *> model;

    Image *img10 = new Image;
    img10->fileName = "images/sky.png";
    img10->offsetx = ((float)g_gl_width) / 2.0f;
    img10->offsety =  ((float)g_gl_height) / 2.0f;  
    img10->rotateXRadius = 0;
    img10->rotateYRadius = 0;
    img10->xScale = g_gl_width;
    img10->yScale =  g_gl_height;
    img10->VAO = generateVAO(0.5);
    model.push_back(img10);
    loadTexture(img10->texture, img10->fileName);


    Image *img7 = new Image;
    img7->fileName = "images/grass2.png";
    img7->offsetx = ((float)g_gl_width) / 2.0f;
    img7->offsety =  ((float)g_gl_height) / 2.0f;  
    img7->rotateXRadius = 0;
    img7->rotateYRadius = 0;
    img7->xScale = g_gl_width;
    img7->yScale =  g_gl_height;
    img7->VAO = generateVAO(0.5);
    model.push_back(img7);
    loadTexture(img7->texture, img7->fileName);

    Image *img6 = new Image;
    img6->fileName = "images/grass3.png";
    img6->offsetx = ((float)g_gl_width) / 2.0f;
    img6->offsety =  ((float)g_gl_height) / 2.0f;  
    img6->rotateXRadius = 0;
    img6->rotateYRadius = 0;
    img6->xScale = g_gl_width;
    img6->yScale =  g_gl_height;
    img6->VAO = generateVAO(0.5);
    model.push_back(img6);
    loadTexture(img6->texture, img6->fileName);

    Image *img4 = new Image;
    img4->fileName = "images/grass.png";
   img4->offsetx = ((float)g_gl_width) / 2.0f;
    img4->offsety =  ((float)g_gl_height) / 2.0f;  
    img4->rotateXRadius = 0;
    img4->rotateYRadius = 0;
    img4->xScale = g_gl_width;
    img4->yScale =  g_gl_height ;
    img4->VAO = generateVAO(0.5);
    model.push_back(img4);
    loadTexture(img4->texture, img4->fileName);

        Image *img8 = new Image;
    img8->fileName = "images/tree1.png";
    img8->offsetx = ((float)g_gl_width) / 1.1f;
    img8->offsety =  ((float)g_gl_height) / 3.8f;  
    img8->rotateXRadius = 0;
    img8->rotateYRadius = 0;
    img8->xScale = g_gl_width / 6;
    img8->yScale =  g_gl_height / 6;
    img8->VAO = generateVAO(0.5);
    model.push_back(img8);
    loadTexture(img8->texture, img8->fileName);

        Image *img9 = new Image;
    img9->fileName = "images/tree2.png";
       img9->offsetx = ((float)g_gl_width) / 8.0f;
    img9->offsety =  ((float)g_gl_height) / 2.8f;  
    img9->rotateXRadius = 0;
    img9->rotateYRadius = 0;
    img9->xScale = g_gl_width / 4;
    img9->yScale =  g_gl_height / 4;
    img9->VAO = generateVAO(0.5);
    model.push_back(img9);
    loadTexture(img9->texture, img9->fileName);

    Image *img5 = new Image;
    img5->fileName = "images/grass4.png";
       img5->offsetx = ((float)g_gl_width) / 2.0f;
    img5->offsety =  ((float)g_gl_height) / 2.0f;  
    img5->rotateXRadius = 0;
    img5->rotateYRadius = 0;
    img5->xScale = g_gl_width ;
    img5->yScale =  g_gl_height;
    img5->VAO = generateVAO(0.5);
    model.push_back(img5);
    loadTexture(img5->texture, img5->fileName);

        Image *img2 = new Image;
    img2->fileName = "images/bwolfRun.png";
    img2->offsetx = ((float)g_gl_width) / 3.0f;
    img2->offsety =  ((float)g_gl_height) / 3.50f;  
    img2->rotateXRadius = 0;
    img2->rotateYRadius = 0;
    img2->xScale = g_gl_width / 4;
    img2->yScale =  g_gl_height / 4.5;
    img2->VAO = generateVAO(0.5);
    model.push_back(img2);
    loadTexture(img2->texture, img2->fileName);

        Image *img0 = new Image;
    img0->fileName = "images/mobi1.png";
    img0->offsetx = ((float)g_gl_width) / 8.0f;
    img0->offsety =  ((float)g_gl_height) / 4.0;  
    img0->rotateXRadius = 0;
    img0->rotateYRadius = 0;
    img0->xScale = g_gl_width / 3;
    img0->yScale =  g_gl_height / 3;
    img0->VAO = generateVAO(0.5);
    model.push_back(img0);
    loadTexture(img0->texture, img0->fileName);

        Image *img11 = new Image;
    img11->fileName = "images/wwolfRun.png";
    img11->offsetx = ((float)g_gl_width) / 100.0f;
    img11->offsety =  ((float)g_gl_height) / 7.0f;  
    img11->rotateXRadius = 0;
    img11->rotateYRadius = 0;
    img11->xScale = g_gl_width / 4;
    img11->yScale =  g_gl_height / 5.0;
    img11->VAO = generateVAO(0.5);
    model.push_back(img11);
    loadTexture(img11->texture, img11->fileName);


    Image *img12 = new Image;
    img12->fileName = "images/rwolfRun.png";
    img12->offsetx = ((float)g_gl_width) / 3.8f;
    img12->offsety =  ((float)g_gl_height) / 8.0f;  
    img12->rotateXRadius = 0;
    img12->rotateYRadius = 0;
    img12->xScale = g_gl_width / 3.8;
    img12->yScale =  g_gl_height / 4;
    img12->VAO = generateVAO(0.5);
    model.push_back(img12);
    loadTexture(img12->texture, img12->fileName);

    Image *img14 = new Image;
    img14->fileName = "images/Arrow.png";
    img14->offsetx = ((float)g_gl_width) / 1.75f;
    img14->offsety =  ((float)g_gl_height) / 7.0f;  
    img14->rotateXRadius = 0;
    img14->rotateYRadius = 180;
    img14->xScale = g_gl_width / 4;
    img14->yScale =  g_gl_height / 4;
    img14->VAO = generateVAO(0.5);
    model.push_back(img14);
    loadTexture(img14->texture, img14->fileName);

    Image *img13 = new Image;
    img13->fileName = "images/wwolfDead.png";
    img13->offsetx = ((float)g_gl_width) / 2.0f;
    img13->offsety =  ((float)g_gl_height) / 6.0f;  
    img13->rotateXRadius = 0;
    img13->rotateYRadius = 0;
    img13->xScale = g_gl_width / 4;
    img13->yScale =  g_gl_height / 8;
    img13->VAO = generateVAO(0.5);
    model.push_back(img13);
    loadTexture(img13->texture, img13->fileName);

    Image *img15 = new Image;
    img15->fileName = "images/Shot.png";
      img15->offsetx = ((float)g_gl_width) / 1.1f;
    img15->offsety =  ((float)g_gl_height) / 2.4f;  
    img15->rotateXRadius = 0;
    img15->rotateYRadius = 180;
    img15->xScale = g_gl_width / 4;
    img15->yScale =  g_gl_height / 4;
    img15->VAO = generateVAO(0.5);
    model.push_back(img15);
    loadTexture(img15->texture, img15->fileName);

    Image *img1 = new Image;
    img1->fileName = "images/samurai.png";
      img1->offsetx = ((float)g_gl_width) / 1.2f;
    img1->offsety =  ((float)g_gl_height) / 4.0f;  
    img1->rotateXRadius = 0;
    img1->rotateYRadius = 180;
    img1->xScale = g_gl_width / 4;
    img1->yScale =  g_gl_height / 4;
    img1->VAO = generateVAO(0.5);
    model.push_back(img1);
    loadTexture(img1->texture, img1->fileName);

    return model;
}

int main()
{

    start_gl();

    vector<Image *> model = generateModel();

    char vertex_shader[1024 * 256];
    char fragment_shader[1024 * 256];
    parse_file_into_str("vs.glsl", vertex_shader, 1024 * 256);
    parse_file_into_str("fs.glsl", fragment_shader, 1024 * 256);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *p = (const GLchar *)vertex_shader;
    glShaderSource(vs, 1, &p, NULL);
    glCompileShader(vs);

    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params)
    {
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
        print_shader_info_log(vs);
        return 1;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    p = (const GLchar *)fragment_shader;
    glShaderSource(fs, 1, &p, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params)
    {
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", fs);
        print_shader_info_log(fs);
        return 1;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &params);
    if (GL_TRUE != params)
    {
        fprintf(stderr, "ERROR: could not link shader programme GL index %i\n",
                shaderProgram);
        return false;
    }

    glm::mat4 projection = glm::ortho(0.0f, (float)g_gl_width, 0.0f, (float)g_gl_height, -1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(g_window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, g_gl_width, g_gl_height);

        glUseProgram(shaderProgram);

        for (int i = 0; i < model.size(); i++)
        {
            glBindVertexArray(model[i]->VAO);


     
            glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(model[i]->offsetx, model[i]->offsety, 0.0f));
            glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, glm::radians(model[i]->rotateXRadius), glm::vec3(-1.0f, 0.0f, 0.0f));
            glm::mat4 view = glm::rotate(ViewRotateX, glm::radians(model[i]->rotateYRadius), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 scale = glm::scale(
                glm::mat4(1.0f),
                glm::vec3(model[i]->xScale, model[i]->yScale, 0.0f));

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scale"), 1, GL_FALSE, glm::value_ptr(scale));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

            glUniform1f(glGetUniformLocation(shaderProgram, "offsetz"), model[i]->offsetz);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, model[i]->texture);
            glUniform1i(glGetUniformLocation(shaderProgram, "sprite"), 0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        glfwPollEvents();
        glfwSwapBuffers(g_window);
    }
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(g_window);
    glfwTerminate();
    return 0;
}
