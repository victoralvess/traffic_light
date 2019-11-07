#include <stdarg.h>

typedef struct {
  int red_timer;
  int green_pin;
  int red_pin;
} pedestrian_traffic_light;

typedef struct {
  int green_pin;
  int red_pin;
  int yellow_pin;
} vehicle_traffic_light;

int can_pedestrian_cross();
void init_traffic_lights();
void turn_on(int, ...);
void turn_off(int, ...);

void pdtl_go_green(pedestrian_traffic_light *);
void pdtl_go_red(pedestrian_traffic_light *);
void alternate_pdtl(pedestrian_traffic_light *);
void alternate_pdtl_red_light(pedestrian_traffic_light *);

void vtls_go_green();
void alternate_vtls(vehicle_traffic_light *, vehicle_traffic_light *);
void go_green(vehicle_traffic_light *, vehicle_traffic_light *);
void go_red(vehicle_traffic_light *, vehicle_traffic_light *);

pedestrian_traffic_light pdtl;
vehicle_traffic_light vtl_1, vtl_2, vtl_3, vtl_4;

int PEDESTRIAN_GREEN_LIGHT_DELAY = 3000; // tempo de delay antes e depois de ligar o verde (pedestre)
int PEDESTRIAN_RED_LIGHT_BLINK_DELAY = 500; // tempo de delay da "piscada" do vermelho (pedestre)
int PEDESTRIAN_VEHICLE_DELAY = 1200;

int VEHICLE_TRAFFIC_LIGHT_DELAY_BETWEEN_PAIRS = 1000; // tempo de delay antes de ligar o outro par de semáforos (veículos)
int VEHICLE_TRAFFIC_LIGHT_GREEN_DELAY = 5000; // tempo do sinal verde ligado (veículo)
int VEHICLE_TRAFFIC_LIGHT_YELLOW_DELAY = 2000; // tempo do sinal amarelo ligado (veículo)

void setup() {
    int i = 0, outputs = 11;
    for (i = 0; i < outputs; i++)
        pinMode((i + 5), OUTPUT);

    init_traffic_lights();
}

void loop() {
    if (can_pedestrian_cross()) {
        alternate_pdtl(&pdtl);
        delay(PEDESTRIAN_VEHICLE_DELAY);
        vtls_go_green();
    }
}

void init_traffic_lights() {
    pdtl = { 0, 5, 6 }; // red_timer, green_pin, red_pin
    turn_off(2, pdtl.green_pin, pdtl.red_pin); // quantidade, pino 1, pino 2, pino 3

    // Semáforos opostos (formam pares)
    vtl_1 = { 7, 9, 8 }; // green_pin, red_pin, yellow_pin
    turn_on(1, vtl_1.red_pin);
    turn_off(2, vtl_1.green_pin, vtl_1.yellow_pin);
    vtl_3 = { 7, 9, 8 }; // green_pin, red_pin, yellow_pin
    turn_on(1, vtl_3.red_pin);
    turn_off(2, vtl_3.green_pin, vtl_3.yellow_pin);

    // Semáforos opostos(formam pares)
    vtl_2 = { 10, 12, 11 }; // green_pin, red_pin, yellow_pin
    turn_on(1, vtl_2.red_pin);
    turn_off(2, vtl_2.green_pin, vtl_2.yellow_pin);
    vtl_4 = { 10, 12, 11 }; // green_pin, red_pin, yellow_pin
    turn_on(1, vtl_4.red_pin);
    turn_off(2, vtl_4.green_pin, vtl_4.yellow_pin);
}

void turn_on(int pins, ...) {
    va_list args;
    int i = 0;
    
    va_start(args, pins);
    for (i = 0; i < pins; i++) {
        int pin = va_arg(args, int);
        digitalWrite(pin, HIGH);
    }

    va_end(args);
}

void turn_off(int pins, ...) {
    va_list args;
    int i = 0;
    
    va_start(args, pins);
    for (i = 0; i < pins; i++) {
        int pin = va_arg(args, int);
        digitalWrite(pin, LOW);
    }

    va_end(args);
}

int can_pedestrian_cross() {
    return (
        (digitalRead(vtl_1.red_pin) == HIGH && digitalRead(vtl_1.green_pin) == LOW) &&
        (digitalRead(vtl_2.red_pin) == HIGH && digitalRead(vtl_2.green_pin) == LOW)
    );
}

void alternate_pdtl(pedestrian_traffic_light *pdtl) {
    delay(PEDESTRIAN_GREEN_LIGHT_DELAY);
    pdtl_go_green(pdtl);
    delay(PEDESTRIAN_GREEN_LIGHT_DELAY);
    pdtl_go_red(pdtl);
}

void pdtl_go_green(pedestrian_traffic_light *pdtl) {
    digitalWrite(pdtl->red_pin, LOW);
    digitalWrite(pdtl->green_pin, HIGH);
}

void pdtl_go_red(pedestrian_traffic_light *pdtl) {
    digitalWrite(pdtl->green_pin, LOW);

    while (pdtl->red_timer <= 5) {
        alternate_pdtl_red_light(pdtl);
        pdtl->red_timer += 1;
    }

    digitalWrite(pdtl->red_pin, HIGH);
    digitalWrite(pdtl->green_pin, LOW);
    pdtl->red_timer = 0;
}

void alternate_pdtl_red_light(pedestrian_traffic_light *pdtl) {
    digitalWrite(pdtl->red_pin, HIGH);
    delay(PEDESTRIAN_RED_LIGHT_BLINK_DELAY);
    digitalWrite(pdtl->red_pin, LOW);
    delay(PEDESTRIAN_RED_LIGHT_BLINK_DELAY);
    digitalWrite(pdtl->red_pin, HIGH); 
}

void vtls_go_green() {
    alternate_vtls(&vtl_1, &vtl_3);
    delay(VEHICLE_TRAFFIC_LIGHT_DELAY_BETWEEN_PAIRS);
    alternate_vtls(&vtl_2, &vtl_4);
}

void alternate_vtls(vehicle_traffic_light *vtl_1, vehicle_traffic_light *vtl_2) {
    go_green(vtl_1, vtl_2);
    delay(VEHICLE_TRAFFIC_LIGHT_GREEN_DELAY);
    go_red(vtl_1, vtl_2);
}

void go_green(vehicle_traffic_light *vtl_1, vehicle_traffic_light *vtl_2) {
    digitalWrite(vtl_1->red_pin, LOW);
    digitalWrite(vtl_1->green_pin, HIGH);
    
    digitalWrite(vtl_2->red_pin, LOW);
    digitalWrite(vtl_2->green_pin, HIGH);
}

void go_red(vehicle_traffic_light *vtl_1, vehicle_traffic_light *vtl_2) {
    digitalWrite(vtl_1->green_pin, LOW);
    digitalWrite(vtl_1->yellow_pin, HIGH);
    
    digitalWrite(vtl_2->green_pin, LOW);
    digitalWrite(vtl_2->yellow_pin, HIGH);
    
    delay(VEHICLE_TRAFFIC_LIGHT_YELLOW_DELAY);
    
    digitalWrite(vtl_1->yellow_pin, LOW);
    digitalWrite(vtl_1->red_pin, HIGH);
    
    digitalWrite(vtl_2->yellow_pin, LOW);
    digitalWrite(vtl_2->red_pin, HIGH);
}