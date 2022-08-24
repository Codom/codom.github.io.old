/*
 * wasm_site.c
 * Copyright (C) 2022 Christopher Odom christopher.r.odom@gmail.com
 *
 * Contains main site functions referenced in wasm_main.c
 *
 */

char content [] = {
    "Christopher Odom\n\n"
    "Benefits of using a canvas-based website:\n"
    "    * No need to wrangle html/css\n"
    "    * More granular control over the graphics\n"
    "    * More spcialized primitives for web content\n"
    "Downsides:\n"
    "    * Not web scraping friendly (this may be a plus in come contexts)\n"
    "    * Heavier network payload\n"
    "    * A bit hacky overall\n"
    "I can mitigate the web scraping issue by simply dumping these content\n"
    "sections into the dom behind the canvas. The network payload isn't great,\n"
    "but it's also not terrible. And the hackyness factor is honestly a plus in\n"
    "my book :^)\n"
};

#define length(a) sizeof(a) / sizeof(a[0])

void render_site(CanvasRenderingContext2D* ctx) {
    ctx->setFont(ctx, "48px serif");
    int start_slice = 0;
    int line = 0;
    for(int i = 0; i < length(content); ++i) {
        if(content[i] == '\n') {
            content[i] = '\0';
            ctx->fillText(ctx, content + start_slice, 0, 150 + line * 24, -1);
            if(line == 0) ctx->setFont(ctx, "24px serif");
            ++line;
            start_slice = i;
            content[i] = '\n';
        }
    }
}



