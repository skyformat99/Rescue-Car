/* Interrupt Handlers */

int c = 0;
extern void distance_vector(unsigned pc);
//extern void audio_sensor_vector(unsigned pc);

void interrupt_vector(unsigned pc) {
//    for (int i = 0; i < 100; i++) c++;
    printf( "i");
    distance_vector(pc);
  //  audio_sensor_vector(pc);
}

// The rest of these should never be called
void fast_interrupt_vector(int pc) {}
void reset_vector(int pc) {}
void undefined_instruction_vector(int pc) {}
void software_interrupt_vector(int pc) {}
void prefetch_abort_vector(int pc) {}
void data_abort_vector(int pc) {}

