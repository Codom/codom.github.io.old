#include "canvas.h"
#include "window.h"

#include "wasm_site.c"

int main(void) {
    HTMLCanvasElement *canvas = createCanvas("myCanvas");
    canvas->setHeight(canvas, Window()->getInnerHeight());
    canvas->setWidth(canvas, Window()->getInnerWidth());

    CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d");
    render_site(ctx);
    freeCanvas(canvas);
    freeWindow(Window());
    return 0;
}
