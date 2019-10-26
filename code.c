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

void go_red(vehicle_traffic_light *);
void go_green(vehicle_traffic_light *);


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

void go_green(vehicle_traffic_light *vtl) {
  digitalWrite(vtl->red_pin, LOW);
  digitalWrite(vtl->green_pin, HIGH);
  delay(5000);
  go_red(vtl);
}

void go_red(vehicle_traffic_light *vtl) {
  digitalWrite(vtl->green_pin, LOW);
  digitalWrite(vtl->yellow_pin, HIGH);
  delay(2000);
  digitalWrite(vtl->yellow_pin, LOW);
  digitalWrite(vtl->red_pin, HIGH);
  delay(5000);
  go_green(vtl);
}

void setup() {
  int i = 0, outputs = 11;
  for (i = 0; i < outputs; i++)
    pinMode((i + 5), OUTPUT);
  pdtl = { 0, 6, 5 }; // red_time, green_pin, red_pin
  vtl_1 = { 7, 8, 9 }; // green_pin, red_pin, yellow_pin
  vtl_3 = { 10, 11, 12 }; // green_pin, red_pin, yellow_pin
}

void loop() {
  pdtl_loop(&pdtl);
  go_green(&vtl_1);
  go_green(&vtl_3);
}
