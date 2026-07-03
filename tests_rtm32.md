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
- Se debe cargar previamente el valor `5` en el registro `R10` ($R[10]$ o `$t0`) mediante el comando de depuración.
- Se debe cargar previamente el valor `3` en el registro `R11` ($R[11]$ o `$t1`)
- Se escribe en la dirección de memoria `0x0` la instrucción en hexadecimal `0x0296C01C`, que corresponde a `add $12, $10, $11` en la arquitectura STX4
- El Contador de Programa (PC) debe apuntar a la dirección `0x0`.

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

# Caso 2: 

## Descripción:
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
## Descripción:
Testeo de la instrucción de tipo I `SW` (Store Word) en la versión corregida del simulador para comprobar el ciclo de escritura completo de una palabra (4 bytes) en la memoria RAM mediante direccionamiento indexado.

## Instrucctions: instrucciones que use durante el test
* `reset`
* `set r10 0xABCDEFFF`
* `set [0x0] 0x48140000`
* `set pc 0x0`
* `step 1`
* `registers`

## Precondiciones: 
- El sistema debe encontrarse inicializado tras una secuencia de reset completa operando en modo KERNEL.
- Se altera el contenido del registro `R10` asignándole el patrón de datos de prueba `0xABCDEFFF` para ser usado como fuente.
- Se escribe en la celda de memoria `0x0` el código equivalente a `0x48140000`, correspondiente a la instrucción `sw $10, 0($0)` según el mapeo de opcodes del manual del procesador STX4.
- El PC debe estar direccionado en `0x0`.

## Code

RTM32> reset
System reset sequence complete. Target PC: 0xF0000000 (Mode: KERNEL)
RTM32> set r10 0xABCDEFFF
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
Address: 0x00000000 | Size: 0x00000004 | Type: WRITE

## Postcondiciones:
Ejecutar el comando registers para evaluar el estado de los registros de control e inspeccionar la última operación de memoria realizada (Last Memory Operation).  

Verificar que el registro CAUSE permanezca en 0x00000000, garantizando que la ejecución no interrumpió el flujo del procesador por excepciones de alineación o código inválido.  Constatar que el campo Size indique un tamaño de transferencia de 0x00000004 bytes.  

## Conclusiones:

Anduvo. Se llegó a esta conclusión debido a que tras realizar el paso único (step 1), el registro de control CAUSE se mantuvo en 0x00000000, indicando la ausencia de excepciones. A diferencia de las pruebas con la versión anterior del software (donde se observaba una escritura anómala de 2 bytes), el nuevo entorno de la máquina virtual procesó la instrucción de manera exitosa, confirmando una transferencia de almacenamiento completa de 4 bytes (Size: 0x00000004) de tipo WRITE en la dirección calculada 0x00000000. Con esto queda validada la corrección del bug que me pasaba antes.

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
- Se cargan previamente los registros `R10` y `R11` con el mismo valor numérico (`5`) para forzar que la condición analizada por la instrucción sea verdadera.
- Se escribe en la dirección de memoria `0x0` la instrucción en hexadecimal `0x82960002`, que corresponde a `beq $10, $11, 2` en la arquitectura STX4.
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

# Caso 5
## Descripción:
Testeo de la instrucción aritmética de tipo R `SUB` para verificar la resta entre dos registros de propósito general.

## Instrucctions: instrucciones que use durante el test
* `reset`
* `set r10 10`
* `set r11 4`
* `set [0x0] 0x0296C01D`
* `set pc 0x0`
* `step 1`
* `registers`

## Precondiciones: 
- El sistema debe estar reseteado y en modo KERNEL.
- Se cargan previamente los registros `R10` con `10` ($0xA$) y `R11` con `4` para realizar la operación $10 - 4$.
- Se escribe en la dirección de memoria `0x0` la instrucción `0x0296C01D`, correspondiente a `sub $12, $10, $11` (Opcode 00000, funct 011101).
- El PC debe apuntar a `0x0`.

## Code
RTM32> reset
System reset sequence complete. Target PC: 0xF0000000 (Mode: KERNEL)
RTM32> set r10 10
Register R10 set to 0x0000000A
RTM32> set r11 4
Register R11 set to 0x00000004
RTM32> set [0x0] 0x0296C01D   
RTM32> set pc 0x0
Program Counter (PC) set to 0x00000000
RTM32> step 1
Stepped instructions. Target PC: 0x00000004
RTM32> registers
=== General Purpose Registers ===
R[ 0]: 0x00000000   R[ 1]: 0x00000000   R[ 2]: 0x00000000   R[ 3]: 0x00000000
R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x0000000A   R[11]: 0x00000004
R[12]: 0x00000006   R[13]: 0x00000000   R[14]: 0x00000000   R[15]: 0x00000000
...
=== Control & Special Registers ===
PC      : 0x00000004  CAUSE   : 0x00000000  EPC     : 0x00000000

Postcondiciones:Ejecutar el comando registers para evaluar si R12 almacenó el resultado esperado.Comprobar que el registro CAUSE se mantenga en 0x00000000.

Conclusiones:Anduvo. Se llegó a esta conclusión porque tras realizar el paso de ejecución, el registro destino R12 pasó a valer 0x6 ($10 - 4 = 6$), demostrando que la ALU procesa correctamente las restas en formato Tipo R sin generar desbordamientos ni excepciones en el estado de control.

# Caso 6

Descripción:Testeo de la instrucción lógica de tipo R AND para evaluar el enmascaramiento bit a bit entre dos registros.

Instrucctions: instrucciones que use durante el test

reset

set r10 0xFFFF

set r11 0x000F

set [0x0] 0x0296C008

set pc 0x0

step 1

registers

Precondiciones:El sistema está reseteado en modo KERNEL.Se cargan los registros R10 con 0xFFFF y R11 con 0x000F para testear la compuerta lógica.Se carga en memoria la instrucción 0x0296C008, que representa and $12, $10, $11 (Opcode 00000, funct 001000).  

## Code

RTM32> reset

System reset sequence complete.

RTM32> set r10 0xFFFF

RTM32> set r11 0x000F

RTM32> set [0x0] 0x0296C008   

RTM32> set pc 0x0

RTM32> step 1

Stepped instructions. Target PC: 0x00000004

RTM32> registers

=== General Purpose Registers ===
R[10]: 0x0000FFFF   R[11]: 0x0000000F

R[12]: 0x0000000F   R[13]: 0x00000000
...
=== Control & Special Registers ===
PC      : 0x00000004  CAUSE   : 0x00000000

Postcondiciones:Evaluar el valor final de R12.Revisar ausencia de excepciones en CAUSE.

Conclusiones:Anduvo. Al realizar la operación lógica AND bit a bit entre 0xFFFF y 0x000F, el resultado conservó únicamente los 4 bits menos significativos encendidos, guardando correctamente el valor 0x0000000F en el registro R12.

# Caso 7

Descripción:Testeo de la instrucción lógica de tipo R OR para verificar la suma lógica bit a bit.

Instrucctions: instrucciones que use durante el test
resetset r10 0x00F0
set r11 0x000F
set [0x0] 0x0296C009
set pc 0x0
step 1
registers

Precondiciones:El procesador se reinicia.Se setean R10 = 0x00F0 y R11 = 0x000F.Se inserta 0x0296C009 en la celda 0x0, lo cual equivale a or $12, $10, $11 (Opcode 00000, funct 001001).  

## Code

RTM32> reset

RTM32> set r10 0x00F0

RTM32> set r11 0x000F

RTM32> set [0x0] 0x0296C009

RTM32> set pc 0x0

RTM32> step 1

Target PC: 0x00000004

RTM32> registers
=== General Purpose Registers ===
R[10]: 0x000000F0   R[11]: 0x0000000F
R[12]: 0x000000FF   R[13]: 0x00000000
...
Postcondiciones:Observar el estado del registro destino R12.

Conclusiones:Anduvo. La instrucción combinó exitosamente los bits de ambos registros mediante la compuerta OR, uniendo 0x00F0 y 0x000F para arrojar un resultado final de 0x000000FF depositado de manera correcta en el registro R12.

# Caso 8

Descripción:Testeo de la instrucción de carga desde memoria de tipo I LW (Load Word) para validar la lectura alineada a la RAM.

Instrucctions: instrucciones que use durante el testresetset [0x0] 0x40140000set pc 0x0step 1registers

Precondiciones:Se aplica el reinicio del sistema.Se graba 0x40140000 en la dirección 0x0, que decodifica como lw $10, 0($0). Como la base es el registro $0 ($0$) y el offset es $0$, la CPU intentará leer el contenido de la dirección 0x0 (la misma instrucción que se está ejecutando).  

## Code RTM32> reset

RTM32> set [0x0] 0x40140000

RTM32> set pc 0x0

RTM32> step 1

Target PC: 0x00000004

RTM32> registers

=== General Purpose Registers ===
R[ 0]: 0x00000000   R[ 1]: 0x00000000
R[10]: 0x40140000   R[11]: 0x00000000
...

Last Memory Operation:

Address: 0x00000000 | Size: 0x00000004 | Type: READ

Postcondiciones:Chequear que R10 cargue el valor binario almacenado en la memoria en la dirección efectiva calculada.

Conclusiones:Anduvo. Se verificó que el procesador calculó la dirección efectiva ($0 + 0 = 0$) y ejecutó una operación de lectura (READ de 4 bytes) sobre la RAM, cargando exitosamente el valor 0x40140000 (que casualmente es el opcode de la instrucción misma) en el registro destino R10.

# Caso 9

Descripción:Testeo de la instrucción de salto incondicional de tipo J J (Jump) para asegurar el cálculo de direcciones directas.

Instrucctions: instrucciones que use durante el test

reset

set [0x0] 0x10000004

set pc 0x0

step 1

registers

Precondiciones:El sistema se prepara desde cero.Se carga la instrucción 0x10000004 (Opcode 00010), donde el campo address es 0x4. Dado que se multiplica por 4 para obtener la dirección final, el salto apuntará a 0x10 ($16$ en decimal).  

## Code

RTM32> reset

RTM32> set [0x0] 0x10000004

RTM32> set pc 0x0

RTM32> step 1

Stepped instructions. Target PC: 0x00000010

RTM32> registers

=== Control & Special Registers ===
PC      : 0x00000010  CAUSE   : 0x00000000

Postcondiciones:Verificar que el PC refleje la dirección de salto objetivo sin alterar registros generales.

Conclusiones:Anduvo. La instrucción sobrescribió correctamente el flujo de ejecución, ignorando el salto condicional. El decodificador concatenó los bits superiores del PC actual y multiplicó el inmediato del campo J por 4, llevando el PC final a la dirección esperada 0x00000010 de forma limpia.

# Caso 10

Descripción:Testeo de la instrucción de salto condicional BNE (Branch on Not Equal) para validar ramificaciones por desigualdad.

Instrucctions: instrucciones que use durante el test
reset
set r10 1
set r11 0
set [0x0] 0x8A960002
set pc 0x0
step 1
registers

Precondiciones:Registros R10 y R11 se setean con valores distintos (1 y 0).Se introduce 0x8A960002, que codifica bne $10, $11, 2. Al ser distintos, saltará $2$ palabras hacia adelante respecto al PC siguiente.  
## Code

RTM32> reset

RTM32> set r10 1

RTM32> set r11 0

RTM32> set [0x0] 0x8A960002

RTM32> set pc 0x0

RTM32> step 1

Target PC: 0x0000000C

RTM32> registers

=== Control & Special Registers ===
PC      : 0x0000000C  CAUSE   : 0x00000000

Postcondiciones:El PC debe reflejar la suma del offset.

Conclusiones:Anduvo. La condición de desigualdad se cumplió ($1 \neq 0$), provocando el branch. El hardware calculó la próxima dirección sumando el PC nominal ($4$) al offset desplazado ($2 \times 4 = 8$), dejando el Program Counter en 0x0000000C.

# Caso 11

Descripción:Testeo de la instrucción de desplazamiento lógico a la izquierda SLL (Shift Left Logical).Instrucctions: instrucciones que use durante el testresetset r10 0x1set [0x0] 0x00146080set pc 0x0step 1registersPrecondiciones:R10 contiene el valor 1.La instrucción 0x00146080 representa sll $12, $10, 2 (usa el campo auxiliar para indicar un corrimiento de 2 posiciones).  

Code

RTM32> reset
RTM32> set r10 0x1
RTM32> set [0x0] 0x00146080
RTM32> set pc 0x0
RTM32> step 1
RTM32> registers
=== General Purpose Registers ===
R[10]: 0x00000001
R[12]: 0x00000004

Postcondiciones:Verificar que R12 haya multiplicado efectivamente el valor por $2^2$.

Conclusiones:Anduvo. El procesador STX4 tomó el operando en R10 (0x1) y desplazó sus bits dos posiciones a la izquierda basándose en el campo aux, almacenando correctamente el resultado final de 0x4 en el registro R12.

# Caso 12

Descripción:Testeo de la instrucción comparativa SLT (Set on Less Than).

Instrucctions: instrucciones que use durante el test

reset
set r10 2
set r11 5
set [0x0] 0x0296C00C
set pc 0x0
step 1
registers

Precondiciones:R10 = 2 y R11 = 5.La instrucción 0x0296C00C decodifica como slt $12, $10, $11. Evalúa si R10 < R11, si es verdadero setea el destino en 1.  

Code 

RTM32> reset
RTM32> set r10 2
RTM32> set r11 5
RTM32> set [0x0] 0x0296C00C
RTM32> set pc 0x0
RTM32> step 1
RTM32> registers
=== General Purpose Registers ===
R[10]: 0x00000002   R[11]: 0x00000005
R[12]: 0x00000001

Postcondiciones:Confirmar que R12 cambie a 1 (booleano verdadero).

Conclusiones:Anduvo. La ALU efectuó la comparación numérica entre los registros; al ser $2 < 5$, devolvió un booleano positivo que se depositó con éxito como un 0x1 en R12.

# Caso 13

Descripción:Testeo de la instrucción LUI (Load Upper Immediate) para verificar la carga de constantes en la porción alta de la palabra.

Instrucctions: instrucciones que use durante el test

reset
set [0x0] 0x381400FF
set pc 0x0
step 1
registers

Precondiciones:El sistema inicia en limpio.La instrucción 0x381400FF se inyecta en memoria, significando lui $10, 0x00FF (Formato L: carga el inmediato en los 16 bits superiores de R10 y llena de ceros los inferiores). 

Code

RTM32> reset
RTM32> set [0x0] 0x381400FF
RTM32> set pc 0x0
RTM32> step 1
RTM32> registers
=== General Purpose Registers ===
R[10]: 0x00FF0000

Postcondiciones:Validar el alineamiento correcto de los 16 bits ingresados en la zona superior del registro destino.

Conclusiones:Anduvo. El procesador decodificó el formato L, tomó la constante de 16 bits 0x00FF proporcionada en el inmediato de la instrucción, la ubicó en la mitad más significativa (MSB) y completó la mitad baja (LSB) con ceros lógicos, dejando el registro R10 exactamente en 0x00FF0000.

# Caso 14

Descripción:Testeo de la instrucción JR (Jump Register) para certificar saltos dinámicos en tiempo de ejecución.

Instrucctions: instrucciones que use durante el test

reset
set r10 0x20
set [0x0] 0x0280000E
set pc 0x0
step 1
registers

Precondiciones:R10 se inicializa con el valor destino del salto, en este caso 0x20.La memoria en 0x0 recibe 0x0280000E, equivalente a jr $10 (Opcode 00000, funct 001110), forzando al hardware a copiar el valor del registro directamente al PC.  

Code

RTM32> reset
RTM32> set r10 0x20
RTM32> set [0x0] 0x0280000E
RTM32> set pc 0x0
RTM32> step 1
Target PC: 0x00000020
RTM32> registers
=== Control & Special Registers ===
PC      : 0x00000020  CAUSE   : 0x00000000

Postcondiciones:Asegurar que el PC tome de forma absoluta el contenido de R10.

Conclusiones:Anduvo. No se detectaron fallos de cálculo. El registro PC fue sobreescrito directamente por la unidad de control, abandonando la secuencia secuencial e incrustando el valor absoluto que residía en el registro fuente (0x20), logrando un cambio de flujo dinámico exitoso.

# Caso 15
## Descripción:
Re-testeo de la instrucción de tipo I `ADDI` (Suma Inmediata) tras la subsanación del bug de desborde en el decodificador de formatos inmediatos por parte de la cátedra, con el fin de verificar la correcta carga de constantes en un registro.

## Instrucctions: instrucciones que use durante el test
* `reset`
* `set [0x0] 0x08140019`
* `set pc 0x0`
* `step 1`
* `registers`

## Precondiciones:
- El procesador debe estar inicializado mediante una secuencia de reset completa operando en modo KERNEL.
- Se escribe en la dirección de memoria `0x0` el valor hexadecimal `0x08140019`, el cual representa la instrucción `addi $10, $0, 25` según el set de instrucciones del procesador STX4.
- El apuntador del programa PC debe estar seteado en `0x0` para iniciar la ejecución en la instrucción bajo prueba.

## Code

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
R[ 8]: 0x00000000   R[ 9]: 0x00000000   R[10]: 0x00000019   R[11]: 0x00000000
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
Address: 0x00000000 | Size: 0x00000004 | Type: FETCH

## Postcondiciones:
Ejecutar el comando registers para evaluar el estado final de los bancos de memoria de la CPU.

Constatar que el registro de control CAUSE permanezca limpio en 0x00000000 (sin excepciones de ejecución).

Verificar que el registro de propósito general R10 haya modificado exitosamente su contenido original por la constante decimal 25 (0x00000019 en hexadecimal).

## Conclusiones:
Anduvo. A diferencia del escenario analizado en las primeras pruebas (donde la falta de un delimitador de fin de rutina en las instrucciones lógicas con inmediato desbordaba el flujo provocando una excepción por instrucción ilegal CAUSE: 0x00000003), la nueva versión corregida por la cátedra decodificó e implementó el formato Tipo I de manera exitosa. El registro R10 asimiló correctamente la constante extendida con signo y la unidad de control operó sin disparar excepciones de hardware.

# Instrucciones restantes:

## Cuadro Resumen: Instrucciones Restantes

A continuación se detalla la planificación para las instrucciones de la arquitectura STX4 que restan ser validadas en el simulador RTM32. Para optimizar el testeo, las agrupo por familia de operación.

| Familia / Instrucciones | Formato | Propósito del Test | Setup (¿Qué debo hacer en consola?) | Verificación (Postcondiciones) |
| :--- | :---: | :--- | :--- | :--- |
| **Saltos a Subrutinas**<br>`JAL`, `JALR` | J / R | Validar el enlace y guardado de la dirección de retorno. | Cargar la instrucción de salto. No requiere variables previas. Ejecutar `step 1`. | Verificar que el `PC` apunte al destino del salto y que obligatoriamente el registro `$ra` (`R31`) haya guardado `PC + 4` |

| **Lógicas Inmediatas**<br>`ANDI`, `ORI`, `XORI` | L | Comprobar máscaras de bits contra constantes de 16 bits. | Setear un registro origen (ej. `R10`) con datos y cargar la instrucción con la constante (Formato L). | Observar el registro destino. **Ojo:** Para `ANDI` verificar si arroja excepción (`CAUSE: 0x3`), ya que el manual advierte un bug crítico en esta instrucción. |

| **Multiplicación y División**<br>`MUL`, `DIV`, `REST` | R | Evaluar la unidad aritmética compleja y guardado en 32/64 bits. | Cargar dos operandos numéricos en dos registros origen y ejecutar. | Revisar que el registro destino contenga el producto, cociente o resto exacto. |

| **Memoria Parcial**<br>`SH`, `SB`, `LH`, `LB` | I | Testear lecturas y escrituras de media palabra (16 bits) y bytes (8 bits). | Setear la memoria con un patrón (para Loads) o un registro (para Stores). | Ejecutar comando de memoria (`dump` o `examine`) y comprobar que los accesos alineados y no alineados escriban/lean la cantidad correcta de bytes. |

| **Desplazamientos Extra**<br>`SRL`, `SRA`, `SLLR`, `SRLR` | R | Comprobar desplazamientos lógicos/aritméticos a derecha y mediante registros. | Setear un registro a desplazar y cargar el inmediato en `aux` o en otro registro (versiones `R`). | Verificar el registro destino y prestar atención al bit de signo en los desplazamientos aritméticos (`SRA`). |

| **Branches Extendidos**<br>`BGT`, `BLT`, `BLE`, `BGE` | I | Validar ramificaciones por comparaciones de mayor/menor/igual. | Setear registros origen forzando condiciones verdaderas y falsas alternadamente. | Comprobar si el `PC` salta calculando $PC + 4 + offset$ o si sigue de largo dependiendo de la condición. |

| **Comparaciones (Set)** <br>`SLTU`, `SLTI`, `SLTIU` | R / I | Testear la bandera de "menor que" con constantes y sin signo. | Cargar registros con valores donde uno sea menor y luego mayor que el otro o que el inmediato. | Constatar que el registro destino cambie exclusivamente a `0x1` (verdadero) o `0x0` (falso). |

| **Sistema y Excepciones**<br>`TRAP`, `RFT`, `CFS`, `CTS` | R | Probar el pasaje a manejadores de excepciones y lectura de registros especiales. | Ejecutar la instrucción `TRAP` o usar `CFS/CTS` apuntando al registro `CAUSE`. | Confirmar si `PC` toma el valor del vector de interrupción y si el `EPC` guardó el retorno. |

> **Nota de testeo:** Debido a la inconsistencia detectada en las pruebas con formatos que utilizan operandos inmediatos (como ocurrió previamente con `ADDI` y `SW`), es altamente probable que las familias de **Lógicas Inmediatas** y **Memoria Parcial** presenten excepciones tempranas (`CAUSE: 0x00000003`) atribuibles a fallas del propio entorno del simulador al decodificar la estructura tipo I/L.
