#include <GL/glew.h>

#include "glow.h"

#include "graphics/shader.h"

#include "graphics/buffers/vertexarray.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexbuffer.h"

#include "maths/vec3.h"


#include "utils/time.h"
#include "utils/log.h"


using namespace Glow;


GLfloat vertices[] = {
    -0.5, -0.5, 0,
    -0.5,  0.5, 0,
     0.5,  0.5, 0,
     0.5,  -0.5, 0
};

GLushort indices[] = {
    0, 1, 2,
    2, 3, 0
};


Engine *glow;



int main(int argc, char *argv[]){
    glow = new Engine();
    glow->initEngine();

    Log::logger.log(Loglevel::INFO, "engine initialized");

    Shader shader("res/shaders/default.vert", "res/shaders/default.frag");

    VertexArray* vao = new VertexArray();
    Buffer* vbo = new Buffer(vertices, 12, 3);
    IndexBuffer ibo(indices, 6);


    vao->addBuffer(vbo, 0);

    while(!glow->quit){
        Time::update();
        glow->pollEvents();
        glow->update();

        glow->displayManager->clearWindow();

        glColor3f(1, 1, 1);
        shader.bind();

        //TEMP
        vao->bind();
        ibo.bind();
        glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
        vao->unbind();
        ibo.unbind();

        shader.unbind();

        glow->displayManager->swapWindow();
    }


    //if the gameloop exited, cleanup
    glow->terminateEngine();

    //cleanup
    delete glow;
    delete vao;

    return 0;
}
