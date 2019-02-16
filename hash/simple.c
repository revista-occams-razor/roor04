/*
 * simple - Generador de Hashes 
 * Copyright (c) 2018 Revista Online Occam's Razor
 *
 * This file is part of Numero 4 ROOR
 *
 * simple is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * simple is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with simple.  If not, see <http://www.gnu.org/licenses/>.
*/
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

  //fprintf (stderr, "Calculando '%s' para fichero '%s'\n", argv[1], argv[2]);

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



// gcc -o shasum shasum.c -lcrypto -lssl
// https://www.openssl.org/docs/manmaster/crypto/sha.html

