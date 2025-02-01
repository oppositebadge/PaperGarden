#include "Tangram.hpp"
#include <raylib.h>

Triangle RightEvenTrig(Vector2 pos, float a, float r){
    Triangle trig(
        {
            pos,
            Vector2Add(pos, Vector2{0,-a}),
            Vector2Add(pos, Vector2{a,0}),
        }
    );

    // here we rotate not around the center of trig but around one of it's vertexes - pos
    for (int i = 0; i < trig.points.size(); i++){
        Vector2 frm_cntr_to_pnt = Vector2Subtract(trig.points[i], pos);
        frm_cntr_to_pnt = Vector2Rotate(frm_cntr_to_pnt, r);
        trig.points[i] = Vector2Add(pos, frm_cntr_to_pnt);
    }
    trig.RearrangeCounterClockwise();

    return trig;
}