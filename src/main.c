#include"renderer.h"

Renderer render;

int main(int argc, char* args[])
{
    init_renderer(&render);
    update_renderer(&render);
    end_section(&render);

    return 0;
}