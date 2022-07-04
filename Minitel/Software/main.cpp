extern void setup();
extern void loop();

int    global_argc;
char** global_argv;

int main(int argc, char** argv) {
   global_argc = argc;
   global_argv = argv;
   setup();
   for(;;) {
      loop();
   }
   return 0;
}
