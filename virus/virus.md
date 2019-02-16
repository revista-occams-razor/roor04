# Como funciona un virus informático?

_Author: Don Bit0_

_Roor Numero 4_

_Esta obra está bajo una [Licencia Creative Commons Atribución 4.0 Internacional](http://creativecommons.org/licenses/by/4.0/)._

Leélo en: [ROOR] (http://www.papermint-designs.com/roor/2018-06-seguridad-para-meros-mortales--virus)

-----
A parte de saber que los virus informáticos hacen que nuestro ordenador se ponga malito, sabéis algo más sobre estos intrigantes bichillos?. La mejor forma de estar protegidos ante esta amenaza, es conocer a tu enemigo... Y para eso estamos nosotros aquí :).

En este artículo vamos a explicaros los fundamentos más básicos de como funcionan los virus informáticos y romper algunos tópicos sobre estos programas tan alucinantes y tus archienemigos los antivirus :)

# Empecemos. Qué es un Virus?
Un virus informático no es más que un tipo especial de programa. Como en muchos otros casos, los virus informáticos, toman su nombre de una analogía con el mundo real ya que, en cierto modo, actúan como los virus biológicos que todos conocemos y que, generalmente no ponen enfermos.

Los virus biológicos, igual que los informáticos, son criaturas alucinantes. Se encuentra justo en el límite de lo que se conoce como un ser vivo (al menos así era cuando yo era un crío :). Para considerar un bicho un ser vivo, este bicho debe ser capaz de realizar las funciones vitales, ya sabéis, nacer, crecer, morir, reproducirse... Es esta última función vital la que mantiene a los virus fuera del reino de los seres vivos.

Los virus no pueden reproducirse por si mismos y necesitan de un huésped. De esta forma, los virus, inyectan su material genético en una célula huésped, convirtiendo esa célula en una replica del virus y, por lo tanto, permitiendo al virus reproducirse.

Un virus informático, hace exactamente lo mismo. Busca programas huéspedes en los que inyectar su código (ahora código binario, en lugar de código genético), y de esta forma convertir esos programas en nuevos virus.

Este proceso es sumamente interesante, tanto en el mundo real como en el virtual, lo que hace de estos pequeños (si los informáticos también suelen ser pequeños) unas criaturas intrigantes. Si nos olvidamos, por un segundo de los efectos nocivos que estos virus tienen tanto en nuestra salud como en nuestros ordenadores, los virus no son más que criaturas que luchan desesperamente por sobrevivir.

Ahora que ya tenemos un poco más claro lo que es un virus vamos a discutir brevemente algunos tópicos sobre estos minúsculos entes.

# Tópicos 1. No hay virus en Linux
Durante muchos años, corrió el bulo de que los sistemas GNU/Linux eran inmunes a los virus informáticos. Esto no es cierto en absoluto, y lo comprobaremos en breve. De hecho hay unos cuantos virus para sistemas GNU/Linux por ahí.

Lo que si es cierto es que, en general, el impacto de un virus en un sistema GNU/Linux es mucho menor que en otros sistemas. La razón fundamental no es necesariamente que GNU/Linux sea más seguro, sino que, las posibilidades de infección en uno de estos sistemas es mucho menor. Veamos por qué.

* Los sistemas UNIX, dada su naturaleza multiusuario, fuerzan, en cierto modo, el uso de usuarios no-privilegiados, lo cual, limita en gran medida la difusión de un virus. En general, un usuario no-privilegiado no puede escribir sobre los ejecutables del sistema (todos los programas en `/bin`, `/sbin`, `/usr/bin`,...), con lo cual, el virus no tiene gran cosa que infectar. 
* Por esa misma razón, aquellos que utilizan el sistema normalmente con el usuario `root`... pues bueno, da igual lo seguro que sea tu caja Linux, estás apañao. 
* Otra razón fundamental es que un usuario GNU/Linux raramente necesita descargar binarios de lugares extraños. Todo el software que necesita está disponible en los repositorios oficiales, reduciendo los riesgos de introducir en el sistema un programa desconocido.

Bueno, seguro que la mayoría de los que estáis leyendo este artículo, ya sabíais esto. Continuemos pues. 

# Tópico 2. Mi antivirus me protege
Volveremos sobre esto al final de artículo utilizando el caso práctico que presentaremos en breve, pero la creencia general de que tu ordenador está seguro simplemente por haber instalado un antivirus, es una verdad a medias.

Disponer de un antivirus es, por supuesto, una cosa buena, pero lo que tenemos que tener claro es que los antivirus solo nos protegen de los virus conocidos (matizaremos esto en un segundo). 

Al igual que las vacunas que nos ponemos de pequeños nos protegen de ciertas enfermedades, si contraemos una enfermedad para la que no estemos vacunados, ya sea por que no existe vacuna o por que se trata de una nueva enfermedad, pues vamos a enfermar si o si. En estos casos, la mejor solución es evitar contagiarse en primera instancia. 

Como decía más arriba esto tiene un matiz. Los antivirus modernos hacen más que mantener una base de datos de virus conocidos. Normalmente implementan métodos para examinar programas desconocidos y determinar si hacen algo _RARO_. Estas funciones son las que hacían que los ordenadores fueran extremadamente lentos hace años cuando se instalaba un antivirus. Afortunadamente, las cosas han mejorado, en los últimos años.

Hay distintas formas de realizar este análisis de los programa sospechosos, ya sea escrutando el código en busca de llamadas al sistema _sospechosas_ o simplemente ejecutando el programa desconocido en un _sandbox_ o _máquina virtual_ y ver si hace/cambia algo malo.

En cualquier caso, instalar un antivirus es una garantía, pero no absoluta. La mejor forma de evitar ser infectado es no descargar y ejecutar programas desconocidos. Esto ha sido así desde... desde siempre.

# Creando un virus
Ajá... este título ha llamado tu atención, jovenzuela rebelde :). Sí, tengo que admitir que es un poco sensacionalista. No, no vamos a escribir un virus, pero lo que si vamos a hacer es infectar un programa manualmente, de forma que podamos ver como actúa un virus y así explicar algunos cosillas más al final del artículo.

Bien, nuestro virus simplemente va a modificar otros programas, haciendo que impriman un mensaje en la pantalla, antes de ejecutarse. De tratarse de un virus real, el código que imprime ese mensaje sería, realmente el virus y por lo tanto, el programa infectado, cada vez que se ejecutase, activaría el virus infectando otros programas... y así sucesivamente.

Así que, lo primero que tenemos que hacer para poder infectar un programa, es conocer en que formato está almacenado en el disco. Y este formato, amigos mios, es ELF.

# Infectando Elfos
A primera vista parece que vamos a liberar una plaga mortal en la Tierra Media con el fin de acabar con esas criaturas de orejas puntiagudas. No temas Légolas, no nos interesan esos elfos, sino los fichero `ELF` (_Executable and Linking Format_).

El formato `ELF` es el estándar actual para la mayoría de sistemas UNIX, no solo GNU/Linux. Así que lo primero que debemos saber es como pinta ese formato.

La verdad es que hay cientos de tutoriales estupendos en Internet sobre el tema, así que aquí, vamos a hacer una breve introducción, solamente para que el artículo esté auto contenido. Los que tengáis ganas de profundizar en el tema os recomiendo fervientemente que os leáis la especificación del formato. No está tan mal para ser una especificación y, si tenéis pensado jugar con el formato es una referencia obligada. Sin más preámbulos vamos al lío.

Prácticamente todos los formatos de ficheros que existen comienzan con lo que se conoce como una cabecera. Esto es, un bloque de datos al principio del fichero, con un formato fijo, en el que se almacena la información necesaria para poder acceder correctamente a todos los demás datos. Y, como podéis imaginaros, el formato `ELF` no es una excepción.

Tras la cabecera, normalmente nos encontraremos la denominada _Program Header Table_. En seguida veremos en detalle que contiene. Por el momento, basta decir que esta tabla nos informa de los bloques de memoria que componen el programa. Tras esta tabla nos encontraremos el código y los datos reales del programa, y finalmente, y esto es opcional, podremos encontrar la denominada _Section Header Table_ y cierta información adicional. 

El siguiente esquema muestra gráficamente la estructura que acabamos de describir.

    |----------------------|
    | CABECERA ELF         |
	|----------------------|
	| Program Header Table |
	|----------------------|
	| Código y Datos       |
	|----------------------|
	| Section Header Table |
	|----------------------|
	|  Otros datos         |
	|----------------------|

La parte final con la tabla de secciones e información adicional no es extrictamente necesaria para poder ejecutar el programa. Normalmente esa información es relevante para el linkado o la depuración. Volveremos sobre ella brevemente un poco más tarde, pero por el momento vamos a ignorarla.

A partir de este punto va a ser mejor que pongamos nombres y apellidos a todas estas estructuras de datos, así que vamos a escribir un sencillo programa con el que estudiarlas en detalle.

```C
$  cat <<EOM | gcc -xc - -o victima
> #include <stdio.h>
> int *p;
> char *str = "Hola Mundo\n";
> int main (void){printf(str);}
> EOM
```

Para explorar nuestro nuevo y flamante binario, vamos a utilizar nuestra querida herramienta `readelf`. Si todavía no te has enamorado de ella, dale tiempo al tiempo. Ya sabes, el roce hace el cariño.

_Nota:Si vais a probar lo que sigue en vuestro ordenador, notad que es posible que, vuestra configuración genere un binario diferente al que yo estoy utilizando aquí (distintas versiones del compilador, libc,...) y no podáis utilizar los valores que aparecen en el artículo directamente. En ese caso, debéis leer la explicación y encontrar los valores adecuados para vuestro binario._

# La Cabecera
Lo primero que vamos a hacer es examinar la cabecera de nuestro binario de prueba:

```bash
$ readelf -h victima
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x400430
  Start of program headers:          64 (bytes into file)
  Start of section headers:          6672 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 28
```

Si, el flag `-h` (de _Header_ en inglés) muestra la cabecera del fichero. Toda esta información esta contenida en los primeros 64 bytes del fichero. Podéis comprobarlo con el siguiente comando:

```bash
$ cat victima | xxd | head -3
00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............
00000010: 0200 3e00 0100 0000 3004 4000 0000 0000  ..>.....0.@.....
00000020: 4000 0000 0000 0000 101a 0000 0000 0000  @...............
```

En el volcado de arriba, podéis ver claramente el campo `Magic` y el resto de datos, ordenando apropiadamente los bytes claro está.

Bueno, vamos a concentrarnos en los campos importantes. Seguro que ya los habéis identificado, pero por si estás un poco despistado en esta primera lectura...

```bash
  Entry point address:               0x400430
  Start of program headers:          64 (bytes into file)
  Start of section headers:          6672 (bytes into file)
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 28
```

Vayamos a través de la lista de campos uno a uno.

* `Entry point address: 0x400430`. Esta es la posición de memoria en la que el programa empezará su ejecución. Un virus sencillo, modificaría este valor para que apunte a su código, y de esta forma poder ejecutarse nada más lanzar el programa.
* `Size of this header: 64`. Pues como su propio nombre indica, este campo nos dice cual es el tamaño de la cabecera.
* `Start of program headers: 64`. Este campo nos indica el offset en el fichero en el que se encuentra la _Program Header Table_. La recordáis, esa tabla que se encontraba justo después de la cabecera. Pues ahí lo tenéis, la cabecera ocupa 64 bytes y la tabla está en el offset 64 :). Si recordáis, dijimos que esta tabla está normalmente justo después de la cabecera... bueno, modificando este campo podéis ponerla en cualquier otra parte del fichero.
* `Start of section headers: 6672`. Lo mismo para las secciones. Podéis comprobar el tamaño del fichero y veréis que este offset apunta hacia la parte final, como habíamos adelantado en la sección anterior.
* `Size of program headers: 56` y `Size of section headers: 64`. Estos campos nos indican el tamaño de cada una de las entradas en las tablas de programas y secciones, permitiéndonos indexar los distintos elementos de la tabla.
* `Number of program headers: 9` y `Number of section headers: 31`. Estos campos nos indican cuantos _Program Headers_ y secciones contiene cada tabla. Vamos, el valor que nos falta para poder escribir un bucle que recorra las tablas.
* `Section header string table index: 28`. Finalmente, este campo nos indica que sección contiene la tabla de cadenas de caracteres asociadas al fichero. En general, aquí nos encontraremos los nombres de la secciones, de los símbolos importados y exportados, etc... Estás cadenas está normalmente relacionadas con el proceso de enlazado y no tienen nada que ver con las cadenas que utiliza el programa (`Hola Mundo` en nuestro ejemplo). Esas otras se encuentra en el bloque de código y datos que mencionamos anteriormente. Estas cadenas de caracteres indexadas por este campo son parte de esa información extra que normalmente encontramos al final del fichero.

Continuemos con los _Program Headers_!

# La _Program Header Table_
Por el momento sabemos que la _Program Header Table_ está localizada justo después de la cabecera. Para nuestro ejemplo, esta tabla contiene 9 entradas de 56 bytes cada una. Vamos a ver que esconde esta tabla con la ayuda de nuestro querido `readelf`.

Analicemos la salida del comando por partes.

```bash
$  readelf -l victima

Elf file type is EXEC (Executable file)
Entry point 0x400430
There are 9 program headers, starting at offset 64

```
El flag `-l` es el que nos permite listar la _Program Header Table_. Lo primero que nos muestra `readelf` es un resumen de la información contenida en la cabecera. Tras esto nos encontramos la lista de segmentos. 

_Nota:La palabra segmento no es estrictamente correcta, sin embargo, ya que esta tabla es utilizada para generar el mapa de memoria principal del proceso, a mi me resulta más intuitivo hablar de segmentos cuando me refiero a las entradas de la Program Header Table. Además Cabecera de Programa es muy largo y realmente no significa nada :)._

Por cada segmento se muestran distintos campos. A saber:

* __Type__. Este campo indica el tipo de segmento. Existen distintos tipos de segmentos, pero para el caso que nos ocupa lo que nos interesa son los segmentos `PT_LOAD`, ya que estos nos indican que partes del fichero van a acabar cargadas en memoria.
* __Offset__. Este campo indica el desplazamiento dentro del fichero en el que encontrar los datos asociados con el segmento.
* **VirtAddr**. Este campo indica la posición en memoria en la que se creará el segmento y en la que, para los segmentos de tipo _PT_LOAD_ se escribirán los datos asociados a este segmento que se encuentran almacenados en el fichero.
* __PhysAddr__. En sistemas GNU/Linux este campo coincide con `VirtAddr`. En otros sistemas en los que las direcciones físicas de memoria son relevantes puede tener distintos valores.
* __FileSiz__. Este campo nos indica el tamaño en disco del segmento.
* __MemSiz__. Y este nos indica el tamaño que tendrá el segmento en memoria
* **Flags**. Si bien, existen flags dependientes del sistema y procesador, los que nos van a interesar a nosotros son los que indican los permisos del segmento. En concreto _Lectura_, _Escritura_ y _Ejecucución_, indicados, respectivamente por las letras `R`, `W` y `E`.
* __Align__. Finalmente, este campo indica el alineamiento de memoria para el segmento especificado. Un valor de 0 o 1 indica que no hay alineamiento.

Bueno, con toda esta información, podemos empezar a ver como se definen los distintos segmentos. Como decíamos más arriba, los segmentos de tipo `LOAD` son los que nos interesan, así que vamos a ignorar, por el momento, los demás.


```bash
Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
(...)
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x000000000000070c 0x000000000000070c  R E    200000
  LOAD           0x0000000000000e10 0x0000000000600e10 0x0000000000600e10
                 0x0000000000000230 0x0000000000000240  RW     200000
```

Como podéis ver, estos dos segmentos tienen, respectivamente, permisos de lectura/ejecución y lectura/escritura. Esto es típico, el primer segmento suele ser el segmento de código y datos de solo lectura, mientras que el segundo es el de datos, donde podemos leer y escribir, pero no podemos ejecutar código. 

Así, tendremos un segmento que se creará en la posición de memoria `0x400000` y tendrá un tamaño de `0x70c`. Esto último no es totalmente cierto, pero no es relevante en estos momentos y no vamos a complicar la explicación más de lo necesario. En esta posición de memoria se copiarán, directamente (tipo `LOAD`), los `0x70c` primeros bytes del fichero (el offset es cero para este primer segmento). El segundo segmento ya lo podéis leer vosotros mismos :P.

Las direcciones de memoria `0x400000` y `0x600000` os deberían resultar familiares si alguna vez habéis analizado algún binario de 64 bits. Sino, bueno, si estáis leyendo esto no tardaréis mucho en que sea así.

Bueno, ha sido un poco duro, pero ya tenemos todas la información necesaria para poder inyectar código en nuestro programa de ejemplo...Qué no?... Ahora veréis.

# Inyectando Código
Hay distintas formas de inyectar código en un fichero ELF. Puesto que nuestra infección la vamos a realizar de forma manual, elegiremos la técnica más sencilla, la conocida como inyección en cuevas de código. Las cuevas de código (o _Code Caves_) son, espacios vacíos en los programas. Las podemos encontrar tanto en los ficheros en el disco, como en la memoria una vez que el programa se carga y ejecuta.

Esta técnica es la más sencilla ya que nos proporciona un hueco en el que meter el código que queramos inyectar. Sin embargo, las cuevas de código tienen tamaños variables dependiendo del programa y, además, no es que nos proporcionen un hueco muy grande. Por esta razón, no es una de las técnicas más utilizadas por los virus, ya que, si el virus tiene un cierto tamaño, puede que no sea posible encontrar una cueva lo suficientemente grande, o al menos, muchos binarios no dispondrán del sitio suficiente para acomodar el virus.

La alternativa es crear el espacio nosotros mismos. Si bien el concepto es sencillo, el artículo se iba a liar bastante y no iba a ayudarnos a entender mejor las ideas principales. Diré, que la forma de crear espacio es manipulando las estructuras de datos de las que ya hemos hablado, ya sea incrementando su tamaño o insertando nuevos segmentos en el fichero.

## Cuevas de Código
Bien, ahora tenemos que encontrar una cueva de código en nuestro programa víctima. De hecho, lo que nos interesa es que exista una de esas cuevas entre nuestro segmento de código y nuestro segmento de datos, de tal forma que el código que inyectemos se cargue directamente en memoria con los permisos adecuados.

Echémosle un ojo de nuevo a los dos segment `PT_LOAD` que nos mostró `readlef`.

```bash
(...)
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x000000000000070c 0x000000000000070c  R E    200000
  LOAD           0x0000000000000e10 0x0000000000600e10 0x0000000000600e10
                 0x0000000000000230 0x0000000000000240  RW     200000
```

Como podéis ver, el primer segmento, el que tiene permisos de ejecución comienza en el offset `0x00` del fichero y tiene un tamaño de `0x70c`. Si nos fijamos en el siguiente segmento, veremos que su offset en el fichero es `0xe10`. Lo que esto significa es que en el fichero tenemos un hueco de `0xe10 - 0x70c = 0x704 = 1796 bytes` en el que poder inyectar nuestro código.

Comprobemos que realmente ese espacio está vacío.

```
$  dd if=victima bs=1 count=1796 skip=$((0x70c)) | xxd
00000000: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000010: 0000 0000 0000 0000 0000 0000 0000 0000  ................
00000020: 0000 0000 0000 0000 0000 0000 0000 0000  ................
(...)
00000700: 0000 0000                                ....
1796+0 records in
1796+0 records out
1796 bytes (1.8 kB, 1.8 KiB) copied, 0.00295752 s, 607 kB/s
```

Pues bien, esa es nuestra cueva. Como ya hemos mencionado anteriormente, estos espacios varían de tamaño de programa a programa y puede que no sean suficientemente grande para acomodar todo el código que queramos inyectar. Sin embargo, nos viene perfecto para nuestra explicación.

## Un virus?
No, no es un virus. Para poder continuar, necesitamos algún código que insertar en la víctima. En el caso de un virus real, ese código sería el virus. En nuestro caso, vamos a escribir un pequeño programa en ensamblador que muestra un mensaje en la consola. Algo como esto:


```asm
section .text

	global _start
_start: mov rax, 1    ; SYS_write = 1
	mov rdi, 1        ; fd = 1 (stdout)
	lea rsi, [rel msg]
	mov rdx, LEN      ; tamaño de la cadena
	syscall           ; (SYS_write = rax(1), fd = rdi (1), buf = rsi (msg), count = rdx (LEN))  

	;;  Terminar Program
	mov rax, 0x3c     ; SYS_exit = 0x3c
	mov rdi, 0        ; status = 0
	syscall           ; (SYS_exit = rax (0x3c), status = rdi (0))
	
	msg	db 'Que pasa lectores de Occams!!',0x0a
LEN:	 equ $-msg

```

Compilemos 

```bash
$  nasm -f elf64 -o virus1.o virus1.asm
```

Estupendo, ya tenemos un fichero objeto con el que empezar a trabajar!

## Infección Manual
Lo primero que necesitamos hacer es extraer del fichero objeto, el código máquina que queremos ejecutar. Un virus real tendrá que hacer, de forma automática, lo que nosotros vamos a hacer de forma manual en un momento. En nuestro caso, la situación es incluso más sencilla ya que estamos trabajando con un fichero objeto y no con un ejecutable.

Los ficheros objeto `.o` no pueden ejecutarse directamente. Su cometido es ser linkados con otros ficheros objeto para producir un ejecutable, algo parecido a lo que hacemos con una librería estática que no es otra cosa que varios fichero objeto empaquetados juntos con el gestor de archivos `ar` (`man ar` para saber más).

Bueno, resumiendo, la cosa es que los ficheros objeto no tiene _Program Header Table_ ya que no pueden ejecutarse, pero si tienen _Section Header Table_, y eso es lo que vamos a utilizar para extraer el código máquina que necesitamos. Veamos que se esconde en la tabla de secciones de nuestro fichero objeto.

```bash
$  readelf -S virus1.o
There are 5 section headers, starting at offset 0x40:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000180
       0000000000000042  0000000000000000  AX       0     0     16
  [ 2] .shstrtab         STRTAB           0000000000000000  000001d0
       0000000000000021  0000000000000000           0     0     1
  [ 3] .symtab           SYMTAB           0000000000000000  00000200
       0000000000000090  0000000000000018           4     5     4
  [ 4] .strtab           STRTAB           0000000000000000  00000290
       000000000000001b  0000000000000000           0     0     1
```

Como podéis imaginar, tanto por el nombre `.text` como por los permisos, la sección en la que estamos interesado es la número 1. Si nos fijamos atentamente, podremos ver que la información asociada a esta sección se encuentra en el offset `0x180` del fichero y tiene un tamaño de `0x42` bytes. Sí, ya sé que no hemos hablado de las secciones hasta ahora... pero seamos realistas. Si todavía estas leyendo esto no creo que necesites mucha explicación para entender esto :).

Lo que vamos a hacer ahora es comprobar que los números que hemos obtenido son los que realmente necesitamos para extraer el código máquina que queremos inyectar. Para ello utilizaremos `objdump` para volcar el código máquina y luego extraeremos con `dd` la parte que nos interesa. De esa forma podremos comprobar que la secuencia de bytes es la que realmente queremos.

```asm
$  objdump -d virus1.o

virus1.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_start>:
   0:   b8 01 00 00 00          mov    $0x1,%eax
   5:   bf 01 00 00 00          mov    $0x1,%edi
   a:   48 8d 35 13 00 00 00    lea    0x13(%rip),%rsi        # 24 <msg>
  11:   ba 1e 00 00 00          mov    $0x1e,%edx
  16:   0f 05                   syscall
  18:   b8 3c 00 00 00          mov    $0x3c,%eax
  1d:   bf 00 00 00 00          mov    $0x0,%edi
  22:   0f 05                   syscall

0000000000000024 <msg>:
  24:   51                      push   %rcx
  25:   75 65                   jne    8c <msg+0x68>
  27:   20 70 61                and    %dh,0x61(%rax)
  2a:   73 61                   jae    8d <msg+0x69>
  2c:   20 6c 65 63             and    %ch,0x63(%rbp,%riz,2)
  30:   74 6f                   je     a1 <msg+0x7d>
  32:   72 65                   jb     99 <msg+0x75>
  34:   73 20                   jae    56 <msg+0x32>
  36:   64 65 20 4f 63          fs and %cl,%gs:0x63(%rdi)
  3b:   63 61 6d                movslq 0x6d(%rcx),%esp
  3e:   73 21                   jae    61 <msg+0x3d>
  40:   21 0a                   and    %ecx,(%rdx)
  
$  dd if=virus1.o bs=1 skip=$((0x180)) count=$((0x42)) | xxd -g 1
00000000: b8 01 00 00 00 bf 01 00 00 00 48 8d 35 13 00 00  ..........H.5...
00000010: 00 ba 1e 00 00 00 0f 05 b8 3c 00 00 00 bf 00 00  .........<......
00000020: 00 00 0f 05 51 75 65 20 70 61 73 61 20 6c 65 63  ....Que pasa lec
00000030: 74 6f 72 65 73 20 64 65 20 4f 63 63 61 6d 73 21  tores de Occams!
00000040: 21 0a                                            !.
66+0 records in
66+0 records out
66 bytes copied, 0.000214502 s, 308 kB/s

```

Bingo. Ahora solo tenemos que inyectar este código en la cueva que habíamos encontrado anteriormente, la cual, si recordáis se encontraba en el ofset `0x70c` de nuestro programa víctima. Nuestra cueva nos permitía acomodar unos 1700 bytes, así que no tendremos problemas para inyectar esto `0x43` bytes. Esto lo podemos hacer con un comando como este:

```bash
$ dd if=virus1.o bs=1 skip=$((0x180)) count=$((0x42)) of=victim seek=$((0x70c)) conv=notrunc
```

_Nota:Los más curiosos podéis comprobar la página del manual de dd en caso de que tengáis curiosidad por lo que significa cada uno de los parámetros del comando anterior._

Si ahora comprobamos el contenido de la cueva de código del programa víctima, ya no encontraremos solo ceros!.

```
$  dd if=victima bs=1 count=1796 skip=$((0x70c)) | xxd
00000000: b801 0000 00bf 0100 0000 488d 3513 0000  ..........H.5...
00000010: 00ba 1e00 0000 0f05 b83c 0000 00bf 0000  .........<......
00000020: 0000 0f05 5175 6520 7061 7361 206c 6563  ....Que pasa lec
00000030: 746f 7265 7320 6465 204f 6363 616d 7321  tores de Occams!
00000040: 210a 0000 0000 0000 0000 0000 0000 0000  !...............
00000050: 0000 0000 0000 0000 0000 0000 0000 0000  ................

```

Podéis comprobar la salida de `objdump` más arriba para verificar que lo que hemos copiado es realmente el código de nuestro pequeño pseudo-virus :). Sí, tenéis que comprobar los números hexadecimales si no me creéis.

## Haciendo que se ejecute el código
Bien, hemos completado la primera parte del proceso de infección de cualquier virus; inyectar el código del virus en un programa huésped. Ahora tenemos que modificar ese programa para que, cada vez que el programa se lance, se ejecute el código de nuestro virus en lugar de el código original.

Este es un buen momento para volver sobre nuestros pasos y repasar la sección en la que hablamos sobre la cabecera ELF. Qué campo creéis que deberíamos modificar para conseguir nuestro propósito?. Bien dicho, `Entry Point` eso es.

Este campo, todavía apunta al código original (el cual no hemos modificado) (`0x400430`). Lo que queremos es que apunte al código que acabamos de inyectar. Para ello debemos calcular la posición de memoria en la que nuestro código será cargado. Esto es más sencillo de lo que parece. Nuestro código lo hemos insertado en el offset `0x70c` del fichero. Puesto que el segmento de código empieza en el offset `0`, y que se va a cargar en memoria a partir de la posición `0x400000` (según lo que nos ha contado `readelf` un poco más arriba), pues nuestro virus se encontrará en la posición de memoria `0x40070c`. Que no?.... vamos a probarlo:

```bash
$  readelf -h victima
ELF Header:
  (...)
  Entry point address:               0x400430
  Start of program headers:          64 (bytes into file)
  (...)
$ ./victima
Hola Mundo
$ echo -ne "\x0c\x07" | dd of=victima seek=$((0x18)) bs=1 count=2 conv=notrunc
(...)
$ readelf -h victima
ELF Header:
  (...)
  Entry point address:               0x40070c
  Start of program headers:          64 (bytes into file)
  (...)
$ ./victima
Que pasa lectores de Occams!!
```

_Podéis determinar el offset al campo Entry Point en la cabecera buscando la dirección original en el volcado hexadecimal, consultando la especificación de ELF, o usando la página de la wikipedia sobre ELF en la que se incluyen los offsets para cada campo tanto para ejecutables de 32bits como de 64bits_

Mola!... Hemos infectado un binario igual que lo haría un virus pero de forma manual e inocua. Un virus real debería contener código para hacer todo esto que nosotros hemos hecho manualmente (con algunas variaciones). Lo único que nos faltaría es ejecutar el código original. Para ello debemos actualizar nuestro virus.

# Virus 2.0
La nueva versión de nuestro virus, sustituye la llamada a `exit` para terminar el proceso, por una llamada al punto de entrada original. El código sería algo como esto;

```asm
section .text

        global _start
        push rdi          ; Almacenamos los registros que continenen parámetros 
        push rsi          ;  y que necesitamos modificar
        push rdx
_start: mov rax, 1        ; SYS_write = 1
        mov rdi, 1        ; fd = 1 (stdout)
        lea rsi, [rel msg]
        mov rdx, LEN      ; tamaño de la cadena
        syscall           ; (SYS_write = rax(1), fd = rdi (1), buf = rsi (msg), count = rdx (LEN))
        pop rdx
        pop rsi
        pop rdi
        mov rax, 0xaabbccdd ;; Para parchear
        jmp rax
        msg     db 'Que pasa lectores de Occams!!',0x0a
LEN:     equ $-msg

```

La dirección `0xaabbccdd` es una marca para saber donde insertar el punto de entrada original. En general, no podemos asumir que el punto de entrada de todos los programas es el mismo, por lo tanto, debemos obtenerlo para cada programa y parchear el código de nuestro virus para que, tras hacer sus cosas, salte al programa original. Por supuesto, esta es solo una forma de hacerlo. Sed creativos!.

Compilemos y echemos un ojo al fichero objeto que hemos obtenido:

```bash
$ nasm -f elf64 -o virus2.o virus2.asm
$ objdump -d virus2.o

virus2.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_start-0x3>:
   0:   57                      push   %rdi
   1:   56                      push   %rsi
   2:   52                      push   %rdx

0000000000000003 <_start>:
   3:   b8 01 00 00 00          mov    $0x1,%eax
   8:   bf 01 00 00 00          mov    $0x1,%edi
   d:   48 8d 35 11 00 00 00    lea    0x11(%rip),%rsi        # 25 <msg>
  14:   ba 1e 00 00 00          mov    $0x1e,%edx
  19:   0f 05                   syscall
  1b:   5a                      pop    %rdx
  1c:   5e                      pop    %rsi
  1d:   5f                      pop    %rdi
  1e:   b8 dd cc bb aa          mov    $0xaabbccdd,%eax
  23:   ff e0                   jmpq   *%rax

(...)
```

Como podéis ver, nuesta dirección `0xaabbccdd` se encuentra claramente en el offset `0x1f` de nuestro fichero objeto. Ahora ya podemos volver a infectar nuestro programa víctima. El proceso será igual que el que vimos en la sección anterior, pero con distintos valores y un comando extra para escribir la dirección del punto de entrada original en el código del virus. Algo como esto:


```
$ cp victima victima2
$ dd if=virus2.o bs=1 skip=$((0x180)) count=$((0x43)) of=victima2 seek=$((0x70c)) conv=notrunc
$ echo -ne "\x0c\x07" | dd of=victima2 seek=$((0x18)) bs=1 count=2 conv=notrunc
$ echo -ne "\x30\x04\x40\x00" | dd of=victima2 seek=$((0x1f + 0x70c)) bs=1 count=4 conv=notrunc
$  ./victima2
Que pasa lectores de Occams!!
Hola Mundo
```

Hemos hecho una copia del programa víctima original, para disponer de dos binarios infectados, cada uno de ellos con una de nuestras versiones del virus. Esto lo vamos a utilizar un poquito más tarde.

Pues ahí lo tenéis. Este virus solo imprime un mensaje en la pantalla... y además necesita bastante assistencia por nuestra parte, pero, en esencia, lo que acabamos de hacer es lo que muchos virus ahí fuera hacen de forma automática.

# Un interesante efecto lateral
Debo admitir que el resultado anteior me sorprendió un poco. Esperaba tener que parchear también los campos que contenían el tamaño del segmento de código. Si recordáis, cada segmento en la _Program Header Table_ contiene dos campos, una para el tamaño del segmento en memoria, y otro para el tamaño del segmento en el disco. Aparentemente, al menos para este sencillo caso, los campos son ignorados (en cierta medida) y la cueva de código entre el segmento de código y el de datos se carga en memoria independientemente de lo que digan esos valores.

La razón la verdad que no la he investigado. Quizás sea un tema interesante para un futuro artículo, pero este hecho tiene unos interesantes efectos laterales.

Probad a volcar el código del programa victima con el comando `objdump -d victima`. Efectivamente, ni rastro del código del virus. El volcado termina donde debe y no muestra el virus que se encuentra al final del código original. De la misma forma, si utilizáis `gdb` tampoco podréis ver el código, ni con el comando `disassemble` ni intentando un volcado directo con `x/20i *0x4007c0`. Para poder verlo tendréis que poner un breakpoint y comenzar la ejecución.

Desde el punto de vista de dificultar la detección del virus esto es bastante interesante. Si a esto, añadimos el hecho de que al utilizar una cueva de código no hemos cambiado el tamaño del binario, pues la verdad que nos a quedado un virus bastante molón.

# El punto de vista de los _Buenos_
Ahora que tenemos una idea general de como funciona un virus es un buen momento para cambiarnos el sombrero y enfrentarnos al tema desde el punto de vista de los _buenos_. Los que se encargan de que esos virus no afecten a nuestros bienamados compañero digitales :).

## El Investigador de Seguridad
Un investigador de seguridad informática, va a estar interesado en ser capaz de detectar ficheros infectados y, si es posible, eliminar el virus de esos ficheros. Vamos un punto de vista, como se suele decir, diametralmente opuesto :).

Movidos por nuestra vocación didáctica, veamos ahora como funciona un antivirus, y una vez más vamos a hacerlo manualmente, de forma que resulte más sencillo comprender que es lo que está sucediendo en cada momento.

Los antivirus han evolucionado de forma impresionante en los últimos años, convirtiéndose en sofisticados programas que hacen algunas filigranas bastante interesantes. Sin embargo, incluso hoy en día y con toda esa sofisticación, los antivirus todavía usan los métodos de búsqueda de patrones igual que lo hacían sus primitivos antepasados. La idea detrás de esta técnica es buscar una firma, una secuencia de bytes en el fichero que permita identificar un virus específico. Normalmente esta firma coincide con el código máquina de parte del virus, pero no siempre es el caso. Así, cuando le pides a tu antivirus que escanee un disco, una de las cosas que va a hacer es buscar ciertos patrones de bytes en los distintos ficheros almacenados en ese disco.

Veamos como funcionaría esto con nuestro virus básico. Para ello necesitamos encontrar una secuencia de bytes que identifique a nuestro virus. En este caso el virus es muy sencillo así que esto será bastante fácil. Simplemente utilizaremos el código del virus tal cual, el mismo que inyectamos manualmente. Fácil no?

Generemos una firma (o _signature_ como les gusta decir a los ingleses).

```
$ dd if=victim bs=1 count=$((0x5e)) skip=$((0x70c)) | xxd -p | tr -d '\n'> SuperVirus_v1.sig
```

Como podéis ver, simplemente estamos extrayendo el virus de nuestro programa víctima infectado con la primera versión de nuestro virus, y la estamos almacenando en un fichero de texto. Podríamos perfectamente utilizar el fichero `virus1.o` con los offsets y tamaños adecuados, y obtendríamos el mismo resultado.

Utilizando esta firma, podremos detectar ficheros infectados de forma muy sencilla con un comando como este:


```
$ xxd -p victim | tr -d '\n' | grep -c -f SuperVirus_v1.sig
1 
$ xxd -p /bin/ls | tr -d '\n' | grep -c -f SuperVirus_v1.sig
0
```

Este comando nos devuelve el valor `1` cuando el fichero que estamos comprobando está infectado, y un `0` en el caso contrario. El comando `tr` lo utilizamos para eliminar el formato que genera `xxd` (los saltos de línea en realidad) y obtener un volcado del fichero en una sola línea de forma que podamos utilizar `grep` para buscar la firma.

## Más sobre signaturas
El proceso anterior funciona perfectamente con nuestra primera versión del virus. Sin embargo, si intentamos utilizar este método con la versión 2.0, tendremos un pequeño problema.

Lo que sucede con la versión 2.0 es que estamos modificando el código del virus para que, cuando termine de hacer sus cosas, ejecute el programa inicial. En general, el punto de entrada de los binarios no es fijo. La posición de memoria en la que se carga el fichero en memoria si que lo suele ser (`0x400000` para ELF de 64 bits, a no ser que el binario sea `PIE` y randomización de direcciones), pero la posición de memoria a la que debemos saltar para ejecutar el programa original, en general va a variar. Vamos a comprobarlo rápidamente:


```bash
$ find /usr/bin -executable -type f -exec readelf -h {} 2> /dev/null  \; | grep Entry

```

Este comando busca todos los ejecutables en `/usr/bin`, imprime su cabecera con `readelf` y muestra el punto de entrada. Si lo ejecutáis veréis como las direcciones que aparecen son todas distintas (bueno, alguna habrá que coincida, pero eso es irrelevante).

Lo que esto significa es que, si infectamos cualquiera de estos programas con nuestra versión 2.0 del virus, y extraemos el virus del programa infectado, el punto de entrada original aparecerá en el código extraído, lo que hará que la firma sea diferente para cada uno de ellos. Así que, lo que tenemos que hacer es reducir el tamaño de nuestra firma para que la parte que contiene el punto de entrada, quede fuera de la misma (o utilizar un sistema más sofisticado para localizar la firma). Echemos un ojo al volcado del virus 2.0:

```bash
$ dd if=virus2.o bs=1 skip=$((0x180)) count=$((0x43)) | xxd -p
575652b801000000bf01000000488d3511000000ba1e0000000f055a5e5f
b8ddccbbaaffe05175652070617361206c6563746f726573206465204f63
63616d7321210a
(...)
```

En la salida podemos ver claramente nuestra marca `AABBCCDD`, así que, si nos quedamos con la primera línea del volcado, deberíamos de poder detectar el virus, independientemente del punto de entrada que se inserte al final.

```
$ dd if=virus2.o bs=1 skip=$((0x180)) count=$((0x18)) | xxd -p > SuperVirus_v2.sig
```

Ahora podemos volver a ejecutar nuestro _Antivirus Manual_.

```bash
$ xxd -p victima2 | tr -d '\n' | grep -c -f SuperVirus_v2.sig
 1
$  xxd -p /bin/ls | tr -d '\n' | grep -c -f SuperVirus_v2.sig
0
```

Ahora, si queréis, podéis intentar infectar algún otro programa con punto de entrada diferente y comprobar que la nueva firma funciona en ambos casos.

# El mundo Real
Supongo que la mayoría de vosotros estaréis pensando que esto es muy tonto no?. Que no puede ser tan fácil. La verdad es que, ni es tan fácil ni es mucho más difícil. Vamos a analizar un ejemplo real, y ver que pinta tienen esas signaturas. Para ello vamos a tomar como ejemplo la signatura para el  [Slapper Worm](https://www.f-secure.com/v-descs/slapper.shtml) utilizada por `clamav`, un antivirus muy popular en los sistemas GNU/Linux.

Una vez descargados y descomprimidos los ficheros de firmas (consultad la FAQ de `clamav` o dejad un comentario si necesitáis ayuda), para el gusano _Slapper_ nos encontramos la siguiente firma:


    Unix.Worm.Slapper-1:0:*:82838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9fa0
    a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebfc0c1c2c3c4c6c7c8c9cacbcc
    cdcecfd0d1d2d3d4d5d6d7d8d9dadbdce0e1e2e3e4e5e6e7e8e9eaebecedeeef


Como podéis ver el formato es muy sencillo. Los campos están separados por `:` y son solo 3. El primero es el nombre del virus. El siguiente es el offset en el fichero en el que buscar la firma. En este caso, este desplazamiento es '*', lo que significa que la firma puede estar en cualquier parte del fichero. Y finalmente nos encontramos la firma del virus la cual es muy parecida a las que hemos generado en las secciones anteriores.

Si bien, este método de detección es muy sencillo, evitar ser detectado de esta forma no es tarea fácil (una vez que el virus ha sido identificado y añadido a la base de datos). Los virus más sofisticados son capaces de mutar en cada infección generando nuevas firmas cada vez que infectan un nuevo fichero. Estos virus se conocen como virus polimórficos (por que tienen muchas formas :)) y son muchísimo más complejos que nuestro virus manual de ejemplo. Para estos casos, así como para la detección de nuevos virus cuya signatura no se encuentra en la base de datos, los antivirus utilizan técnicas más sofisticadas, pero eso lo dejaremos para otro artículo. Quizás. 

Para terminar, decir que, si bien los antivirus son güays y útiles, la mejor defensa frente a este tipo de ataques (_malware_) es el sentido común y seguir las reglas de seguridad básicas: no usar el sistema como `root`, no ejecutar cualquier cosa que nos encontremos, tener un firewall instalado, hacer copias de seguridad frecuentes... vamos, lo normal.... que ninguno hacemos :).

# Desinfección

Ahora que sabemos como detectar los ficheros infectados en nuestro sistema, llega el momento de intentar eliminar el virus. La desinfección no siempre es posible, depende de si el virus ha destruido parte del programa original y, en ese caso habrá que borrar el fichero infectado e instalar una nueva versión limpia... que por otra parte es quizás la mejor forma de solucionar el problema... he mencionado el tema de las copias de seguridad?

Dicho esto, supongamos que nuestro virus no destruye el código original y queremos desarrollar una vacuna para desinfectar todos los fichero _enfermos_ de nuestro sistema... Seamos claros... recuperar un backup completo de un sistema es un dolor de muelas en la mayoría de los casos. Tener un programilla que ejecutamos y nos lo deja todo niquelado es mucho más atractivo :). 

Vale. Para nuestro sencillo virus, una vacuna solo tiene que hacer dos cosas:

* Restaurar el punto de entrada del programa
* Borrar el código del virus escribiendo, por ejemplo ceros sobre el código inyectado. Esto no es estrictamente necesario, pero eliminar totalmente el código del virus en lugar de dejarlo _latente_ en el binario, parece una buena idea. Aunque solo sea para que el antivirus deje de detectar el virus aún después de haber sido desactivado :).

A estas alturas, creo que esto lo podéis hacer vosotros sin problemas con todo lo que hemos visto hasta ahora. Recordad que tenemos un dispositivo muy mono llamado `/dev/zero` que genera ceros :).

Notad que, en realidad, nuestro pequeño virus es, en cierto modo, destructivo, en el sentido de que sobrescribe el punto de entrada del binario. En este caso, el investigador de seguridad, tendría, probablemente, que hacer un poco de ingeniería inversa para poder encontrar el punto de entrada original y de esta forma desinfectar el fichero. 

Como os podéis imaginar, en el mundo real, las cosas no son tan sencillas. El proceso de desinfección, en un mundo ideal, debería borrar cualquier rastro del virus y sus efectos, sin embargo esto no siempre es posible, especialmente con virus destructivos que eliminan o corrompen datos del sistema. En esos casos, las copias de seguridad es la única opción para recuperar el sistema.

## El punto de vista del Usuario
Para terminar con este artículo vamos a ponernos por un momento de el pellejo del usuario. Por usuario aquí nos referimos a esas personas que utilizan el ordenador y las herramientas que proporciona, pero que, por la razón que sea, no saben ni quieren saber como funciona el ordenador.

En este contexto, es común escuchar comentarios como: "Que mal va tu ordenador, a lo mejor tienes un virus". Es también común que muchos usuarios extrapolen el concepto de una infección de un virus informático al de una infección por un virus biológico y crean que su ordenador _está enfermo_ y que puede contagiar a otros ordenadores. Si bien, tomadas literalmente estas frases pueden parecer tonterías, la realidad es que ese punto de vista no es tan descabellado, sobre todo, hace que los usuarios actúen con mayor cautela y, por lo tanto, minimicen los efectos de la infección. Para mi es super interesante ya que muestra como la cultura popular crea elementos de protección fáciles de asimilar por cualquiera y como esto sucede en lapsos de tiempo relativamente cortos... un artículo sobre antropología sería interesante... estoy dando pistas :).

Nosotros aquí vamos a ir un poco más allá e intentar explicar porque ese tipo de comportamientos (programas que fallan, respuesta lenta del sistema,...) sí que pueden ser síntomas de una infección.

La realidad es que hay muchos virus por ahí cuyo código tiene fallos, y esto es lo que provoca estos comportamientos. Veamos algunos ejemplos:

* En ocasiones, y esto también pasa con otros programas, no solo con los virus, los desarrolladores usan máquinas bastante potentes para hacer sus programas. Con los recursos de esa máquina, el programa funciona sin problemas, pero cuando intentas ejecutarlo en una máquina más modesta, el impacto en el rendimiento es muy grande, en ocasiones llegando a bloquear o ralentizar de forma claramente apreciable todo el sistema. Cuando se trata de un programa normal, la solución es escribir en la caja/web del programa unos requisitos mínimos de hardware para poder ejecutar el programa... Los virus no te preguntan si tienes 2 o 4 Gb de RAM... :)
* Otras veces, el virus está preparado para atacar configuraciones específicas (una versión del sistema operativo o distribución concreta). En esta situación es posible que el código del virus no funcione correctamente y, aunque sea capaz de infectar ficheros, no sea capaz de ejecutarse. El resultado es que ciertos programas dejan de funcionar de repente.
* Otra razón para este comportamiento puede ser una codificación pobre del código que elige el programa víctima a infectar o que activa el virus. En estos casos se puede producir un efecto avalancha (varías instancias del mismo virus escaneando el disco en busca de victimas) que tenga un impacto en el rendimiento del sistema.

En general, un virus, de los buenos, no mostrará estos fallos. De hecho, si es realmente bueno, puede permanecer meses o años en un sistema infectando binarios y aguardando pacientemente a que llegue el momento adecuado para hacer lo que tenga que hacer. Hay varios casos de virus que se activaban en determinadas fechas o bajo otras condiciones. Algunos ejemplos famosos son el virus Michelangelo o el devastador CIH.

## Un ejemplo práctico.
Para entender un poco mejor porque pueden pasar algunas de estas cosas, volvamos por un momento a nuestro ejemplo. Si recordáis, el método que utilizamos para inyectar el código fue el de buscar cuevas de código en el fichero. Como dijimos, el tamaño de estas cuevas varia de binario a binario, y si el virus es grande, hay posibilidades de que no _quepa_ en la cueva.

Lo normal, es que el virus, no se preocupe de comprobar cosas como esas. Simplemente va a infectar el fichero y si el programa original deja de funcionar, pues qué esperabas?, estás infectado!!!. Los virus que quieren permanecer indetectables si que hacen estas comprobaciones para no levantar ningún tipo de sospecha.

Para demostrar este caso, vamos a coger nuestro programa víctima infectado con la versión 2.0 de nuestro virus, la que también ejecuta el programa original, y vamos a escribir más datos de los que deberíamos en el fichero, simulando lo que sería un virus más grande. Si bien este escenario no es totalmente representativo, como veremos, una vez que analicemos lo que pasa, si que es aplicable.

Así que lo que haremos será insertar datos aleatorios justo después del código de nuestro virus y ver que pasa.

```bash
$ cp victima2 victima2.CORRUPTA
$ dd if=/dev/urandom bs=1 count=1700 of=victima2.CORRUPTA seek=$((0x770)) conv=notrunc
$  ./victima2.CORRUPTA
Que pasa lectores de Occams!!
Segmentation fault (core dumped)

```

_Nota: Puede que en vuestro sistema, por la razón que sea, la cueva de código tenga un tamaño diferente y el parámetro count del ejemplo anterior debe ser mayor o menor. Si habéis seguido el artículo deberías tener una idea de que valores utilizar o al menos como encontrarlos._

Ahí lo tenemos. Veámos en detalle que es lo que ha pasado.

Si recordáis, la cueva de código que utilizamos se encontraba entre el segemento de código `.text` y el de datos `.data`. Al escribir más de la cuenta, lo que hemos hecho es sobreescribir el segmento de datos. Si ejecutáis el programa en `gdb` y exploráis un poco veréis que lo que ha pasado es que hemos corrompido la zona del segmento de datos que contiene la tabla de constructores. El virus se ejecuta directamente, pero cuando devuelve el control a `_start`, esta función intentará ejecutar los constructores definidos en la sección `.init` (invocando la función `__libc_csu_init`), los cuales ahora están corrompidos y apuntan a saber donde. 

_Nota:Podéis examinar el contenido de la sección `.init` en el fichero y el valor de `RIP` en `gdb` cuando el programa se estrella._

De cualquier forma, como podéis ver, dependiendo de como se haya escrito el virus y de las comprobaciones que este haga, es más que posible que una infección tenga como efecto lateral que algunos programas dejen de funcionar... vamos que el ordenador empiece a hacer cosas raras. Que esté enfermo. Bendita sabiduría popular!.

# Conclusiones
Bueno, pues hasta aquí esta introducción a los virus informáticos. Hemos visto los principios básicos de su funcionamiento, de como se pueden detectar y eliminar y también hemos profundizado un poquillo en las razones por las que nuestro ordenador se puede comportar de forma errática o simplemente extraña cuando hemos sido víctimas de una infección.

Si el tema os ha resultado interesante y queréis más... hacédnoslo saber!


Creditos: Drew Hays
https://unsplash.com/photos/tGYrlchfObE
