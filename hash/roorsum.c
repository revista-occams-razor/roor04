/*
 * roorsum - Generador de Hashes 
 * Copyright (c) 2018 Revista Online Occam's Razor
 *
 * This file is part of Numero 4 ROOR
 *
 * roorsum is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * roorsum is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with roorsum.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <openssl/evp.h>

#define PDEBUG(fmt,...) fprintf (stderr, fmt, __VA_ARGS__)

#define FILE_CHUNK 4096

/* Contexto para calculo de hash. Para este programa sencillo lo
 * vamos a declarar global :o */
const EVP_MD  *md;

unsigned char *
file_digest (char *fname, unsigned int *md_len)
{
  EVP_MD_CTX    *mdctx;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  FILE *f;
  unsigned char buffer[FILE_CHUNK];
  int           len;
 
  mdctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(mdctx, md, NULL);

  if (fname[0] == '-') f = stdin;
  else
    if ((f = fopen (fname, "rb")) == NULL)
      {
	fprintf (stderr, "No puedo abrir el fichero %s\n", fname);
	return NULL;
      }
  while (!feof (f))
    {
      if ((len = fread (buffer, 1, FILE_CHUNK, f)) < 0)
	{
	  perror ("fread:");
	  return NULL;
	}
      if(!EVP_DigestUpdate (mdctx, (unsigned char*)buffer, len))
	{
	  fprintf (stderr, "No puedo generar hash\n");
	  return NULL;
	}
    }

  fclose (f);
  if(!EVP_DigestFinal(mdctx, md_value, md_len))
    return NULL;
  EVP_MD_CTX_destroy (mdctx);

  /* Reserva meoria en el heap para retornar el hash */
  unsigned char *res = malloc (*md_len);
  memcpy (res, md_value, *md_len);

  return res;
}


void
dump_digest (unsigned char *md_value, int md_len)
{
  int i;

  for (i = 0; i < md_len; i++)
    printf ("%02x", (unsigned char) md_value[i]);

}

int 
usage (char *prog)
{
  printf ("Uso:\n%s [-h funcion_hash]\n", prog);
  exit (1);
}

int 
main(int argc, char *argv[])
{
  unsigned int   md_len, i, f;
  unsigned char *md_value;
  char          *hfunc;
  char          *fname;

  /* A no ser que nos digan lo contrario vamos a generar un SHA256 */
  hfunc = strdup ("sha256");

  /* Parseamos Parametros */
  for (i = 1, f = 1; i < argc; i++)
    {
      if ((!strcmp (argv[i], "-h")) || 
	  (!strcmp (argv[i], "--hfunc")))
	{
	  if (argv[i + 1] == NULL) usage (argv[0]);
	  free (hfunc);
	  hfunc = strdup (argv[i + 1]);
	  i++;
	  f+=2;
	  continue;
	}
    }

  fname = argv[f];
  PDEBUG ("Usandon Función: '%s'\n", hfunc);

  /* Inicializa OpenSSL y contexto para calcular hashes*/
  OpenSSL_add_all_digests ();
  if (!(md = EVP_get_digestbyname (hfunc)))
    {
      fprintf (stderr, "Funcion %s desconocida\n", hfunc);
      exit (1);
    }

  if ((md_value = file_digest (fname, &md_len)))
    {
      dump_digest (md_value, md_len);
      printf ("  %s\n", fname);
    }
  else
    printf ("%s: %s: %s\n", argv[0], fname, strerror(errno));
  

  return 0;
}



// gcc -o shasum shasum.c -lcrypto -lssl
// https://www.openssl.org/docs/manmaster/crypto/sha.html

