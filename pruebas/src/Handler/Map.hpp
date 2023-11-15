#pragma once

#include <tmx.h>

#define LINE_THICKNESS 2.5

struct Map
{
    Map(const char *path){
        map = tmx_load(path);
        layers = map->ly_head;
    }

    ~Map(){
        tmx_map_free(map);
        delete map;
    }

    Color int_to_color(int color) {
        tmx_col_bytes res = tmx_col_to_bytes(color);
        return *((Color*)&res);
    }


    void draw_image_layer(tmx_image *image) {
        Texture2D *texture = (Texture2D*)image->resource_image;
        DrawTexture(*texture, 0, 0, WHITE);
    }

    void draw_tile(void *image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
                unsigned int dx, unsigned int dy, float opacity, unsigned int flags) {
        if(image != nullptr){
            // Casting del puntero void* a Texture2D*
            Texture2D* texture = static_cast<Texture2D*>(image);

            // Ajustar la opacidad del color
            //Color color = {1.0f, 1.0f, 1.0f, opacity};

            DrawTextureRec(*texture, (Rectangle) {sx, sy, sw, sh}, (Vector2) {dx, dy}, (Color) {opacity, opacity, opacity, opacity});
        }
    }

    void draw_layer(tmx_map *map, tmx_layer *layer) {
        unsigned long i, j;
        unsigned int gid, x, y, w, h, flags;
        float op;
        tmx_tileset *ts;
        tmx_image *im;
        void* image;
        op = layer->opacity;
        for (i=0; i<map->height; i++) {
            for (j=0; j<map->width; j++) {
                gid = (layer->content.gids[(i*map->width)+j]) & TMX_FLIP_BITS_REMOVAL;
                if (map->tiles[gid] != NULL) {
                    ts = map->tiles[gid]->tileset;
                    im = map->tiles[gid]->image;
                    x  = map->tiles[gid]->ul_x;
                    y  = map->tiles[gid]->ul_y;
                    w  = ts->tile_width;
                    h  = ts->tile_height;
                    if (im) {
                        image = im->resource_image;
                    }
                    else {
                        image = ts->image->resource_image;
                    }
                    flags = (layer->content.gids[(i*map->width)+j]) & ~TMX_FLIP_BITS_REMOVAL;
                    draw_tile(image, x, y, w, h, j*ts->tile_width, i*ts->tile_height, op, flags); // Function to be implemented
                }
            }
        }
    }

void draw_polyline(double offset_x, double offset_y, double **points, int points_count, Color color) {
    int i;
    for (i=1; i<points_count; i++) {
        DrawLineEx((Vector2){offset_x + points[i-1][0], offset_y + points[i-1][1]},
               (Vector2){offset_x + points[i][0], offset_y + points[i][1]},
               LINE_THICKNESS, color);
    }
}

void draw_polygon(double offset_x, double offset_y, double **points, int points_count, Color color) {
    draw_polyline(offset_x, offset_y, points, points_count, color);
    if (points_count > 2) {
        DrawLineEx((Vector2){offset_x + points[0][0], offset_y + points[0][1]},
               (Vector2){offset_x + points[points_count-1][0], offset_y + points[points_count-1][1]},
               LINE_THICKNESS, color);
    }
}

void draw_objects(tmx_object_group *objgr) {
    tmx_object *head = objgr->head;
    Color color = int_to_color(objgr->color);

    while (head) {
        if (head->visible) {
            if (head->obj_type == OT_SQUARE) {
                DrawRectangleLinesEx((Rectangle){head->x, head->y, head->width, head->height}, LINE_THICKNESS, color);
            }
            else if (head->obj_type  == OT_POLYGON) {
                draw_polygon(head->x, head->y, head->content.shape->points, head->content.shape->points_len, color);
            }
            else if (head->obj_type == OT_POLYLINE) {
                draw_polyline(head->x, head->y, head->content.shape->points, head->content.shape->points_len, color);
            }
            else if (head->obj_type == OT_ELLIPSE) {
                DrawEllipseLines(head->x + head->width/2.0, head->y + head->height/2.0, head->width/2.0, head->height/2.0, color);
            }
        }
        head = head->next;
    }
}

void DrawAll(){
    draw_all_layers(map,layers);
}

    void draw_all_layers(tmx_map *m, tmx_layer *l) {
        while (l) {
            if (l->visible) {
            
              if (l->type == L_GROUP) {
                draw_all_layers(m, l->content.group_head); // recursive call
              }
              else if (l->type == L_OBJGR) {
                draw_objects(l->content.objgr); // Function to be implemented
              }
              else if (l->type == L_IMAGE) {
                draw_image_layer(l->content.image); // Function to be implemented
              }
              else if (l->type == L_LAYER) {
                draw_layer(m, l); // Function to be implemented
              }
            }
            l = l->next;
        }
    }

    private:
        tmx_map *map;
        tmx_layer *layers;
       
};
