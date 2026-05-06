#include <stdio.h>
#include "cpu.h" // Incluimos nuestro propio header

// Acá CREAMOS las memorias reales en la RAM de la compu
uint16_t data_memory[MEM_SIZE];
uint16_t program_memory[MEM_SIZE];

void inicializar_cpu(CPU *cpu) {
    cpu->pc = 0;
    cpu->psw = 0;
    for(int i = 0; i < 16; i++) {
        cpu->regs[i] = 0;
    }
}

// Fase EXECUTE aislada en una función
void ejecutar_instruccion(CPU *cpu, uint8_t opcode, uint8_t rd, uint8_t rs, uint8_t rt, uint16_t jump_addr, bool *running) {
    switch (opcode) {
        case 0x0: // ADD
            cpu->regs[rd] = cpu->regs[rs] + cpu->regs[rt];
            break;

        case 0x1: // LW
            cpu->regs[rd] = data_memory[cpu->regs[rs] + rt];
            break;

        case 0x3: // SW
            data_memory[cpu->regs[rs] + rt] = cpu->regs[rd];
            break;

        case 0x4: // BEQ
            if (cpu->regs[rd] == cpu->regs[rs]) {
                int8_t offset = rt; 
                if (offset & 0x08) offset |= 0xF0; // Extensión de signo
                cpu->pc = cpu->pc + offset;
            }
            break;

        case 0xE: // J
            cpu->pc = jump_addr;
            break;

        default:
            printf("Error: Opcode desconocido %X en PC: %d\n", opcode, cpu->pc - 1);
            *running = false;
            break;
    }
}