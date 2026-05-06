#include <stdio.h>
#include "cpu.h"

int main() {
    CPU cpu;
    inicializar_cpu(&cpu);
    bool running = true;

    // --- PROGRAMA DE PRUEBA ---
    cpu.regs[1] = 5;  // RS
    cpu.regs[2] = 3;  // RT
    program_memory[0] = 0x0312; // ADD
    program_memory[1] = 0x0000; // Corta la ejecución

    // Ciclo Principal
    while (running) {
        
        // FETCH
        uint16_t instr = program_memory[cpu.pc];
        cpu.pc++; 
        
        if (instr == 0x0000) break;

        // DECODE
        uint8_t opcode = (instr >> 12) & 0x0F;
        uint8_t rd     = (instr >> 8)  & 0x0F;
        uint8_t rs     = (instr >> 4)  & 0x0F;
        uint8_t rt     = instr & 0x0F;         
        uint16_t jump_addr = instr & 0x0FFF;

        // EXECUTE (Llamamos a la función del otro archivo)
        // Usamos &cpu y &running porque pasamos la memoria original (punteros),
        // así la función puede modificar los registros de verdad.
        ejecutar_instruccion(&cpu, opcode, rd, rs, rt, jump_addr, &running);
    }

    printf("Ejecución finalizada. El registro 3 vale: %d\n", cpu.regs[3]);
    return 0;
}