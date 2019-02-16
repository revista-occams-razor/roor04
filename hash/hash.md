# Calculando Hashes en tus Programas con OpenSSL
_Author: Nelly Kerningham_

_Roor Numero 4_

_Esta obra está bajo una [Licencia Creative Commons Atribución 4.0 Internacional](http://creativecommons.org/licenses/by/4.0/)._

Leélo en: [ROOR] (http://www.papermint-designs.com/roor/2019-02-calculando-hashes-en-tus-programas-con-openssl)

-----

Una función _hash_ nos permite calcular una firma asociada a un conjunto de datos. La peculiaridad de estas funciones es que, simplemente modificando un byte de los datos originales, el resultado de la función cambia radicalmente. En este artículo vamos a explicaros como poder calcular cualquier tipo de _hash_ en vuestros programas.

Seguro que todos habéis utilizado en alguna ocasión programas como `md5sum` `sha256sum`, para calcular el _hash_ de un fichero y comprobar su integridad o verificar que se trata de un duplicado de otro fichero. Si bien este es quizás el uso más habitual al que la mayoría de los usuarios están expuestos, las funciones _hash_ se utilizan a menudo en los programas para otros menesteres. Algunos ejemplos:

* Generar _desafios_ para esquemas de autenticación de claves de un sentido (_one-way key_).
* Nombrar ficheros para evitar caracteres extraños y detectar duplicados.
* Generar _cookies_ para las identificar sesiones.

Estos son solo algunos ejemplos. Para poder generar un _hash_, tendremos que ir leyendo bloques de datos de la fuente que deseemos (un fichero, la entrada estándar, una conexión de red) e ir pasando esos datos por nuestra función de _hash_. Una vez que hayamos usado todos los datos, podremos recuperar el deseado resultado. :)

En el resto de este artículo vamos a ver como calcular cualquier tipo de _hash_ usando la librería __OpenSSL__.

# OpenSSL
La librería __OpenSSL__ nos proporciona las distintas herramientas criptográficas necesarias para poder utilizar lo que se conoce como capa segura de socket (`SSL` _Secure Socket Layer_) y la denominada seguridad de capa de transporte (`TLS` Transport Layer Security). Estos dos protocolos de red hacen uso de multitud de algoritmos criptográficos y __OpenSSL__ nos hace la vida más fácil cuando se trata de trabajar con estas cosas raras.

Algunas de las funciones que nos ofrece __OpenSSL__, extraídas de la página del manual.

* Creación y gestión de claves públicas y privadas
* Operaciones criptográficas usando claves públicas
* Creación de certificados X.509, CSR y CRLs 
* Encriptado y Desencriptado utilizando distintos cifrados
* Clientes y servidores de test SSL/TLS 
* Manejo de e-mail S/MIME firmado o encriptado
* Petición, generación y verificación de marcas de tiempo (_Time Stamps_)
* Cálculo de hashs (o _Message Digest_)

Como podéis ver, __OpenSSL__ nos ofrece un montón de funciones. Por ahora, vamos a centrarnos en la última categoría. Ya exploraremos el resto de la librería en futuros artículos.

# Un programa para generar hashes
Como solemos hacer, vamos directos al código. Hemos escrito una versión mínima de un programa capaz de generar _hashes_ utilizando todos los algoritmos proporcionados por __OpenSSL__. En el código que sigue, hemos eliminado las comprobaciones de error para mantener el código simple y corto.... Pero no olvidéis que siempre debéis comprobar los códigos de error retornados por las funciones.

Nuestro programa, espera dos parámetros. El primero será la función hash que deseemos utilizar, y el segundo será el fichero, del cual queremos calcular su hash. 

Aquí tenéis el programa completo. En las siguiente secciones lo iremos destripando, línea a línea.

```C
#include <stdio.h>
#include <openssl/evp.h>

#define FILE_CHUNK 4096

int 
main(int argc, char *argv[])
{
  const EVP_MD  *md;
  EVP_MD_CTX    *mdctx;
  unsigned int   md_len, i;
  unsigned char  md_value[EVP_MAX_MD_SIZE];
  FILE          *f;
  unsigned char  buffer[FILE_CHUNK];
  int            len;
  
  /* argv[1] -> función hash
   * argv[2] -> fichero
   */

fprintf (stderr, "Calculando '%s' para fichero '%s'\n", argv[1], argv[2]);

  /* Inicializa OpenSSL y contexto para calcular hashes*/
  OpenSSL_add_all_digests ();
  md = EVP_get_digestbyname (argv[1]);

  /* Calculamos hash*/
  mdctx = EVP_MD_CTX_create ();
  EVP_DigestInit_ex (mdctx, md, NULL);

  f = fopen (argv[2], "rb");
  while (!feof (f))
    {
      len = fread (buffer, 1, FILE_CHUNK, f);
      EVP_DigestUpdate (mdctx, buffer, len);
    }
  fclose (f);

  /* Recuperamos el hash calculado y destruimos el contexto */
  EVP_DigestFinal(mdctx, md_value, &md_len);
  EVP_MD_CTX_destroy (mdctx);

  /* Volcamos hash*/
  for (i = 0; i < md_len; i++)
    printf ("%02x", (unsigned char) md_value[i]);
  printf ("  %s\n", argv[2]);

  return 0;
}

```


# Inicializaciones 
Lo primero que debemos hacer es inicializar __OpenSSL__ para generar hashes, lo cual se consigue con el siguiente código:

```C
  OpenSSL_add_all_digests ();
  const EVP_MD *md = EVP_get_digestbyname (argv[1]);
```

Como podéis ver, le estamos pasando nuestro primer parámetro a la función `EVP_get_digestbyname`, la cual nos devolverá un objeto del tipo `EVP_MD`. Este objeto es el encargado de realizar el cálculo del _hash_ como veremos en un segundo.

# Creando un Contexto
Lo siguiente que debemos hacer es crear un contexto para poder calcular nuestro _hash_. Un contexto no es más que un bloque de memoria en el que la librería va a mantener cierta información necesaria para poder hacer sus cálculos.

Como veremos en un segundo, no podemos coger todos los datos de nuestro fichero, y pasarlo como parámetro a la función _hash_.... Que pasaría si nuestro fichero es de 100Gb?... quien tiene tanta RAM en su ordenador?.... Y si el fichero es de 100 Tb?. Efectivamente, para calcular el _hash_ de ficheros tan grandes (pensad por ejemplo en imágenes de disco), necesitamos leerlos en bloques e ir calculando el _hash_ poco a poco. 

El contexto es donde esa información intermedia que necesitamos se almacena. Crear un contexto para calcular hashes requiere otras dos llamadas:

```C
  EVP_MD_CTX    *mdctx = EVP_MD_CTX_create ();
  EVP_DigestInit_ex (mdctx, md, NULL);
```

Como podéis ver, la primera función crea el contexto, y la segunda lo inicializa con la función _hash_ que habíamos obtenido en el paso anterior a través de `EVP_get_digest_byname`.

Bien, Ya estamos listos para comenzar a calcular.

# Calculando
El cálculo del _hash_ es tremendamente sencillo usando __OpenSSL__. Simplemente debemos obtener nuestros datos y pasárselos al contexto para que haga su trabajo. El siguiente código, va a leer el fichero que pasamos como segundo parámetro, en bloques de tamaño `FILE_CHUNK` y comenzar a calcular el _hash_.

```C
  f = fopen (argv[2], "rb");
  while (!feof (f))
    {
      len = fread (buffer, 1, FILE_CHUNK, f);
      EVP_DigestUpdate (mdctx, buffer, len);
    }
  fclose (f);
```

Como podéis ver, una vez que tenemos nuestro contexto inicializado `mdctx`, solo tenemos que leer datos y pasárselos... Chupao.

Una vez que hayamos terminado con los datos, debemos informar al contexto para que nos devuelva nuestro hash y ya estaríamos listos... es decir, ya podemos destruir el contexto:

```C
  unsigned int   md_len;
  unsigned char  md_value[EVP_MAX_MD_SIZE];

  EVP_DigestFinal(mdctx, md_value, &md_len);
  EVP_MD_CTX_destroy (mdctx);
```


La función `EVP_DigestFinal` nos devuelve el valor del hash y la función `EVP_MD_CTX_destroy` elimina el contexto. Obviamente.

# Porque necesitamos esa última llamada?

Quizás os preguntéis porque tenemos que llamar a `EVP_DigestFinal`. La razón (bueno, creo, la verdad es que no lo he comprobado en detalle), es que estos algoritmos _hash_, normalmente trabajan sobre bloques de datos de un determinado tamaño. Mientras calculamos el _hash_, vamos introduciendo datos, pero si el tamaño de los datos que introducimos no es múltiplo del tamaño de bloque que necesita la función _hash_... Entonces tendremos que pararnos hasta que tengamos más datos.

Imaginad, que la función hash que hemos elegido es [`MD5`](https://en.wikipedia.org/wiki/MD5). `MD5` utiliza bloques de 512 bits, o lo que es lo mismo, bloques de 16 palabras de 32bits. Imaginad que nuestro fichero tiene un tamaño de 30 palabras de 32bits (960 bits, o 120 bytes). Las primeras 16 palabras las procesamos sin problema. El algoritmo las digiere sin más.

Cuando nuestro código termina de leer el fichero, en el contexto de nuestro `MD5`, tendremos 14 palabras almacenadas, las cuales no son suficientes para ejecutar una nueva vuelta del algoritmo (necesitamos 16). En este caso, el contexto seguiría esperando más datos, pero ya no hay más, así que tenemos que decirle que _ya está_, _sa'cabao_, _finito_, _this is the end_.

Cuando esto sucede, el algoritmo define una política de `padding`, es decir, como rellenar los datos que faltan para poder ejecutar una vuelta más del algoritmo y, por lo tanto, tener en cuenta esos datos que no nos llegaban para la última iteración. Por ejemplo, completando con ceros hasta tener un bloque de 16 palabras completo.

Pues bien, para eso es `EVP_DigiestFinal`.

# Mostrando orgullosamente nuestro HASH
Ahora ya solo nos queda mostrar orgullosamente nuestro _hash_. El _hash_ es un valor binario y, normalmente, se suele mostrar como un volcado hexadecimal.

Esto es algo que podemos hacer con las siguientes líneas:

```C
  for (i = 0; i < md_len; i++)
    printf ("%02x", (unsigned char) md_value[i]);
  printf ("  %s\n", argv[2]);
```

Observad como tras volcar el hash, también mostramos el nombre del fichero... igual que hacen las herramientas `md5sum` o `sha512sum`. 

Listo. Ya solo queda probarlo.

# Compilando
Podemos compilar nuestro generador de hashes con la siguiente línea:

```
$ gcc -o simple simple.c -lcrypto -lssl
```

Si, hemos llamado a nuestro fichero fuente C `simple.c` y necesitamos dos librerías para que funcione.

# Probando

Ha llegado la hora de probar nuestro programa. Para ello, lo primero que necesitamos saber es que algoritmos hash podemos usar. La forma más sencilla de obtener la lista es preguntando a __OpenSSL__ con la herramienta de línea de comandos `openssl`:).

```
$ openssl list-message-digest-algorithms
DSA
DSA-SHA
DSA-SHA1 => DSA
DSA-SHA1-old => DSA-SHA1
DSS1 => DSA-SHA1
MD4
MD5
RIPEMD160
RSA-MD4 => MD4
RSA-MD5 => MD5
RSA-RIPEMD160 => RIPEMD160
RSA-SHA => SHA
RSA-SHA1 => SHA1
RSA-SHA1-2 => RSA-SHA1
RSA-SHA224 => SHA224
RSA-SHA256 => SHA256
RSA-SHA384 => SHA384
RSA-SHA512 => SHA512
SHA
SHA1
SHA224
SHA256
SHA384
SHA512
DSA
DSA-SHA
dsaWithSHA1 => DSA
dss1 => DSA-SHA1
ecdsa-with-SHA1
MD4
md4WithRSAEncryption => MD4
MD5
md5WithRSAEncryption => MD5
ripemd => RIPEMD160
RIPEMD160
ripemd160WithRSA => RIPEMD160
rmd160 => RIPEMD160
SHA
SHA1
sha1WithRSAEncryption => SHA1
SHA224
sha224WithRSAEncryption => SHA224
SHA256
sha256WithRSAEncryption => SHA256
SHA384
sha384WithRSAEncryption => SHA384
SHA512
sha512WithRSAEncryption => SHA512
shaWithRSAEncryption => SHA
ssl2-md5 => MD5
ssl3-md5 => MD5
ssl3-sha1 => SHA1
whirlpool

```

Y ahora ya podemos comparar los resultados obtenidos con nuestro programa con las herramientas clásicas de este tipo:

```
$ ./simple md5 simple
8ea739ddf55afafa9c0150f120d3e7f9  simple
$ md5sum simple
8ea739ddf55afafa9c0150f120d3e7f9  simple
$ ./simple sha1 simple
dfabf5fcff1650b1e15c9fdad0346f778f71013e  simple
$ sha1sum simple
dfabf5fcff1650b1e15c9fdad0346f778f71013e  simple
$ ./simple sha256 simple
b54fdcab2a454539ed091e5498732d7125f7380d931782245e4f5c4bde354fc7  simple
$ sha256sum simple
b54fdcab2a454539ed091e5498732d7125f7380d931782245e4f5c4bde354fc7  simple
```

Genial!

# Conclusiones
Ahora ya sabéis como calcular _hashes_ en vuestros programas usando __OpenSSL__. Como podéis ver es muy sencillo. Además, os habéis familiarizado con el concepto de contexto, que se utiliza también con las funciones de encriptación, así que doble ventaja. Podéis obtener el código de este artículo en nuestro `github` junto con una versión más extensa con las comprobaciones de error implementadas.

Puedes descargar el ćodigo de este artículo, incluyendo la versión Markdown del mismo en: [Repo ROOR04](https://github.com/revista-occams-razor/roor04)
