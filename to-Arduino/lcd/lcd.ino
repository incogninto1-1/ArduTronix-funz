#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <stdlib.h>

#define TFT_CS     10
#define TFT_RST    8 
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

typedef struct pixel {
  int x;
  int y;
  struct pixel *next;
} pixel;

typedef struct {
  pixel* head;
  pixel* tail;
  int length;
} path;

pixel* newPixel(int x, int y){
  pixel* newPixel = (pixel*)malloc(sizeof(pixel));
  if (newPixel == NULL) return NULL;
  newPixel->x = x;
  newPixel->y = y;
  newPixel->next = NULL;
  return newPixel;
}

void addPixel(path* list, int x, int y){
  pixel* fresh = newPixel(x, y);
  if(!fresh) return;
  if (list->head ==NULL) {
    list->head = fresh;
  }
  else{
    list->tail->next = fresh;
  }
  list->tail = fresh;
  list->length++;
}

path* define_path(int (*shape)[2], int length){
  path* lol = NULL;
  //take every pixel in the array ([0][n]=x axis, [1][n]=y axis), and insert them into lol
  for(int i=0; i<length; i++){
    if(lol==NULL){
      lol = (path*)malloc(sizeof(path));
      if(lol==NULL) return NULL;
      lol->head = NULL;
      lol->tail = NULL;
      lol->length = 0;
    }
    addPixel(lol, shape[i][0], shape[i][1]);
  }
  return lol;
}

void nuke_path(pixel* initial){
  if(initial==NULL) return;
  pixel* current = initial;
  while(current->next != NULL){
    pixel* next = current->next;
    free(current);
    current = next;
  }
  free(current);
}

void draw_path(pixel *initial){
  if(initial==NULL || initial->next==NULL){
    tft.setCursor(0, 0);
    tft.println("You need more than one node for this function to work :\\");
    return;
  }
  pixel *current = initial;
  while(current-> next != NULL){
    pixel *next = current->next;
    tft.drawLine(current->x, current->y, next->x, next->y, ST77XX_WHITE);
    current = current->next;
  }
  tft.drawLine(current->x, current->y, initial->x, initial->y, ST77XX_WHITE);
}

void random_lines(){
  short random_x1 = 0;
  short random_y1 = 0;
  short random_x2 = 0;
  short random_y2 = 0;
  for(int i=0; i=9999; i++){
    random_x1=random(0,128);
    random_y1=random(0,160);
    random_x2=random(0,128);
    random_y2=random(0,160);
    tft.drawLine(random_x1, random_y1, random_x2, random_y2, ST77XX_CYAN);
    
  }
}

void prime_calc(int input){
  short prime=1;
  for(int i=input; i<999999; i++){
    for(int a=2; a<i && prime==1; a++){
      if(i%a==0){
        prime=0;
      }
    }
    if(prime==1){
      tft.fillRect(0, 0, 80, 10, ST77XX_BLACK);
      tft.setCursor(0, 0);
      tft.println(i);

    }
    prime=1;
  }
}


void setup() {
  #pragma region Initialization_nonsense
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  analogWrite(3, 0);
  Serial.println("STARTING LCD");
  tft.initR(INITR_BLACKTAB); // Initialize for 1.8" ST7735R
  pinMode(3, OUTPUT);
  for(uint8_t i=0; i <255; i++){
    delay(5);
    analogWrite(3, i);
  }
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  #pragma endregion

  int shape[11][2] = {{15,104}, {15,59}, {38,40}, {81,39}, {103,56}, {103,104}, {79,122}, {71,113}, {63,126}, {48,111}, {33,127}};
  path* thing = define_path(shape, 11);


  draw_path(thing->head);

  nuke_path(thing->head);



  //What I am going to do next is NOT RECCOMENDED. This is a classic software vulnerability that is called use after free. It is when you free a pointer, but then continue to use it. In this case, I am going to free the path that I just drew, and then try to draw it again. This will cause undefined behavior, and may cause the program to crash or do something unexpected. I am doing this for educational purposes only, and I do not reccomend doing this in any real code.

  //draw_path(thing->head); 
  
  //prime_calc(27397);
  //random_lines();
  //tft.println("");
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()){
      Serial.read();
    for(uint8_t i=255; i >0; i--){
    delay(1);
    analogWrite(3, i);
  }
  }
  // put your main code here, to run repeatedly:

}
