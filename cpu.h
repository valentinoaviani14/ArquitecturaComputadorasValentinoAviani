#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#define MEM_SIZE 1024

// 1. Estructura de la CPU
typedef struct {
    unsigned int pc;
    unsigned int psw;
    uint16_t regs[16];
} CPU;

// 2. Uso de 'extern': 
// Le avisa a todos los archivos que estas memorias existen en ALGÚN lugar,
// pero sin crearlas dos veces para evitar errores de duplicación.
extern uint16_t data_memory[MEM_SIZE];
extern uint16_t program_memory[MEM_SIZE];

// 3. Prototipos de funciones
void inicializar_cpu(CPU *cpu);
void ejecutar_instruccion(CPU *cpu, uint8_t opcode, uint8_t rd, uint8_t rs, uint8_t rt, uint16_t jump_addr, bool *running);

#endif