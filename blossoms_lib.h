struct Point {
    double x, y;
};

struct RGB {
    double r, g, b;
};


//TODO not really needed, just for testing
/*
//given p0 and p1, find point off p1 that lies along the same line, at a distance equal to dis(p0,p1)
//Used in testing to ensure we are doing the math right
struct Point find_point(struct Point p0, struct Point p1){
    double change_x = p1.x - p0.x;
    double change_y = p1.y - p0.y;

    double p2x = p1.x - change_y;
    double p2y = p1.y + change_x;
    struct Point p_off_p1 = {p2x, p2y};

    return p_off_p1;
}
*/

void blossom_draw_save(struct Point blossoms[], int *index, struct Point p1, struct Point p2, struct Point p3, struct Point p4, int initial_radius ){
        //adjust colors to be one of three shades of pink
        int random = rand() % 3; //make 3 random numbers from 0 -2

        if(random == 0){
            G_rgb(0.87,0.647,0.643);//hot pink
        }
        else if (random == 1){
            G_rgb(0.95,0.76,0.76);//pink
        } else {
            G_rgb(0.98,0.85,0.86);//light pink
        }
        //draw circles at the end points of each final square
        G_fill_circle(p1.x, p1.y, initial_radius);
        G_fill_circle(p2.x, p2.y, initial_radius);
        G_fill_circle(p3.x, p3.y, initial_radius);
        G_fill_circle(p4.x, p4.y, initial_radius);

        //populate array
        blossoms[(*index)] = p1;
        (*index)++;
        blossoms[(*index)] = p2;
        (*index)++;
        blossoms[(*index)] = p3;
        (*index)++;
        blossoms[(*index)] = p4;
        (*index)++;

}

//Initialize array of blossoms with empty points
void init_blossoms(struct Point array[], int size){
         struct Point init = {0,0};
         for(int i =0; i < size; i++){
            array[i] = init;
         }
}
