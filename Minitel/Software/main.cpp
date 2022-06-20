extern void setup();
extern void loop();

int main() {
   setup();
   for(;;) {
      loop();
   }
   return 0;
}
