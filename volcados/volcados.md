# Manejando Volcados de Disco como un Pro

uthor: Nelly Kerningham_

_Roor Numero 4_

_Esta obra está bajo una [Licencia Creative Commons Atribución 4.0 Internacional](http://creativecommons.org/licenses/by/4.0/)._

Leélo en: [ROOR] (http://www.papermint-designs.com/roor/2018-01-manejando-volcados-de-disco-como-un-pro)

-----

En este artículo os vamos a contar todos los secretos para trabajar con imágenes de disco en plan profesional. Si bien existen muy buenas herramientas hoy en día que nos permiten hacer prácticamente de todo, nosotros que somos mú tradicionales vamos a contaros como trabajar con imágenes de disco en la línea de comandos. Amo allá.

Ya sea porque necesitamos hacer un backup completo de un disco, porque queremos echar un ojo a la última imagen de nuestra distro preferida para nuestro querido SBC o por que deseamos aprender un poco más sobre como trabajan los forenses informáticos, en algún momento de nuestra vida vamos a tener que vérnoslas con esas dichosas imágenes. Así que mejor estar preparados y tener este artículo bookmarkeado :).

# Generalidades
Antes de meternos en harina, vamos a hacer un par de comentarios que, si bien pueden parecer triviales, es mejor dejar claros en caso de que alguien esté un poco despistado mientras lee este interesantísimo artículo.

Normalmente, cuando nos dispongamos a hacer una imagen de un disco nos interesa que el disco no esté siendo usado o, como mínimo, que no tenga permisos de escritura. De no ser así, los datos que estamos volcando podrían modificarse mientras los copiamos. En general, eso puede hacer que el proceso de copia falle o que ciertos datos se corrompan...

Para ello, podemos hacer dos cosas:

* Extraer el disco del ordenador y conectarlo como un disco externo en otro ordenador. Para ello debemos asegurarnos de que el sistema operativo del ordenador que utilizaremos para la copia está configurado para no montar automáticamente discos externos
* Arrancar el ordenador que contiene el disco a copiar con una distro live. De nuevo, debemos asegurarnos de que la distro usada no monta los discos en el ordenador automáticamente.

Si queréis probar los distintos comandos que vamos a discutir en el artículo, os aconsejamos que utilicéis un lapicero USB o una tarjeta SD en lugar de el disco duro, sino queréis esperar durante mongollón de tiempo entre prueba y prueba. Alternativamente podéis crear una imagen de disco a medida para hacer las pruebas o alguna de las imágenes disponibles para Raspberry PI, BeagleBone y similares

# Generando una imagen de test
En la sección de trucos del número 3 os contamos como generar una imagen de una partición EXT4. Vamos a utilizar la misma técnica para generar una imagen de disco con dos particiones y sistema de ficheros FAT y EXT4, para aquellos de vosotros que no queráis trastear con el disco duro de vuestro ordenador.

Aquí está la secuencia de comandos:

```bash
$ fallocate -l 1G test.img
$ fdisk test.img <<EOC
o

n
p
1

+100M
t
b

n
p
2


t
2
83

w
q
EOC

```

Ya tenemos nuestra imagen de disco con dos particiones, pero todavía necesitamos crear los sistemas de ficheros. Veamos como.

# Creando sistemas de ficheros
Para crear sistemas de ficheros (lo que algunos conocen como formatear :), debemos utilizar la familia de funciones `mkfs.XXX` donde `XXX` es el sistema de ficheros que queremos crear. En nuestro caso, en la primera partición queremos un sistema de ficheros `FAT32` y en la segunda crearemos un `EXT4`. Este es el caso para la mayoría de las imágenes de las placas de desarrollo que nos podemos encontrar por ahí.

A diferencia de lo que ocurre con un dispositivo real, donde podemos acceder directamente a las particiones, en nuestra imagen cada partición se encuentra en una determinada parte del fichero. Lo primero que debemos hacer es encontrar los offsets dentro del fichero para cada particion. Comprobemos la información que nos ofrece `fdisk -l` para nuestra imagen:

```bash
$ fdisk -l test.img
Disk test.img: 1 GiB, 1073741824 bytes, 2097152 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x4b4b8e62

Device     Boot  Start     End Sectors  Size Id Type
test.img1         2048  206847  204800  100M  b W95 FAT32
test.img2       206848 2097151 1890304  923M 83 Linux

```

El comando anterior nos proporciona toda la información que necesitamos. En primer lugar nos indica las unidades utilizadas en la salida. En este caso se trata de sectores de 512 bytes.

```
Units: sectors of 1 * 512 = 512 bytes
```

En segundo lugar nos indica el valor de comienzo de las distintas particiones utilizando la unidad anteriormente indicada. Vamos secores de 512 byte. Por tanto, debemos multiplicar el valor en la columna _Start_ de la lista de particiones por 512, para obtener el desplazamiento en bytes dentro del fichero. En un segundo veremos por que necesitamos ese valor en bytes. Así:

    Particion 1: 2048   Unidades -> 2048   * 512 = 1048576
	Particion 2: 206848 Unidades -> 206848 * 512 = 105906176

Ahora ya podemos crear nuestros sistemas de ficheros. Para ello utilizaremos dispositivos de _loopback_ que nos permiten acceder a un fichero como si de un dispositivo real se tratase. 

```bash
$ sudo losetup -o $((2048*512)) loop0 test.img
$ sudo mkfs.vfat /dev/loop0
$ sudo losetup -D /dev/loop0
$ sudo losetup -o $((206848*512)) loop0 test.img
$ sudo mkfs.ext4 /dev/loop0
$ sudo losetup -D /dev/loop0
```

El comand `losetup` nos permite crear un dispositivo `loop` sobre un fichero, y nos da la opción de indicar un offset dentro de ese fichero que es justo lo que queremos. Una vez que el dispositivo ha sido creado ya solo tenemos que crear el sistema de ficheros con `mkfs.XXX`, y destruir el dispositivo una vez que estemos listos.

# Creando imágenes de disco
Vamos a comenzar viendo como generar una imagen de un disco, algo que, como veremos en un segundo es algo super sencillo utilizando el comando `dd`.

```bash
$ sudo dd if=/dev/sdb of=/tmp/disco.img
o
$ sudo dd if=/tmp/test.img of=/tmp/disco.img
```

Fácil que no?. El comando `dd` nos permite copiar datos de un fichero a otro, y como en UNIX todo es un fichero, `dd` nos va a permitir copiar prácticamente cualquier cosa. En el comando anterior el flag `if` identifica el fichero de entrada (_Input File_ supongo) y el flag `of` identifica el fichero de salida (_Output File_). 

El comando que acabamos de ver hace un volcado del disco `/dev/sdb`, esto es, todo el disco incluyendo el sector de arranque, tabla de particiones y toda la pesca. Alternativamente podéis hacer un volcado de una partición en concreto pasando como parámetro el nombre de la misma. Por ejemplo `/dev/sdb1` volcará la primera partición del disco `/dev/sdb`.

Como suele ocurrir con la mayoría de las herramientas de línea de comandos, si no especificamos un fichero de entrada, `dd` utilizara la entrada estándar (`stdin`) y, de la misma forma, si no especificamos un fichero de salida, los datos se volcarán en la salida estándar `stdout`.

Así, podemos utilizar `dd` para crear fichero en plan _superfreak_.

```bash
$  dd of=test.c
#include <stdio.h>

int main() { printf ("Hola\n");}
0+3 records in
0+1 records out
53 bytes copied, 26.9184 s, 0.0 kB/s

```
_Nota: Debéis pulsar CTRL+D para terminar la entrada de datos._

Con esta nueva e interesante información, podemos mejorar ostensiblemente nuestra técnica de volcado de datos.

# Comprimiendo
El comando de volcado que acabamos de ver, genera una imagen byte a byte de todo el disco. En general, el volcado del disco no nos va a caber en él mismo por razones obvias, así que tendremos que usar un espacio de almacenamiento alternativo. 

En general, utilizaremos un disco externo o un servidor remoto. Además, podemos comprimir los datos antes de copiarlos ahorrando espacio. Pensad que estamos hablando de cientos de Gb.

Veamos como modificar nuestro comando anterior para comprimir los datos al vuelo:

```bash
$ dd if=/dev/sdb | gzip > /path_to_external/disco.img.gz
```

O utilizando `xz` que en general va a comprimir un poco más:

```bash
$ dd if=/dev/sdb | xz -zc > zero.img.xz
```

De esta forma conseguiremos que nuestra imagen ocupe menos, pero, ahora, generar la imagen requiere bastante mas tiempo.

# Troceando
Otra cosa que nos puede interesar hacer es trocear la imagen. Ya sea porque vamos a necesitar almacenarla en un soporte con un tamaño máximo de fichero limitado (DVDs por ejemplo) o no disponemos de un disco externo lo suficientemente grande para almacenar toda la imagen de golpe.

Para ello, podemos utilizar el siguiente comando:

```bash
$ dd if=/dev/sdb | split -d -b 500M - cacho-
```

Este comando funciona perfectamente, sin embargo no es de gran utilidad, ya que todos los pedazos se van a almacenar en el mismo lugar. Lo que necesitamos es almacenar cada pedazo en un dispositivo diferente.

En este caso quizás deberíamos escribir un pequeño script para, haciendo uso del flag `-n` de `split` para referenciar los bloques individualmente. Nosotros vamos a intentar hacerlo en una sola línea.

Para ello, supongamos que queremos volcar nuestro disco `/dev/sdb` de 1GB en dis discos externos de 500GB cada uno. Lo que vamos a hacer es montar los discos externos utilizando como punto de montaje el nombre del fichero que `split` generará para cada bloque:

```bash
$ cd /tmp
$ mkdir cacho-{00,01,02}
$ sudo mount /dev/sdc1 /tmp/cacho-00
$ sudo mount /dev/sdd1 /tmp/cacho-01
```

Ahora, el primer disco externo esta accesible en `/tmp/cacho-00` y el segundo en `/tmp/cacho-01`. Ahora podremos utilizar un comando como este:

```bash
$ dd if=/dev/sdb | split -d -b 500M --filter='cat > /tmp/$FILE/$FILE' - cacho-
```

El parámetro filter, nos permite pasar la salida de `split` por un comando shell para el que la variable `$FILE` ha sido inicializada con el nombre del fichero que `split` va a escribir. Así que, lo único que hacemos es redirigir la salida de `split` al fichero `/tmp/$FILE/$FILE`, es decir, `/tmp/cacho-00/cacho-00` para el primer cacho y `/tmp/cacho-01/cacho-01` para el segundo.

# Troceando y comprimiendo
Esto ya deberíais ser capaces de hacerlo vosotros mismos. En cualquier caso, para los más despistados, este sería el comando para hacer ambas cosas simultáneamente:

```bash
$ dd if=/dev/sdb | split -d -b 500M --filter='gzip > /tmp/$FILE/$FILE.gz' - cacho-
```

Lamentablemente, ahora el valor de `500M` que le pasamos a `split` no es de gran ayuda, ya que se refiere a los datos originales sin comprimir. Para poder sacar todo el partido a nuestro espacio de disco, ahora si que sería mejor escribir un pequeño script que vaya calculando el espacio ocupado en los discos externos por cada cacho del volcado copiado, y cambie de disco cada vez que se llenen.

# Comprobando imágenes
Suele ser buena idea, y en ocasiones es realmente necesario, el comprobar la integridad de los datos almacenados. Una forma sencilla de conseguir esto es calculando un _hash_ de los datos, tal como `MD5` o `SHA1`. Vamos a ver como calcular esos hashes en los distintos casos que hemos cubierto por el momento.

Empecemos calculando el hash de nuestra imagen original, utilizando `SHA256`:

```bash
$ dd if=/dev/sdb | sha256sum
2097152+0 records in
2097152+0 records out
1073741824 bytes (1.1 GB, 1.0 GiB) copied, 5.90121 s, 182 MB/s
03d6d763a08979ac91ae300d76db55514448fcbd812188df1e09b144ab16d5fe  -
```

Ahora veamos como calcular el hash de nuestra imagen comprimida con `gzip`.

```bash
$ zcat test.img.gz | sha256sum
03d6d763a08979ac91ae300d76db55514448fcbd812188df1e09b144ab16d5fe  -
```

Y en case de que hayamos usado `xz`L

```bash
$ xzcat test.img.xz | sha256sum
03d6d763a08979ac91ae300d76db55514448fcbd812188df1e09b144ab16d5fe  -
```

En el caso de haber troceado el fichero usaríamos el siguiente comando:

```bash
$  cat ca-* | sha256sum
03d6d763a08979ac91ae300d76db55514448fcbd812188df1e09b144ab16d5fe  -
```

Y por último, en el caso de que hayamos troceado y comprimido los cachos del volcado en distintos directorios:

```bash
$  zcat cacho-*/cacho*gz | sha256sum
03d6d763a08979ac91ae300d76db55514448fcbd812188df1e09b144ab16d5fe  -
```

Ahora que ya sabemos como generar imágenes.... veamos como acceder a ellas.

# Accediendo al contenido de las imágenes
Para acceder al contenido de nuestros fabulosos volcados de disco, podríamos restaurar la imagen en un dispositivo físico para obtener una copia exacta del disco original. Como os podéis imaginar, esto lo podemos hacer utilizando una vez más el comando `dd`, pero en este caso, utilizando como fichero de salida el disco en el que queremos volcar la imagen.

Imaginemos que queremos volcar nuestra imagen `test.img` en el disco `/dev/sdc` de un determinado ordenador. En general, el disco destino deberia tener las mismas caracteristicas que el disco original y al menos ser del mismo tamaño. Si bien puede parecer un poco raro, esta el la forma habitual de instalar el sistema operativo en pequeños ordenadores como Raspberry Pi o BeagleBone. La imagen que descargamos del sitio original es un fichero similar a los que hemos estado generando hasta el momento. En ese caso, volcamos ese fichero en una tarjeta SD que debe tener un tamaño mínimo para poder almacenar el sistema operativo. Bueno, en cualquier caso, lo que haríamos para restaurar la imagen sería:

```bash
$ sudo dd if=test.img of=/dev/sdc
```

Y si quisieramos restaurar la version comprimida de la imagen:

```bash
$ sudo zcat test.img.gz | dd of=/dev/sdc
```

Como podéis observar, podemos restaurar nuestra imagen con los mismos comandos que utilizamos para calcular el hash, pero substituyendo `sha256sum` por el comando `dd of=/dev/sdc`.

Por cierto, alguna gente sigue comprimiendo con `ZIP` imágenes. Aquí tenéis el comando para flashear sin necesidad de descomprimir primero

```bash
$ sudo unzip -p test.img.zip | dd of=/dev/sdc
```

# Montando particiones
En ocasiones no queremos restaurar el volcado sino que queremos acceder a algún fichero que se encuentra en la imagen, o hacer algún tipo de análisis. En esos casos, simplemente podemos montar la imagen de disco en lugar de hacer una restauración completa en un dispositivo físico.

Si la imagen de la que disponemos es de una sola partición, podemos montarla directamente utilizando el comando `mount`:

```bash
$ sudo mount -o ro test.img /tmp/mount_point
```

Es posible montar el sistema de fichero en modo lectura/escritura e incluso modificar fichero en su interior. En ese caso no utilices la opción `-o ro`.

Sin embargo, si lo que tenemos es una imagen de un disco completo, el proceso de montaje es un poco más complejo... aunque no mucho más. 

Lo que sucede es que ahora, tenemos que saltarnos el sector de arranque y la tabla de particiones para poder acceder a la parte del disco donde se encuentra el sistema de ficheros que queremos montar. En otras palabras, tenemos que decirle a `mount` en que parte del fichero se encuentra la partición que queremos montar.

En nuestro fichero de ejemplo, creamos una imagen de disco con dos particiones. En mi sistema, el resultado es algo talque así:

```bash
$ fdisk -l test.img
Disk test.img: 1 GiB, 1073741824 bytes, 2097152 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x09930925

Device     Boot  Start     End Sectors  Size Id Type
test.img1         2048  206847  204800  100M  b W95 FAT32
test.img2       206848 2097151 1890304  923M 83 Linux
```

Ahora solo debemos pasar el offset correct a `mount` para acceder a las distintas particiones. Recordad, debemos multiplicar el valor de la column _Start_ por el tamaño de las unidades utilizadas por `fdisk` (512 en este caso), para obtener el desplazamiento en bytes dentro del fichero.

```bash
$ mkdir part1
$ mkdir part2
$ sudo mount -o ro,offset=$((2048*512)) test.img ./part1
$ sudo mount -o ro,offset=$((206848*512)) test.img ./part2
```

Y ya podemos acceder a las particiones de nuestro volcado de disco!

% pandoc -s volcados.md -o /tmp/volcados.html
