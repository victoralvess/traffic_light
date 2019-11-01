typedef struct {
  int red_time;
  int green_pin;
  int red_pin;
} pedestrian_traffic_light;

typedef struct {
  int green_pin;
  int red_pin;
  int yellow_pin;
} vehicle_traffic_light;

//void go_red(vehicle_traffic_light *);
//void go_green(vehicle_traffic_light *);


pedestrian_traffic_light pdtl;
vehicle_traffic_light vtl_1, vtl_3;

void pdtl_loop(pedestrian_traffic_light *pdtl) {
  if (pdtl->red_time >= 5) {
      delay(5000);
      digitalWrite(pdtl->red_pin, LOW);
      digitalWrite(pdtl->green_pin, HIGH);
      delay(5000);
      digitalWrite(pdtl->green_pin, LOW);
      digitalWrite(pdtl->red_pin, HIGH);
      pdtl->red_time = 0;
    return;
  }
  delay(500);
  digitalWrite(pdtl->red_pin, LOW);
  delay(500);
  digitalWrite(pdtl->red_pin, HIGH); 
  pdtl->red_time += 1;
}

void go_green(vehicle_traffic_light *vtl_1, vehicle_traffic_light *vtl_2) {
  delay(1000);
  digitalWrite(vtl_1->red_pin, LOW);
  digitalWrite(vtl_1->green_pin, HIGH);
//  digitalWrite(vtl_2->red_pin, LOW);
//  digitalWrite(vtl_2->green_pin, HIGH);
//  delay(5000);
//  go_red(vtl);
}

//void go_green2(vehicle_traffic_light vtl) {
//  delay(1000);
//  digitalWrite(vtl.red_pin, LOW);
//  digitalWrite(vtl.green_pin, HIGH);
//  delay(5000);
//  go_red(&vtl);
//}

void go_red(vehicle_traffic_light *vtl_1, vehicle_traffic_light *vtl_2) {
  digitalWrite(vtl_1->green_pin, LOW);
  digitalWrite(vtl_1->yellow_pin, HIGH);
//  digitalWrite(vtl_2->green_pin, LOW);
//  digitalWrite(vtl_2->yellow_pin, HIGH);
  delay(2000);
  digitalWrite(vtl_1->yellow_pin, LOW);
  digitalWrite(vtl_1->red_pin, HIGH);
//  digitalWrite(vtl_2->yellow_pin, LOW);
//  digitalWrite(vtl_2->red_pin, HIGH);
//  delay(5000);
//  go_green(vtl);
}

int can_pedestrian_cross() {
  return (
    digitalRead(vtl_1.green_pin) == LOW &&
    digitalRead(vtl_3.green_pin) == LOW
  );
}
int last_pair = 1;
int ONE_AND_THREE = 0;
int TWO_AND_FOUR = 1;

void vtl_go_green() {
  if (last_pair == ONE_AND_THREE) {
//        go_green(&vtl_2);
//        go_green(&vtl_4);
    go_green(&vtl_1, &vtl_1);
    delay(5000);
    go_red(&vtl_1, &vtl_3);
    go_green(&vtl_3, &vtl_1);
    delay(5000);
    go_red(&vtl_3, &vtl_1);
    last_pair = TWO_AND_FOUR;
  } else if (last_pair == TWO_AND_FOUR) {
    go_green(&vtl_1, &vtl_3);
    delay(5000);
    go_red(&vtl_1, &vtl_3);
    go_green(&vtl_3, &vtl_1);
    delay(5000);
    go_red(&vtl_3, &vtl_1);
    last_pair = ONE_AND_THREE;
  }
}
void pdtl_go_red(pedestrian_traffic_light *pdtl) {
   digitalWrite(pdtl->green_pin, LOW);

  while (pdtl->red_time <= 5) {
    digitalWrite(pdtl->red_pin, HIGH);
    digitalWrite(pdtl->green_pin, LOW);
    delay(500);
    digitalWrite(pdtl->red_pin, LOW);
    delay(500);
    digitalWrite(pdtl->red_pin, HIGH); 
    pdtl->red_time += 1;
  }

  digitalWrite(pdtl->red_pin, HIGH);
  digitalWrite(pdtl->green_pin, LOW);
  pdtl->red_time = 0;
  vtl_go_green();
}

void pdtl_go_green(pedestrian_traffic_light *pdtl) {
  delay(3000);
  digitalWrite(pdtl->red_pin, LOW);
  digitalWrite(pdtl->green_pin, HIGH);
  delay(3000);
  pdtl_go_red(pdtl);
}

void setup() {
  int i = 0, outputs = 11;
  for (i = 0; i < outputs; i++)
    pinMode((i + 5), OUTPUT);
  pdtl = { 0, 5, 6 }; // red_time, green_pin, red_pin
  vtl_1 = { 9, 10, 8 }; // green_pin, red_pin, yellow_pin
  vtl_3 = { 12, 11, 13 }; // green_pin, red_pin, yellow_pin
}

void loop() {
//  pdtl_loop(&pdtl);
//  digitalWrite(vtl_1.green_pin, HIGH);
//  digitalWrite(vtl_3.green_pin, HIGH);
//  digitalWrite(vtl_1.green_pin, LOW);
//  digitalWrite(vtl_3.green_pin, LOW);
  if (can_pedestrian_cross()) {
    pdtl_go_green(&pdtl);
  }
//  go_green(&vtl_1);
//  go_green(&vtl_3);
}
