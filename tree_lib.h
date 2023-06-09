
#include "blossoms_lib.h"

//assumes triangle P0, P1, P2
//where P2 is the unknown 90 degree angle point at the top, P0 is lower left, P1 is lower right
//distance is between P0 and P1, percent is how far from P0, pm is
struct Point calculate_point(struct Point p0, struct Point p1, double distance, double percent){
    //find change in x and y between P0 and P1
    double change_x = p1.x - p0.x;
    double change_y = p1.y - p0.y;

    //find the point, pm that lies between P0 and P1 exactly percent ways from P0, p4 and p5 will be along this line
    double xm = p0.x + (percent * change_x);
    double ym = p0.y + (percent * change_y);
    struct Point pm = {xm, ym};

    //find the point, P3, directly above pm
    //We will calculate p2, the needed point, using this point
    //It will be back from pm by change_y, and up by change_x
    double x3 = pm.x - change_y;
    double y3 = pm.y + change_x;
    struct Point p3 = {x3, y3};

    //first find the distance between P1 and Pm
    double dis_p1_pm = sqrt((p1.x - pm.x) * (p1.x - pm.x) + (p1.y - pm.y) * (p1.y - pm.y));
    //then find the distance between p0 and pm
    double dis_p0_pm = distance - dis_p1_pm;

    double l = sqrt(dis_p1_pm * dis_p0_pm);

    double scale_factor = l / distance;

    //move from p3 over by change in y times scale factor...
    //...and from p3 down by the change in x times the scale factor
    double x2 = p3.x + scale_factor * change_y;
    double y2 = p3.y - scale_factor * change_x;
    struct Point p2 = {x2, y2};

    return p2;

}


void redraw_tree_no_blossoms (struct Point p0, struct Point p1, double distance, double percent, double depth){
    if (depth == 0){
         return;
    }

    //get the third point
    struct Point p2 = calculate_point(p0, p1, distance, percent);

    //draw triangle
    G_rgb(1,0,0); //red
    G_line(p0.x, p0.y, p2.x, p2.y);
    G_rgb(0,1,0); //green
    G_line(p2.x, p2.y, p1.x, p1.y);
    G_rgb(1,0,1); //purple
    G_line(p1.x, p1.y, p0.x, p0.y);
    G_rgb(.588, 0.294, 0);
    G_fill_triangle(p0.x, p0.y, p2.x, p2.y, p1.x, p1.y);

    //draw squares off each edge: p0-p2, p2-p1, p0-p1

    //-----------------------------//
    //change x and y between p2 and p0
    double change_x = p2.x - p0.x;
    double change_y = p2.y - p0.y;

    //point off p2
    double p4x = p2.x - change_y;
    double p4y = p2.y + change_x;
    struct Point p4 = {p4x, p4y};

    //point off p0
    double p3x = p0.x - change_y;
    double p3y = p0.y + change_x;
    struct Point p3 = {p3x, p3y};

    //Draw square off p0-p2
    G_rgb(0.6, 0.32, 0.24);
    G_line(p2.x, p2.y, p4.x, p4.y);
    G_line(p0.x, p0.y, p3.x, p3.y);
    G_line(p3.x, p3.y, p4.x, p4.y);

    //-----------------------------//
    //change x and y between p2 and p1
    change_x = p1.x - p2.x;
    change_y = p1.y - p2.y;

    //point off p2
    double p5x = p2.x - change_y;
    double p5y = p2.y + change_x;
    struct Point p5 = {p5x, p5y};

    //point off p1
    double p6x = p1.x - change_y;
    double p6y = p1.y + change_x;
    struct Point p6 = {p6x, p6y};

    //draw square off p2-p1
     G_rgb(0.6, 0.32, 0.24);
    G_line(p1.x, p1.y, p6.x, p6.y);
    G_line(p2.x, p2.y, p5.x, p5.y);
    G_line(p5.x, p5.y, p6.x, p6.y);


    //-----------------------------//
    //change x and y between p0 and p1
    change_x = p0.x - p1.x;
    change_y = p0.y - p1.y;

    //point off p0
    double p7x = p0.x - change_y;
    double p7y = p0.y + change_x;
    struct Point p7 = {p7x, p7y};

    //point off p1
    double p8x = p1.x - change_y;
    double p8y = p1.y + change_x;
    struct Point p8 = {p8x, p8y};

    //Draw square off p0-p1
    G_rgb(0.6, 0.32, 0.24);
    G_line(p0.x, p0.y, p7.x, p7.y);
    G_line(p1.x, p1.y, p8.x, p8.y);
    G_line(p7.x, p7.y, p8.x, p8.y);
    //-----------------------------//


    depth -= 1;

    //call children with p3-p4 and p5-p6
    redraw_tree_no_blossoms(p3,p4, distance, percent, depth);
    redraw_tree_no_blossoms(p5, p6, distance, percent, depth);
}

void tree (struct Point p0, struct Point p1, double distance, double percent, double depth, struct Point blossoms[], int *index){
    if (depth == 0){
         return;
    }

    //get the third point
    struct Point p2 = calculate_point(p0, p1, distance, percent);

    //draw triangle
    G_rgb(1,0,0); //red
    G_line(p0.x, p0.y, p2.x, p2.y);
    G_rgb(0,1,0); //green
    G_line(p2.x, p2.y, p1.x, p1.y);
    G_rgb(1,0,1); //purple
    G_line(p1.x, p1.y, p0.x, p0.y);
    G_rgb(.588, 0.294, 0);
    G_fill_triangle(p0.x, p0.y, p2.x, p2.y, p1.x, p1.y);

    //draw squares off each edge: p0-p2, p2-p1, p0-p1

    //-----------------------------//
    //change x and y between p2 and p0
    double change_x = p2.x - p0.x;
    double change_y = p2.y - p0.y;

    //point off p2
    double p4x = p2.x - change_y;
    double p4y = p2.y + change_x;
    struct Point p4 = {p4x, p4y};

    //point off p0
    double p3x = p0.x - change_y;
    double p3y = p0.y + change_x;
    struct Point p3 = {p3x, p3y};

    //Draw square off p0-p2
    G_rgb(0.6, 0.32, 0.24);
    G_line(p2.x, p2.y, p4.x, p4.y);
    G_line(p0.x, p0.y, p3.x, p3.y);
    G_line(p3.x, p3.y, p4.x, p4.y);



    //double dis_p0_p2 = sqrt((p0.x - p2.x) * (p0.x - p2.x) + (p0.y - p2.y) * (p0.y - p2.y));
    //G_fill_rectangle(p0.x, p0.y, dis_p0_p2, dis_p0_p2);

    //-----------------------------//
    //change x and y between p2 and p1
    change_x = p1.x - p2.x;
    change_y = p1.y - p2.y;

    //point off p2
    double p5x = p2.x - change_y;
    double p5y = p2.y + change_x;
    struct Point p5 = {p5x, p5y};

    //point off p1
    double p6x = p1.x - change_y;
    double p6y = p1.y + change_x;
    struct Point p6 = {p6x, p6y};

    //draw square off p2-p1
     G_rgb(0.6, 0.32, 0.24);
    G_line(p1.x, p1.y, p6.x, p6.y);
    G_line(p2.x, p2.y, p5.x, p5.y);
    G_line(p5.x, p5.y, p6.x, p6.y);


    //-----------------------------//
    //change x and y between p0 and p1
    change_x = p0.x - p1.x;
    change_y = p0.y - p1.y;

    //point off p0
    double p7x = p0.x - change_y;
    double p7y = p0.y + change_x;
    struct Point p7 = {p7x, p7y};

    //point off p1
    double p8x = p1.x - change_y;
    double p8y = p1.y + change_x;
    struct Point p8 = {p8x, p8y};

    //Draw square off p0-p1
    G_rgb(0.6, 0.32, 0.24);
    G_line(p0.x, p0.y, p7.x, p7.y);
    G_line(p1.x, p1.y, p8.x, p8.y);
    G_line(p7.x, p7.y, p8.x, p8.y);
    //-----------------------------//

    //Initial blossoms
    if(depth == 1){
        int radius = 5;
        blossom_draw_save(blossoms, index, p3, p4, p5, p6, radius);
    }

    depth -= 1;

    //call children with p3-p4 and p5-p6
    tree(p3,p4, distance, percent, depth, blossoms, index);
    tree(p5, p6, distance, percent, depth, blossoms, index);
}

void tree_save_blossoms (struct Point p0, struct Point p1, double distance, double percent, double depth, struct Point blossoms[], int *index){
    if (depth == 0){
         return;
    }

    //get the third point
    struct Point p2 = calculate_point(p0, p1, distance, percent);

    //draw triangle
    G_rgb(1,0,0); //red
    G_line(p0.x, p0.y, p2.x, p2.y);
    G_rgb(0,1,0); //green
    G_line(p2.x, p2.y, p1.x, p1.y);
    G_rgb(1,0,1); //purple
    G_line(p1.x, p1.y, p0.x, p0.y);
    G_rgb(.588, 0.294, 0);
    G_fill_triangle(p0.x, p0.y, p2.x, p2.y, p1.x, p1.y);

    //draw squares off each edge: p0-p2, p2-p1, p0-p1

    //-----------------------------//
    //change x and y between p2 and p0
    double change_x = p2.x - p0.x;
    double change_y = p2.y - p0.y;

    //point off p2
    double p4x = p2.x - change_y;
    double p4y = p2.y + change_x;
    struct Point p4 = {p4x, p4y};

    //point off p0
    double p3x = p0.x - change_y;
    double p3y = p0.y + change_x;
    struct Point p3 = {p3x, p3y};

    //Draw square off p0-p2
    G_rgb(0.6, 0.32, 0.24);
    G_line(p2.x, p2.y, p4.x, p4.y);
    G_line(p0.x, p0.y, p3.x, p3.y);
    G_line(p3.x, p3.y, p4.x, p4.y);

    //double dis_p0_p2 = sqrt((p0.x - p2.x) * (p0.x - p2.x) + (p0.y - p2.y) * (p0.y - p2.y));
    //G_fill_rectangle(p0.x, p0.y, dis_p0_p2, dis_p0_p2);

    //-----------------------------//
    //change x and y between p2 and p1
    change_x = p1.x - p2.x;
    change_y = p1.y - p2.y;

    //point off p2
    double p5x = p2.x - change_y;
    double p5y = p2.y + change_x;
    struct Point p5 = {p5x, p5y};

    //point off p1
    double p6x = p1.x - change_y;
    double p6y = p1.y + change_x;
    struct Point p6 = {p6x, p6y};

    //draw square off p2-p1
     G_rgb(0.6, 0.32, 0.24);
    G_line(p1.x, p1.y, p6.x, p6.y);
    G_line(p2.x, p2.y, p5.x, p5.y);
    G_line(p5.x, p5.y, p6.x, p6.y);


    //-----------------------------//
    //change x and y between p0 and p1
    change_x = p0.x - p1.x;
    change_y = p0.y - p1.y;

    //point off p0
    double p7x = p0.x - change_y;
    double p7y = p0.y + change_x;
    struct Point p7 = {p7x, p7y};

    //point off p1
    double p8x = p1.x - change_y;
    double p8y = p1.y + change_x;
    struct Point p8 = {p8x, p8y};

    //Draw square off p0-p1
    G_rgb(0.6, 0.32, 0.24);
    G_line(p0.x, p0.y, p7.x, p7.y);
    G_line(p1.x, p1.y, p8.x, p8.y);
    G_line(p7.x, p7.y, p8.x, p8.y);
    //-----------------------------//

    //Initial blossoms
    if(depth == 1){
        int radius = 5;
        blossom_save(blossoms, index, p3, p4, p5, p6, radius);
    }

    depth -= 1;

    //call children with p3-p4 and p5-p6
    tree(p3,p4, distance, percent, depth, blossoms, index);
    tree(p5, p6, distance, percent, depth, blossoms, index);
}