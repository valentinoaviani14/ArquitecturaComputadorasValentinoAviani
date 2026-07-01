**Casos de Testeo - RTM32 / STX4**

# Caso 1
## Descripción:
Testeo de la instrucción aritmética de tipo R `ADD` para verificar la correcta decodificación y ejecución de una suma entre dos registros de propósito general.

## Instrucctions: instrucciones que use durante el test
* `reset`
* `set r10 5`
* `set r11 3`
* `set [0x0] 0x0296C01C`
* `set pc 0x0`
* `step 1`
* `registers`

## Precondiciones: 
- El sistema debe estar reseteado y en modo Kernel por defecto.
- [cite_start]Se debe cargar previamente el valor `5` en el registro `R10` ($R[10]$ o `$t0`) mediante el comando de depuración[cite: 3, 13].
- [cite_start]Se debe cargar previamente el valor `3` en el registro `R11` ($R[11]$ o `$t1`)[cite: 3, 13].
- [cite_start]Se escribe en la dirección de memoria `0x0` la instrucción en hexadecimal `0x0296C01C`, que corresponde a `add $12, $10, $11` en la arquitectura STX4[cite: 39, 42, 62, 145].
- [cite_start]El Contador de Programa (PC) debe apuntar a la dirección `0x0`.

## Code
RTM32> reset
System reset sequence complete. Target PC: 0xF0000000 (Mode: KERNEL)
RTM32> set r10 5
Register R10 set to 0x00000005
RTM32> set r11 3
Register R11 set to 0x00000003
RTM32> set [0x0] 0x0296C01C
RTM32> set pc 0x0
Program Counter (PC) set to 0x00000000
RTM32> step 1
Stepped instructions. Target PC: 0x00000004
RTM32> registers
=== General Purpose Registers ===
R[ 0]: 0x00000000   R[ 1]: 0x00000000   R[ 2]: 0x00000000   R[ 3]: 0x00000000
R[ 4]: 0x00000000   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000
R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000005   R[11]: 0x00000003
R[12]: 0x00000008   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000
R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000
R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000
R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000
R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===
PC      : 0x00000004  CAUSE   : 0x00000000  EPC     : 0x00000000
BADVADR : 0x00000000  VBR     : 0xF0000000

Execution State:
Mode: KERNEL | Flags: [-----]

Last Memory Operation:
Address: 0x00000000 | Size: 0x00000004 | Type: FETCH

Conclusiones: Anduvo. Se llegó a esta conclusión porque tras realizar el paso único de ejecución, el registro destino R12 pasó de 0x0 a 0x8, demostrando que la unidad aritmética decodificó correctamente el Opcode 00000 y la función 011100 del procesador STX4

## Caso 2: 

Descripción:
Testeo de la instrucción de tipo I ADDI (Suma Inmediata) para comprobar la carga directa de una constante en un registro utilizando la extensión de signo del procesador y el registro cableado a cero.

Instrucctions: instrucciones que use durante el test

reset

set [0x0] 0x08140019

set pc 0x0

step 1

registers

Precondiciones:El procesador debe estar inicializado mediante una secuencia de reset completa.Se escribe en la dirección de memoria 0x0 el valor hexadecimal 0x08140019, el cual representa la instrucción addi $10, $0, 25 (Opcode 00001, registro fuente $0 o $zero, registro destino R10, e inmediato 25).  El apuntador del programa PC debe estar seteado en 0x0 para iniciar en la instrucción bajo prueba.

RTM32> reset

System reset sequence complete. Target PC: 0xF0000000 (Mode: KERNEL)

RTM32> set [0x0] 0x08140019

RTM32> set pc 0x0

Program Counter (PC) set to 0x00000000

RTM32> step 1

Stepped instructions. Target PC: 0x00000004

RTM32> registers

=== General Purpose Registers ===
R[ 0]: 0x00000000   R[ 1]: 0x00000000   R[ 2]: 0x00000000   R[ 3]: 0x00000000
R[ 4]: 0x00000000   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000
R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000000   R[11]: 0x00000000
R[12]: 0x00000000   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000
R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000
R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000
R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000
R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===
PC      : 0x00000004  CAUSE   : 0x00000003  EPC     : 0x00000000
BADVADR : 0x00000000  VBR     : 0x00000002

Execution State:
Mode: KERNEL | Flags: [-----]

Last Memory Operation:
Address: 0x00000000 | Size: 0x00000004 | Type: FETCH

Conclusiones: Al final de la página 4, el manual advierte textualmente: "Actualmente hay un bug importante a solucionar en la instrucción ANDI". Nose si tiene que ver con esto, pero esto fue lo que me ocurrio explicitamente.
 
# Caso 3
## Descripción: que estoy testeando
Testeo de la instrucción de tipo I `SW` (Store Word) para comprobar el ciclo de escritura en la memoria RAM calculando una dirección efectiva mediante base más desplazamiento (offset).

## Instrucctions: instrucciones que use durante el test
* `reset`
* `set r10 0xABCDEFFF`
* `set [0x0] 0x48140000`
* `set pc 0x0`
* `step 1`
* `registers`

## Precondiciones: 
- El sistema debe encontrarse inicializado tras una secuencia de reset completa.
- Se altera el contenido del registro `R10` asignándole el patrón de datos de prueba `0xABCDEFFF` para ser usado como fuente.
- Se escribe en la celda de memoria `0x0` el código equivalente a `0x48140000`, correspondiente a la instrucción `sw $10, 0($0)` según el mapeo de opcodes del manual del procesador STX4.
- El PC debe estar direccionado en `0x0`.

## Code:

RTM32> reset
System reset sequence complete. Target PC: 0xF0000000 (Mode: KERNEL)
RTM32> set r10 0xABCDEFFF`
Register R10 set to 0xABCDEFFF
RTM32> set [0x0] 0x48140000
RTM32> set pc 0x0
Program Counter (PC) set to 0x00000000
RTM32> step 1
Stepped instructions. Target PC: 0x00000004
RTM32> registers
=== General Purpose Registers ===
R[ 0]: 0x00000000   R[ 1]: 0x00000000   R[ 2]: 0x00000000   R[ 3]: 0x00000000
R[ 4]: 0x00000000   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000
R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0xABCDEFFF   R[11]: 0x00000000
R[12]: 0x00000000   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000
R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000
R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000
R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000
R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===
PC      : 0x00000004  CAUSE   : 0x00000000  EPC     : 0x00000000
BADVADR : 0x00000000  VBR     : 0xF0000000

Execution State:
Mode: KERNEL | Flags: [-----]

Last Memory Operation:
Address: 0x00000000 | Size: 0x00000002 | Type: WRITE

Postcondiciones:
Ejecutar el comando registers para evaluar el estado de los registros de control e inspeccionar la última operación de memoria realizada (Last Memory Operation).

Verificar que el registro CAUSE permanezca en 0x00000000, garantizando que la ejecución no interrumpió el flujo del procesador por excepciones de alineación o código inválido

Conclusiones:
Anduvo. Se llegó a esta conclusión debido a que tras realizar el paso único (step 1), el registro de control CAUSE se mantuvo en 0x00000000, indicando que no se generaron excepciones. Asimismo, la interfaz reportó exitosamente un evento de escritura en memoria (Type: WRITE) sobre la dirección efectiva calculada 0x00000000.

# Caso 4
## Descripción:
Testeo de la instrucción de salto condicional de tipo I `BEQ` (Branch on Equal) para verificar el cálculo del nuevo Program Counter (PC) cuando la condición de igualdad entre dos registros se cumple.

## Instrucctions: instrucciones que use durante el test
* `reset`
* `set r10 5`
* `set r11 5`
* `set [0x0] 0x82960002`
* `set pc 0x0`
* `step 1`
* `registers`

## Precondiciones: 
- El procesador se inicializa mediante la secuencia de reset completa, operando en modo KERNEL.
- [cite_start]Se cargan previamente los registros `R10` y `R11` con el mismo valor numérico (`5`) para forzar que la condición analizada por la instrucción sea verdadera.
- [cite_start]Se escribe en la dirección de memoria `0x0` la instrucción en hexadecimal `0x82960002`, que corresponde a `beq $10, $11, 2` en la arquitectura STX4.
- El Contador de Programa (PC) debe apuntar a la dirección inicial `0x0`.

## Code

RTM32> reset
System reset sequence complete. Target PC: 0xF0000000 (Mode: KERNEL)
RTM32> set r10 5
Register R10 set to 0x00000005
RTM32> set r11 5
Register R11 set to 0x00000005
RTM32> set [0x0] 0x82960002   
RTM32> set pc 0x0
Program Counter (PC) set to 0x00000000
RTM32> step 1
Stepped instructions. Target PC: 0x0000000C
RTM32> registers
=== General Purpose Registers ===
R[ 0]: 0x00000000   R[ 1]: 0x00000000   R[ 2]: 0x00000000   R[ 3]: 0x00000000
R[ 4]: 0x00000000   R[ 5]: 0x00000000   R[ 6]: 0x00000000   R[ 7]: 0x00000000
R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000005   R[11]: 0x00000005
R[12]: 0x00000000   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000
R[16]: 0x00000000   R[17]: 0x00000000   R[18]: 0x00000000   R[19]: 0x00000000
R[20]: 0x00000000   R[21]: 0x00000000   R[22]: 0x00000000   R[23]: 0x00000000
R[24]: 0x00000000   R[25]: 0x00000000   R[26]: 0x00000000   R[27]: 0x00000000
R[28]: 0x00000000   R[29]: 0x00000000   R[30]: 0x00000000   R[31]: 0x00000000

=== Control & Special Registers ===
PC      : 0x0000000C  CAUSE   : 0x00000000  EPC     : 0x00000000
BADVADR : 0x00000000  VBR     : 0xF0000000

Execution State:
Mode: KERNEL | Flags: [-----]

Last Memory Operation:
Address: 0x00000000 | Size: 0x00000004 | Type: FETCH

## Postcondiciones:

Ejecutar el comando registers para evaluar el estado de los registros de control, prestando particular atención a la actualización del Contador de Programa (PC).

Comprobar que no se hayan disparado excepciones revisando que el registro CAUSE se mantenga en 0x00000000.

Verificar que el valor final del PC coincida matemáticamente con la ecuación de salto detallada en el manual: $PC = PC + 4 \times imm$.  

Conclusiones:Anduvo. Se llegó a esta conclusión debido a que la condición evaluada ($R[10] == R[11]$) resultó verdadera, lo que disparó el recálculo del flujo de ejecución sin levantar ninguna excepción en el registro CAUSE. 

Siguiendo la fórmula arquitectónica del procesador STX4 , el sistema tomó el valor del PC de la siguiente instrucción (4) y le sumó el desplazamiento calculado a partir del inmediato ($2 \times 4 = 8$). El resultado final arrojó correctamente un nuevo PC de 0x0000000C ($12$ en decimal), demostrando que la unidad de control procesa los saltos incondicionales de manera adecuada.
