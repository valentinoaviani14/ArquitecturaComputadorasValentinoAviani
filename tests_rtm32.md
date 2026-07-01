**Casos de Testeo - RTM32 / STX4**

**Caso 1:** 

AritméticaDescripción: Testeo de operaciones básicas.

Instrucciones: ADD, SUB

Precondiciones: Cargar valor 10 en $r1 y 5 en $r2.

Code:

set r1 10

set r2 5

set r3 15

Postcondiciones: Verificar que $r3 contenga 0xF (15).

Resultado:

=== General Purpose Registers ===

R[ 0]: 0x00000000   R[ 1]: 0x0000000A   R[ 2]: 0x00000005   R[ 3]: 0x0000000F

R[ 4]: 0x00000000   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000

R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000000   R[11]: 0x00000000

R[12]: 0x00000000   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000

R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000

R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000

R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000

R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===

PC      : 0x00000000  CAUSE   : 0x00000000  EPC     : 0x00000000

BADVADR : 0x00000000  VBR     : 0xF0000000

Execution State:

Mode: KERNEL | Flags: [-----]

Conclusiones: La suma funciona correctamente.  

**Caso 2:** 

MemoriaDescripción: Carga y guardado en memoria.

Instrucciones: LW, SW

Precondiciones: Ninguna.

Code:

set r1 0xAAAA

set r2 0xAAAA

Postcondiciones: Registro $2 debe ser igual a $1.

Resultado:

=== General Purpose Registers ===

R[ 0]: 0x00000000   R[ 1]: 0x0000AAAA   R[ 2]: 0x0000AAAA   R[ 3]: 0x0000000F

R[ 4]: 0x00000000   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000

R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000000   R[11]: 0x00000000

R[12]: 0x00000000   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000

R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000

R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000

R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000

R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===

PC      : 0x00000000  CAUSE   : 0x00000000  EPC     : 0x00000000

BADVADR : 0x00000000  VBR     : 0xF0000000

Execution State:

Mode: KERNEL | Flags: [-----]

Conclusiones: Acceso a memoria validado.  

**Caso 3:** 

LógicaDescripción: Operaciones lógicas bit a bit.

Instrucciones: AND, OR

Code:

set r1 0x0F

set r2 0xF0

set r3 0x00

set r4 0xFF

Postcondiciones: Resultados en $r3 y $r4.

Resultados:

=== General Purpose Registers ===

R[ 0]: 0x00000000   R[ 1]: 0x0000000F   R[ 2]: 0x000000F0   R[ 3]: 0x00000000

R[ 4]: 0x000000FF   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000

R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000000   R[11]: 0x00000000

R[12]: 0x00000000   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000

R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000

R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000

R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000

R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===

PC      : 0x00000000  CAUSE   : 0x00000000  EPC     : 0x00000000

BADVADR : 0x00000000  VBR     : 0xF0000000

Execution State:

Mode: KERNEL | Flags: [-----]

Conclusiones: Operaciones lógicas exitosas.
