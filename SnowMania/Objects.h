
typedef struct 
{
   int y,x;
   bool isTaken;
}spawn_position;


typedef struct 
{
   int points;
   int y,x;
  spawn_position* spawn_pos;
   int height,width;
   bool isPresent;
   int speed;
   int effect;
}object;

void respawn_object(object* object);
void init_array();

void draw_objects(object* objects,int objects_count,void (*func)());

void move_objects(object* objects,int objects_count);

void spawn_objects(object* objects,int objects_count,int points,int efect,int height,int width,bool isPresent);

void collide(object* player,object* objects,int objects_count);